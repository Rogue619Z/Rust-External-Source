#define IMGUI_DEFINE_MATH_OPERATORS
#include "esp.hpp"
#include "common.hpp"

#pragma region Drawing Funcs
ImU32 __fastcall FtIM(float* color) {
	return ImGui::ColorConvertFloat4ToU32(ImVec4(color[0], color[1], color[2], color[3]));
}

struct Color {
public:
	float r, g, b, a;

	Color(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

void __fastcall Text(ImVec2 pos, std::string strText, ImColor color, bool outline, ImFont* font, float fontSize)
{
	ImGuiContext& g = *GImGui;

	const char* text_end = strText.c_str() + strlen(strText.c_str());
	const char* text_display_end = ImGui::FindRenderedTextEnd(strText.c_str(), text_end);

	if (fontSize == 0.f) fontSize = g.Font->FontSize;

	if (outline) {
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos - ImVec2(1, 0), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos - ImVec2(0, 1), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos + ImVec2(1, 0), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos + ImVec2(0, 1), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
	}

	ImGui::GetWindowDrawList()->AddText(font, fontSize, pos, color, strText.c_str(), NULL, 0.0f, NULL);
}
void __fastcall DrawFilledRect(float x, float y, float w, float h, ImVec4 color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), NULL, NULL);
}
void __fastcall Line(ImVec2 pos, ImVec2 size, ImU32 color, float thickness)
{
	ImGui::GetWindowDrawList()->AddLine(pos, size, color, thickness);
}
float normalize_angle(float angle)
{
	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return angle;
}
Vector2 RotatePoint(Vector2 pointToRotate, Vector2 centerPoint, float angle, bool angleInRadians = false)
{
	float rad = (normalize_angle(angle) * static_cast<float>((M_PI / 180.0f)));
	float s = -sin(rad);
	float c = cos(rad);
	pointToRotate.x -= centerPoint.x;
	pointToRotate.y -= centerPoint.y;
	float xnew = pointToRotate.x * c - pointToRotate.y * s;
	float znew = pointToRotate.x * s + pointToRotate.y * c;
	pointToRotate.x = xnew + centerPoint.x;
	pointToRotate.y = znew + centerPoint.y;
	return pointToRotate;
}

