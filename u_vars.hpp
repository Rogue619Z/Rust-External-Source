#pragma once
#ifndef u_vars_hpp
#define u_vars_hpp

class c_vars
{
public:
	// menu
	bool g_open = true;
	int g_menu_key = VK_INSERT;
	int walkbind = 0;
	int longbind = 0;
	int speedbind = 0;
	int mountbind = 0;
	int zoombind = 0;
	int desyncbind = 0;
	int flyhackbind = 0;
	bool rapidfire = false;
	bool mounted = false;
	float rapid_val = 0.01;
	int rWidth;
	int rHeight;
	float health_color[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
	float esp_color[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
	float corner_color[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
	float drawColor_skeleton[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
	float drawColor_crosshair[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
	float drawColor_name[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
	float drawColor_weapon[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
	bool bone_esp = false;
	float draw_coolcolor[4] = { 1.f, 1.f, 1.f, 0.15f };
	// cheat
	bool no_recoil = false;
	bool admin_flags = false;
	bool doublejump = true;
	bool walkonwater = false;
	bool spyderman = false;
	bool always_shoot = false;
	bool antiaim = false;
	bool flyhack = false;
	bool longeject = false;
	bool thickbullet = false;
	bool instacompound = false;
	bool speedhack = false;
	bool nospread = false;
	bool mountfire = false;
	bool omnisprint = false;
	bool set_zoom = false;
	bool instanteoka = false;
	bool desync = false;
	bool fastbow = false;
	bool aimbot = false;
	bool silentaim = false;
	bool prediction = true;

	int aimbotkey = 0;
	float aimbotDist = 300.f;
	bool fov = false;
	bool skychanger = false;
	float fovamount = 120;
	float skycolor = 1.0f;

	bool esp = false;
	bool corner = false;
	bool boxesp = false;
	bool healthesp = false;
	bool nameesp = false;
	bool weaponesp = false;
	bool head = false;
	bool chest = false;
	bool pelvis = false;
	bool tdtdbox = false;
	bool tdbox = false;
	bool interactive_esp = false;
	

	const char* bone[4] = {
		"Head",
		"Chest",
		"Arms",
		"Legs",
	};

	const char* aimtype[2] = {
		"memory",
		"silent"
	};
	bool tracers = false;
	bool autooo = false;
	bool shotty_ns = false;

	int aim_on = 0;
	float fovcolor[4] = { 3.10f, 0.09f, 2.12f, 1.00f};
	int dist;
	int max_distance = 400;
	float neckamount = 0.0f;
	float fov_amount = 90;
	float gravity_amount = 2.5f;
	float fatbulletamount = 1.f;
	bool enabled = false;
	bool radar = false;
	bool beltesp = false;
	bool nodeesp = false;
	bool stashesp = false;
	bool scientistesp = false;
	bool peekassist = false;
	bool crosshair = false;
	bool chams = false;
	bool stone = false;
	bool metal = false;
	bool sulfur = false;
	bool hemp = false;
	
	
};
inline c_vars vars; 

#endif // !u_vars_hpp
