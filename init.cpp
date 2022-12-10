#pragma once
#include "common.hpp"

auto c_init::cheat() -> bool
{

	ProcessID = (int)GetProcessId2("RustClient.exe");

	u_base = GetModuleBase("UnityPlayer.dll");
	g_base = GetModuleBase("GameAssembly.dll");

	std::cout << ProcessID << "\n";
	std::cout << u_base << "\n";
	std::cout << g_base << "\n";


	return true;
}

auto c_init::local_player() ->uintptr_t
{
	uintptr_t local_player_pointer_1 = read<uintptr_t>(g_base + 0x314CC88); //base network
	uintptr_t local_player_pointer_2 = read<uintptr_t>(local_player_pointer_1 + 0xB8);
	uintptr_t local_player_pointer_3 = read<uintptr_t>(local_player_pointer_2 + 0x0);
	uintptr_t local_player_pointer_4 = read<uintptr_t>(local_player_pointer_3 + 0x10);
	uintptr_t local_player_pointer_5 = read<uintptr_t>(local_player_pointer_4 + 0x28);
	uintptr_t local_player_pointer_6 = read<uintptr_t>(local_player_pointer_5 + 0x18);
	return read<uintptr_t>(local_player_pointer_6 + 0x20);
}