void _fastcall DrawPlayerHealth(uint64_t player, float actualhealth)
{
	auto health = actualhealth;
	if (health > 100)
		health = 99;
	Vector3 head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.2, 0));
	Vector3 feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
	Vector2 tempFeet, tempHead;
	if (Utils::WorldToScreen(head, tempHead) && Utils::WorldToScreen(feet, tempFeet)) {
		float height = (tempHead.y - tempFeet.y);
		float width = height / 4.0f;

		float Entity_x = tempFeet.x + width;
		float Entity_y = tempFeet.y;
		float flBoxes = std::ceil(health / 10.f);
		float flX = Entity_x - 4; float flY = Entity_y;
		float flHeight = height / 10.f;
		float flMultiplier = 12 / 360.f; flMultiplier *= flBoxes - 1;
		ImColor ColHealth = ImColor(1, 255, 1);

		Text(ImVec2(flX, flY), "hp: " + std::to_string((int)actualhealth), ImColor(255, 255, 255, 255), true, structure.c_font_defult, 0.f);

		DrawFilledRect(flX + 1, flY, 2, flHeight * flBoxes + 3, ColHealth);
		DrawFilledRect(flX, flY, 4, height + 2, ImColor(80, 80, 80, 160));
	}
}
void _fastcall DrawPlayerWeapon(uint64_t player, std::string buffer)
{
	Vector3 Head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.23, 0));
	Vector3 Feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
	Vector2 tempFeet;

	wchar_t res[256];
	std::string final = buffer;
	if (Utils::WorldToScreen(Feet, tempFeet)) {
		auto text_size = ImGui::CalcTextSize(final.c_str());
		Text(ImVec2(tempFeet.x - text_size.x / 2, (tempFeet.y + 30) - text_size.y), final, ImColor(255, 255, 255), true, structure.c_font_defult, 0.f);
	}
}
void _fastcall DrawPlayerName(uint64_t player, std::string buffer, int distance) {
	Vector3 Head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(-0.3, 0.4, 0));
	Vector3 Feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
	Vector2 tempFeet;
	Vector2 tempHead;

	wchar_t res[256];
	std::string full_str = buffer + " - " + std::to_string(distance) + "m";
	//std::string full_str = buffer;

	if (Utils::WorldToScreen(Feet, tempFeet) && Utils::WorldToScreen(Head, tempHead)) {
		auto text_size = ImGui::CalcTextSize(full_str.c_str());
		Text(ImVec2(tempFeet.x - text_size.x / 2, tempHead.y - text_size.y), full_str, ImColor(255, 255, 255), true, structure.c_font_defult, 0.f);
	}
}
void __fastcall DrawCornerBox(ImVec2 pos, ImVec2 size, ImColor color)
{
	float lineW = (size.x / 5);
	float lineH = (size.y / 6);
	float lineT = 1;
	auto overlay = ImGui::GetWindowDrawList();
	{
		overlay->AddLine(ImVec2(pos.x - lineT, pos.y - lineT), ImVec2(pos.x + lineW, pos.y - lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x - lineT, pos.y - lineT), ImVec2(pos.x - lineT, pos.y + lineH), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x - lineT, pos.y + size.y - lineH), ImVec2(pos.x - lineT, pos.y + size.y + lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x - lineT, pos.y + size.y + lineT), ImVec2(pos.x + lineW, pos.y + size.y + lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x + size.x - lineW, pos.y - lineT), ImVec2(pos.x + size.x + lineT, pos.y - lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x + size.x + lineT, pos.y - lineT), ImVec2(pos.x + size.x + lineT, pos.y + lineH), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x + size.x + lineT, pos.y + size.y - lineH), ImVec2(pos.x + size.x + lineT, pos.y + size.y + lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x + size.x - lineW, pos.y + size.y + lineT), ImVec2(pos.x + size.x + lineT, pos.y + size.y + lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x, pos.y + lineH), color, 1.f);
		overlay->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x + lineW, pos.y), color, 1.f);
		overlay->AddLine(ImVec2(pos.x + size.x - lineW, pos.y), ImVec2(pos.x + size.x, pos.y), color, 1.f);
		overlay->AddLine(ImVec2(pos.x + size.x, pos.y), ImVec2(pos.x + size.x, pos.y + lineH), color, 1.f);
		overlay->AddLine(ImVec2(pos.x, pos.y + size.y - lineH), ImVec2(pos.x, pos.y + size.y), color, 1.f);
		overlay->AddLine(ImVec2(pos.x, pos.y + size.y), ImVec2(pos.x + lineW, pos.y + size.y), color, 1.f);
		overlay->AddLine(ImVec2(pos.x + size.x - lineW, pos.y + size.y), ImVec2(pos.x + size.x, pos.y + size.y), color);
		overlay->AddLine(ImVec2(pos.x + size.x, pos.y + size.y - lineH), ImVec2(pos.x + size.x, pos.y + size.y), color, 1.f);
	}
}
void __fastcall DrawBoxx(ImVec2 pos, ImVec2 size, ImColor color)
{
	const ImRect rect_bb(pos, pos + size);

	ImGui::GetWindowDrawList()->AddRect(rect_bb.Min - ImVec2(1, 1), rect_bb.Max + ImVec2(1, 1), FtIM(vars.esp_color), 0.0f, 15, 1);
	ImGui::GetWindowDrawList()->AddRect(rect_bb.Min + ImVec2(1, 1), rect_bb.Max - ImVec2(1, 1), FtIM(vars.esp_color), 0.0f, 15, 1);
	ImGui::GetWindowDrawList()->AddRect(rect_bb.Min, rect_bb.Max, color, 0.0f, 15, 1);
}
void __fastcall DrawBox(uint64_t player) {

	Vector3 head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.2, 0));
	Vector3 feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
	Vector2 tempFeet, tempHead;

	if (Utils::WorldToScreen(head, tempHead) && Utils::WorldToScreen(feet, tempFeet)) {
		float height = (tempHead.y - tempFeet.y);
		float width = height / 3.0f;

		float Entity_x = tempFeet.x - width;
		float Entity_y = tempFeet.y;
		float Entity_w = height / 2;
		DrawCornerBox(ImVec2(Entity_x, Entity_y), ImVec2(Entity_w, height), FtIM(vars.corner_color));

	}
}
void  DrawSkeleton(uint64_t player) {
	float drawColor_skeleton[4] = { 1.f, 1.f, 1.f, 1.f };

	std::array<BonesList, 15> Bones = {
		r_foot, l_knee, l_hip,
		l_foot, r_knee, r_hip,
		spine1, neck, head,
		l_upperarm, l_forearm, l_hand,
		r_upperarm, r_forearm, r_hand

	}; std::array<Vector2, Bones.size()> BonesPos;

	for (int i = 0; i < BonesPos.size(); ++i) {
		if (!(Utils::WorldToScreen(Utils::GetBonePosition(player, Bones[i]), BonesPos.at(i)))) continue;
	}

	for (int j = 0; j < BonesPos.size(); j += 3) {
		Line({ BonesPos[j].x, BonesPos[j].y }, { BonesPos[j + 1].x, BonesPos[j + 1].y }, FtIM(vars.drawColor_skeleton), 1.0f);
		Line({ BonesPos[j + 1].x, BonesPos[j + 1].y }, { BonesPos[j + 2].x, BonesPos[j + 2].y }, FtIM(vars.drawColor_skeleton), 1.0f);
	}

	Line({ BonesPos[2].x, BonesPos[2].y }, { BonesPos[6].x, BonesPos[6].y }, FtIM(vars.drawColor_skeleton), 1.0f);
	Line({ BonesPos[5].x, BonesPos[5].y }, { BonesPos[6].x, BonesPos[6].y }, FtIM(vars.drawColor_skeleton), 1.0f);
	Line({ BonesPos[9].x, BonesPos[9].y }, { BonesPos[7].x, BonesPos[7].y }, FtIM(vars.drawColor_skeleton), 1.0f);
	Line({ BonesPos[12].x, BonesPos[12].y }, { BonesPos[7].x, BonesPos[7].y }, FtIM(vars.drawColor_skeleton), 1.0f);
}
void __fastcall DrawBox2(uint64_t player) {

	Vector3 head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.2, 0));
	Vector3 feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
	Vector2 tempFeet, tempHead;

	if (Utils::WorldToScreen(head, tempHead) && Utils::WorldToScreen(feet, tempFeet)) {
		float height = (tempHead.y - tempFeet.y);
		float width = height / 4.0f;

		float Entity_x = tempFeet.x - width;
		float Entity_y = tempFeet.y;
		float Entity_w = height / 2;
		DrawBoxx(ImVec2(Entity_x, Entity_y), ImVec2(Entity_w, height), ImColor(255, 255, 255, 1));

	}
}

