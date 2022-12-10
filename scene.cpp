#pragma once
#include "scene.hpp"
		  
void styles()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.Alpha = 1.0f;
		style.WindowPadding = ImVec2(0, 0);
		style.WindowMinSize = ImVec2(32, 32);
		style.WindowRounding = 0.0f;
		style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
		//style.ChildWindowRounding = 0.0f;
		style.FramePadding = ImVec2(4, 3);
		style.FrameRounding = 0.0f;
		style.ItemSpacing = ImVec2(8, 8);
		style.ItemInnerSpacing = ImVec2(8, 8);
		style.TouchExtraPadding = ImVec2(0, 0);
		style.IndentSpacing = 21.0f;
		style.ColumnsMinSpacing = 0.0f;
		style.ScrollbarSize = 6.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 0.0f;
		style.ButtonTextAlign = ImVec2(0.0f, 0.5f);
		style.DisplayWindowPadding = ImVec2(22, 22);
		style.DisplaySafeAreaPadding = ImVec2(4, 4);
		style.AntiAliasedLines = true;
		//style.AntiAliasedShapes = false;
		style.CurveTessellationTol = 1.f;
		style.WindowPadding = ImVec2(15, 15);
		style.FramePadding = ImVec2(2, 2);
		style.ItemInnerSpacing = ImVec2(8, 6);
		style.IndentSpacing = 25.0f;
		style.ScrollbarSize = 15.0f;
		style.ScrollbarRounding = 9.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 3.0f;
		style.Colors[ImGuiCol_Tab] = ImColor(255, 20, 147);
		style.Colors[ImGuiCol_Button] = ImColor(255, 20, 147);
		style.Colors[ImGuiCol_Text] = ImColor(255, 20, 147);
		style.Colors[ImGuiCol_TextDisabled] = ImColor(255, 20, 147);
		style.Colors[ImGuiCol_WindowBg] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_PopupBg] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_BorderShadow] = ImColor(25, 25, 112);
		style.Colors[ImGuiCol_FrameBg] = ImColor(25, 25, 112);
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(25, 25, 112);
		style.Colors[ImGuiCol_FrameBgActive] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_TitleBg] = ImColor(1.0f, 0.09f, 0.12f, 0.70f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(1.00f, 0.98f, 0.95f, 0.75f);
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_MenuBarBg] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(0.80f, 0.80f, 0.83f, 0.31f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(0.56f, 0.56f, 0.58f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(0.06f, 0.05f, 0.07f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImColor(255, 20, 147);
		style.Colors[ImGuiCol_SliderGrab] = ImColor(0.80f, 0.80f, 0.83f, 0.31f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImColor(0.06f, 0.05f, 0.07f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImColor(255, 20, 147);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(255, 20, 147);
		style.Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_Header] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImColor(0.56f, 0.56f, 0.58f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImColor(0.06f, 0.05f, 0.07f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImColor(0.40f, 0.39f, 0.38f, 0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImColor(0.25f, 1.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImColor(0.40f, 0.39f, 0.38f, 0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImColor(0.25f, 1.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImColor(0.25f, 1.00f, 0.00f, 0.43f);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImColor(1.00f, 0.98f, 0.95f, 0.73f);
		style.Colors[ImGuiCol_Separator] = ImColor(0.2f, 0.4f, 0.9f, 1.00f);
		style.Alpha = 1.0f;
		style.WindowRounding = 5;
		style.FramePadding = ImVec2(4, 3);
		style.WindowPadding = ImVec2(2, 1);
		style.ItemInnerSpacing = ImVec2(4, 4);
		style.ItemSpacing = ImVec2(15, 20);
		style.FrameRounding = 12;
		style.ScrollbarSize = 2.f;
		style.ScrollbarRounding = 12.f;
		style.PopupRounding = 2.f;
		style.FrameRounding = 4.4f;
		style.Colors[ImGuiCol_CheckMark] = ImColor(25, 25, 112);
		style.Colors[ImGuiCol_TitleBg] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImColor(25, 25, 112);
		style.Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(25, 25, 112);
		style.Colors[ImGuiCol_FrameBg] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImColor(25, 25, 112);
		style.Colors[ImGuiCol_SliderGrabActive] = ImColor(25, 25, 112);
		style.Colors[ImGuiCol_Header] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImColor(255, 20, 147);
	}

	ImGuiStyle* style = &ImGui::GetStyle();
	{
		style->WindowBorderSize = 1.0f;
		style->ChildBorderSize = 1.0f;

		style->FramePadding = ImVec2(4, 0);

		style->WindowTitleAlign = ImVec2(.5, .5);
	}
}
auto wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> bool
{
	return true;
}
auto init_ui() -> void  
{

	//ImGui::StyleColorsDark();
	styles();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImFontConfig font_config;
	font_config.OversampleH = 1; //or 2 is the same
	font_config.OversampleV = 1;
	font_config.PixelSnapH = 1;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x044F, // Cyrillic
		0,
	};
	structure.c_font_defult = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 17.f);
	structure.c_font_icon = io.Fonts->AddFontFromMemoryTTF((void*)iconfont, sizeof(iconfont), 30, &font_config, ranges);
}

auto create_scene() -> void 
{
	// create cheat 
	cheat->create();
	
	// draw gui 
	gui->draw();	
}

void espThread()
{
	//if (vars.esp)
	gui->drawESPOverlay();
		
}

std::string gen_random(const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	std::string tmp_s;
	tmp_s.reserve(len);

	for (int i = 0; i < len; ++i) {
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return tmp_s;
}

void c_scene::create()
{
	Sleep(1000);
	GAPI::MakeWindow("Swoop", "Swoop", wnd_proc, init_ui, create_scene, espThread, &vars.g_open, &vars.g_menu_key);
}

