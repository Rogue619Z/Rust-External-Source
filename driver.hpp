namespace D {
	class DRIVER
	{
	public:
		static void* Module();
	};
}
inline int ProcessID;
inline static std::mutex mtx;
enum Request {
	ReadMemory = 1,
	WriteMemoryK = 2,
	DriverCheck = 3,
	ModuleBase = 4,
	SecurityCheck = 5,
};
typedef struct Omen
{
	Request Request;
	ULONG64 SecureCheck;
	ULONG ProcessID;
	void* Buffer;
	UINT_PTR WriteAddr;
	ULONGLONG WriteSize;
	UINT_PTR ReadAddr;
	ULONGLONG ReadSize;
	void* Value;
	const char* ModuleName;
	ULONG64 ModuleBase;
	ULONG64 DriverCheck;
} Omen;

struct HandleDisposer
{
	using pointer = HANDLE;

	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
			CloseHandle(handle);
	}
};
using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;
inline const UINT GetProcessId2(std::string_view process_name) {
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return NULL;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE)
	{
		if (process_name.compare((LPSTR)(processentry.szExeFile)) == NULL)
		{
			return processentry.th32ProcessID;
		}
	}
	return NULL;
}

template<typename ... A>
inline uint64_t SendOveride(const A ... Override)
{
	void* SendOverideM = D::DRIVER::Module();
	const auto SendOveride = static_cast<uint64_t(__stdcall*)(A...)>(SendOverideM);
	return SendOveride(Override ...);
}
static ULONG64 GetModuleBase(const char* ModuleName)
{
	Omen c;
	c.ProcessID = ProcessID;
	c.Request = Request::ModuleBase;
	c.SecureCheck = Request::SecurityCheck;
	c.ModuleName = ModuleName;
	SendOveride(&c);
	ULONG64 base = NULL;
	base = c.ModuleBase;
	return base;
}
template <class T>
T read(uintptr_t ReadAddr)
{
	mtx.lock();
	T response{};
	Omen c;
	c.ProcessID = ProcessID;
	c.ReadSize = sizeof(T);
	c.ReadAddr = ReadAddr;
	c.Request = Request::ReadMemory;
	c.SecureCheck = Request::SecurityCheck;
	c.Value = &response;
	SendOveride(&c);
	mtx.unlock();
	return response;
}
inline uintptr_t DriverConnection()
{
	Omen C;
	C.Request = Request::DriverCheck;
	C.SecureCheck = Request::SecurityCheck;
	SendOveride(&C);
	ULONG64 Base = NULL;
	Base = C.DriverCheck;
	return Base;
}
inline bool WriteMemory(UINT_PTR WriteAddr, UINT_PTR Buffer, SIZE_T Size)
{
	mtx.lock();
	Omen c;
	c.WriteAddr = WriteAddr;
	c.ProcessID = ProcessID;
	c.Request = Request::WriteMemoryK;
	c.SecureCheck = Request::SecurityCheck;
	c.Buffer = (void*)Buffer;
	c.WriteSize = Size;

	SendOveride(&c);
	mtx.unlock();
	return true;
}
inline bool ReadBuffer(UINT_PTR WriteAddr, void* Buffer, SIZE_T Size)
{
	mtx.lock();
	Omen c;
	c.Request = Request::ReadMemory;
	c.SecureCheck = Request::SecurityCheck;
	c.ProcessID = ProcessID;
	c.ReadSize = Size;
	c.ReadAddr = WriteAddr;
	c.Value = Buffer;

	SendOveride(&c);
	mtx.unlock();

	return true;
}
template<typename S>
inline bool write(UINT_PTR WriteAddr, const S& Value)
{
	return WriteMemory(WriteAddr, (UINT_PTR)&Value, sizeof(S));
}

inline bool ReadString(UINT_PTR WriteAddr, void* Buffer, SIZE_T Size)
{
	mtx.lock();
	Omen c;
	c.Request = Request::ReadMemory;
	c.SecureCheck = Request::SecurityCheck;
	c.ProcessID = ProcessID;
	c.ReadSize = Size;
	c.ReadAddr = WriteAddr;
	c.Value = Buffer;

	SendOveride(&c);
	mtx.unlock();

    return true;
}
inline std::wstring read_uni(uint64_t address) {
    wchar_t buffer[1024 * sizeof(wchar_t)];

    ReadString(address, &buffer, 1024 * sizeof(wchar_t));

    return std::wstring(buffer);
}
inline std::string read_nat(uint64_t address) {
	wchar_t buffer[1024 * sizeof(wchar_t)];

	ReadString(read<uint64_t>(address), &buffer, 1024 * sizeof(wchar_t));


}
template <typename Type>
Type read_chain(uint64_t address, std::vector<uint64_t> chain) {
	uint64_t current = address;
	for (int i = 0; i < chain.size() - 1; i++) {
		current = read<uint64_t>(current + chain[i]);
	}
	return read<Type>(current + chain[chain.size() - 1]);
}