std::string prevItem;
uintptr_t prevPlayer;

#pragma endregion
void TargetBelt(uintptr_t player, std::string playerName, bool textDisabled)
{
	float x = GetSystemMetrics(SM_CXSCREEN) - 1000, y = 120;
	ImGui::GetWindowDrawList()->AddRectFilled({ x, y - 20.0f }, ImVec2(x + 200, y + 20), ImColor(25, 25, 25));
	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + 200, y + 102), ImColor(25, 25, 25));
	if (!textDisabled)
	{
	Text(ImVec2(x + 7.0f, y - 16.0f), playerName, ImColor(255, 255, 255), false, structure.c_font_defult, 0.f);

	int active_weapon_id = read<int>(player + 0x5D0); //private uint clActiveItem;
	uint64_t items = read_chain<uint64_t>(player, { (uint64_t)0x690, (uint64_t)0x28, (uint64_t)0x38, 0x10 }); //public PlayerInventory inventory;
	//std::cout << "Held weapon: found :" <<  items << std::endl;
	

		for (int items_on_belt = 0; items_on_belt <= 5; items_on_belt++)
		{
			uint64_t item = read<uint64_t>(items + 0x20 + (items_on_belt * 0x8));
			HeldItem Beltitem = HeldItem(item);
			std::string itemName = Beltitem.GetItemName();
			if (itemName != "")
			{
				if (itemName != prevItem || player != prevPlayer)
				{
					Text(ImVec2(x + 7.0f, y + 7.0f), itemName, ImColor(255, 255, 255), false, structure.c_font_defult, 0.f);
					y += 15;
					prevItem = itemName;
					prevPlayer = player;
				}
			}

		}
		prevItem = "";
	}
}

void Crosshair(ImVec2 targetPos)
{
		Text(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2), "+", ImColor(255, 255, 255), false, structure.c_font_defult, 20.f);
		Text(targetPos, "+", ImColor(255, 255, 255), false, structure.c_font_defult, 20.f);
}

void c_visuals::DrawRadar()
{
	if (vars.radar)
	{
		float x = GetSystemMetrics(SM_CXSCREEN) - 175, y = 200;

		ImGui::GetWindowDrawList()->AddLine(ImVec2{ x, y - 150 }, ImVec2{ x, y + 150 }, ImColor{ 0.f, 0.f, 0.f, 1.f });
		ImGui::GetWindowDrawList()->AddLine(ImVec2{ x - 150, y }, ImVec2{ x + 150, y }, ImColor{ 0.f, 0.f, 0.f, 1.f });
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2{ x - 1, y - 1 }, ImVec2{ x + 2, y + 2 }, 0xFFFFFFFF, 0.5f);

		Vector2 m_vecLocal = localPlayer2.getPosition2D();
		Vector2 m_angLocal = localPlayer2.getBodyAngles();
		for (auto i = 0; i < player_list->size(); i++)
		{
			std::unique_ptr<baseEntity> nn = std::make_unique<baseEntity>(player_list->at(i));
			const Vector3 position = nn->getPosition();

			if (nn->isSleeping())
				continue;

			Vector2 m_vecEnemy{ position.x, position.z };
			m_vecEnemy = m_vecLocal - m_vecEnemy;

			float m_flDistance = m_vecEnemy.length();
			m_vecEnemy = m_vecEnemy.normalized();
			m_flDistance = min(150.f, m_flDistance);
			m_vecEnemy *= m_flDistance;
			m_vecEnemy = RotatePoint(m_vecEnemy, { 0, 0 }, 360.f - m_angLocal.y, true);
			{
				ImColor color = ImColor{ 3.10f, 0.09f, 2.12f, 1.00f };
				ImGui::GetWindowDrawList()->AddRectFilled(ImVec2{ x - m_vecEnemy.x - 2, y + m_vecEnemy.y - 2 }, ImVec2{ x - m_vecEnemy.x + 2, y + m_vecEnemy.y + 2 }, color, 0.5f);
			}
		}
	}
	
}

void DoChams(uintptr_t player, uintptr_t entity)
{
	DWORD64 ObjManager = read<DWORD64>(u_base + 0x17C1F18); if (!ObjManager) return;
	DWORD64 Obj = read<DWORD64>(ObjManager + 0x8); (Obj && (Obj) != read<DWORD64>(ObjManager)); Obj = read<DWORD64>(Obj + 0x8);
	DWORD64 GameObject = read<DWORD64>(Obj + 0x10);
	DWORD64 ObjClass = read<DWORD64>(GameObject + 0x30);
	DWORD64 Entity1 = read<DWORD64>(ObjClass + 0x18);
	DWORD64 Dome = read<DWORD64>(Entity1 + 0x28);

	auto player_model = read<uintptr_t>(player + 0x4C0);
	auto set = read<uintptr_t>(player_model + 0x198);

	auto skins = read<uintptr_t>(set + 0x18);
	auto size = read<int>(skins + 0x18);

	uintptr_t inventory = read<uintptr_t>(player + 0x690);           // | inventory          | PlayerInventory                | 0x690  |
	uintptr_t containerWear = read<uintptr_t>(inventory + 0x30);                 // | containerWear	    | ItemContainer	                 | 0x30   |
	uintptr_t itemList = read<uintptr_t>(containerWear + 0x38);                  // | itemList	        | List(Item)	                 | 0x38   |
	int itemListSize = read<int>(itemList + 0x18);                               // | size               | int    	                     | 0x18   |
	uintptr_t items = read<uintptr_t>(itemList + 0x10);                          // | items              | Items                          | 0x10   |   
	for (int i = 0; i < itemListSize; i++) {                                             // |                    |                                |        |
		uintptr_t item = read<uintptr_t>(items + (0x20 + (i * 0x8)));            // | item               | Items[]                        | 0x20   |
		uintptr_t itemDefinition = read<uintptr_t>(item + 0x20);                 // | info	            | ItemDefinition	             | 0x20   |
		uintptr_t itemModWearable = read<uintptr_t>(itemDefinition + 0x100);     // |(ItemModWearable)   | ItemModWearable	             | 0x100  |                  
		write<int>(itemModWearable + 0x48, 64);             // | occlusionType	    | UIBlackoutOverlay.blackoutType | 0x48   |
	}

	if (set != 0)
	{

		for (int itr = 0; itr <= size; itr++)
		{
			auto skin = read<uintptr_t>(skins + 0x18 + (itr * 0x8));
			if (!skin)
				continue;

			auto components = read<uintptr_t>(Dome + 0xA8); // heres the material,(sky, CHECKED; atmosphere, cloud material
			if (!components)
				continue;

			auto scattering = read<uintptr_t>(components + 0x1A0);
			if (!scattering)
				continue;

			auto material = read<uintptr_t>(scattering + 0x78);
			if (!material)
				continue;

			write<uintptr_t>(skin + 0x68, material);
			write<uintptr_t>(skin + 0x70, material);
			write<uintptr_t>(skin + 0x78, material);
		}
	}

}

void bullet_tracers()
{



}

void __fastcall c_visuals::ESP()
{

	//TargetBelt(NULL, "N\A", true);
	//Vector2 CrosshairPos;
	//Utils::WorldToScreen(Utils::GetBonePosition(aimbot->getTarget(), BonesList::head), CrosshairPos);
	DrawRadar();

	for (auto i = 0; i < player_list->size(); i++)
	{
		std::unique_ptr<baseEntity> BPlayer = std::make_unique<baseEntity>(player_list->at(i));

		if (read<bool>(BPlayer->playerModel + 0x289))
		{
			continue;
		}

		if (!BPlayer->IsInView()) continue;

		if (BPlayer->isSleeping()) continue;

		auto dist = (int)Math::Distance(&localPlayer2.position, &BPlayer->position);

		if (dist > vars.max_distance) continue;

		if (aimbot->getTarget() == BPlayer->player && vars.beltesp)
		{
			TargetBelt(BPlayer->player, BPlayer->getName(), false);
		}
		if (vars.esp == true && vars.boxesp)
		{
			DrawBox2(BPlayer->player);
		}
		if (vars.esp == true && vars.corner)
		{
			DrawBox(BPlayer->player);
		}
		if (vars.esp == true && vars.healthesp)
		{
			DrawPlayerHealth(BPlayer->player, BPlayer->health);
		}
		if (vars.esp == true && vars.nameesp)
		{
			DrawPlayerName(BPlayer->player, BPlayer->getName(), dist);
		}
		if (vars.esp == true && vars.weaponesp)
		{
			DrawPlayerWeapon(BPlayer->player, BPlayer->getHeldItem().GetItemName());
		}
		if (vars.esp == true && vars.bone_esp)
		{
			DrawSkeleton(BPlayer->player);
		}
		if (vars.esp == true && vars.chams)
		{
			std::thread chams(DoChams, BPlayer->player, BPlayer->baseentity);
			chams.detach();
		}

	}

}