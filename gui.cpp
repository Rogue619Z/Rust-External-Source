#pragma once
#ifndef gui_cpp
#define safe_str
#define gui_cpp
#include "gui.hpp"
int tab = 0;

ImU32 rainbow()
{
    auto pos = ImGui::GetWindowPos();
    auto size = ImGui::GetWindowSize();
    float rainbowSpeed = 0.001;
    static float staticHue = 0;

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    staticHue -= rainbowSpeed;
    if (staticHue < -1.f) staticHue += 1.f;
    for (int i = 0; i < 3; i++)
    {
        float hue = staticHue + (1.f / (float)3) * i;
        if (hue < 0.f) hue += 1.f;
        ImColor cRainbow = ImColor::HSV(hue, 1.f, 1.f);
        draw_list->AddRectFilled(ImVec2(pos.x, pos.y + 0), ImVec2(pos.x + 545, pos.y + 500), ImColor(255, 20, 147));
    }
    return rainbowSpeed;
}
ImColor rainbow_color()
{
    float rainbowSpeed = 0.002;
    static float staticHue = 1;
    staticHue -= rainbowSpeed;
    ImColor cRainbow;
    for (int i = 0; i < 3; i++)
    {
        float hue = staticHue + (1.f / (float)3) * i;
        if (hue < 0.f) hue += .1f;
        cRainbow = ImColor::HSV(hue, 1.f, 1.f);
        std::cout << std::to_string(hue) + "\n";
        if (hue < 1.f) hue += 0.0f;
    }
    return cRainbow;
}

void check()
{
    ImGui::SetCursorPos(ImVec2(5, 510));
    ImColor(255, 20, 147);
    if (ImGui::tab("aimbot", 0 == tab)) tab = 0;
    ImColor(255, 20, 147);
    ImGui::SetCursorPos(ImVec2(85, 510));
    ImColor(255, 20, 147);
    if (ImGui::tab("player esp", 1 == tab)) tab = 1;
    ImGui::SetCursorPos(ImVec2(165, 510));
    ImColor(255, 20, 147);
    if (ImGui::tab("world esp", 2 == tab)) tab = 2;
    ImGui::SetCursorPos(ImVec2(245, 510));
    ImColor(255, 20, 147);
    if (ImGui::tab("weapon", 3 == tab)) tab = 3;
    ImGui::SetCursorPos(ImVec2(310, 510));
    if (ImGui::tab("misc", 4 == tab)) tab = 4; 
    ImGui::SetCursorPos(ImVec2(375, 510));
    if (ImGui::tab("colors", 5 == tab)) tab = 5;

}

ImU32 __fastcall FtIM2(float* color) {
    return ImGui::ColorConvertFloat4ToU32(ImVec4(color[0], color[1], color[2], color[3]));
}

void c_gui::draw()
{
    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF,
        0x0400, 0x044F,
        0,
    };
    ImFontConfig font_config;
    font_config.OversampleH = 1;
    font_config.OversampleV = 1;
    font_config.PixelSnapH = 1;
    ImFont* icon = nullptr;
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = ImGui::GetStyle().Colors;
    icon = io.Fonts->AddFontFromMemoryTTF((void*)icon, sizeof(icon), 25, &font_config, ranges);

    if (vars.fov == true)
    {
        ImGui::Begin("##CIRCLE", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);
        auto draw = ImGui::GetBackgroundDrawList();
        draw->AddCircle(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2), vars.fovamount, FtIM2(vars.fovcolor), 100, 1.0f);
        ImGui::End();
    }
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    POINT mPos;
    GetCursorPos(&mPos);
    ImVec2 window_size = ImVec2(450, 570);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowPos(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2 - window_size.x / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - window_size.y / 2), ImGuiCond_Once);


    if (vars.g_open)
    {


        ImGui::Begin("##MENU", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        {
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            auto pos = ImGui::GetWindowPos();
            auto size = ImGui::GetWindowSize();
            bool isHovering = mPos.x >= pos.x && mPos.y >= pos.y && mPos.x <= (pos.x + size.x) && mPos.y <= (pos.y + size.y);

            if (isHovering)
                GAPI::EnableInput();
            else if (!isHovering)
                GAPI::DisableInput();

            ImGui::SetNextWindowBgAlpha(1.f);
            draw_list->AddRectFilled(pos, ImVec2(pos.x + 545, pos.y + 355), ImColor(255, 20, 147), 9);
           draw_list->AddRectFilled(pos, ImVec2(pos.x + 545, pos.y + 355), ImGui::GetColorU32(ImGuiCol_WindowBg), 9);
           draw_list->AddRectFilled(ImVec2(pos.x, pos.y + 30), ImVec2(pos.x + 130, pos.y + 355), ImGui::GetColorU32(ImGuiCol_TabBar), 9, 4);
            draw_list->AddLine(ImVec2(pos.x, pos.y + 8), ImVec2(pos.x + 545, pos.y + 8), ImColor(255, 20, 147));

            check();

            switch (tab)
            {
                break;
            case 0: //aimbot

                ImGui::SetCursorPos(ImVec2(4, 4));
                ImGui::BeginChild("    ", ImVec2(440, 500));
                {
                
                        ImGui::SetCursorPos(ImVec2(13, 25));
                        ImGui::Checkbox("aim  ", &vars.aimbot);
                        ImGui::SetCursorPos(ImVec2(13, 45));
                        ImGui::Checkbox("silent  ", &vars.silentaim);
                        ImGui::SetCursorPos(ImVec2(13, 65));
                        ImGui::Checkbox("fov circle  ", &vars.fov); 
                        ImGui::SetCursorPos(ImVec2(90, 65));
                        ImGui::SetNextItemWidth(270);
                        ImGui::SliderFloat("##fovamount", &vars.fovamount, 30, 360); ImGui::SameLine(); ImGui::ColorEdit4(safe_str(""), vars.fovcolor, ImGuiColorEditFlags_NoInputs);
                        if (vars.fovcolor) 
                        {

                        }
                            ImGui::SetCursorPos(ImVec2(90, 25));
                            ImGui::SetNextItemWidth(200);
                            ImGui::SetCursorPos(ImVec2(13, 85));
                            ImGui::Combo("type", &vars.aim_on, vars.aimtype, IM_ARRAYSIZE(vars.aimtype));
                            ImGui::SetCursorPos(ImVec2(325, 25));
                            ImGui::KeyBind("aim key", vars.aimbotkey, ImVec2(50, 15));
               
                        

                    
                    
                }
                ImGui::EndChild();
                break;
            case 1:
                ImGui::SetCursorPos(ImVec2(4, 4));
                ImGui::BeginChild("        ", ImVec2(440, 500)); // player esp
                {
                    ImGui::SetCursorPos(ImVec2(13, 25));
                    ImGui::Checkbox("2d BOX  ", &vars.boxesp); 
                    ImGui::SetCursorPos(ImVec2(13, 45));
                    ImGui::Checkbox("2D CORNER  ", &vars.corner);
                    ImGui::SetCursorPos(ImVec2(13, 65));
                    ImGui::Checkbox("2D 3D BOX  ", &vars.tdtdbox);
                    ImGui::SetCursorPos(ImVec2(13, 85));
                    ImGui::Checkbox("3D BOX  ", &vars.tdbox);
                    ImGui::SetCursorPos(ImVec2(13, 105));
                    ImGui::Checkbox("NAME  ", &vars.nameesp);
                    ImGui::SetCursorPos(ImVec2(13, 125));
                    ImGui::Checkbox("HEALTH  ", &vars.healthesp);
                    if (vars.health_color)
                    {

                    }
                    ImGui::SetCursorPos(ImVec2(13, 145));
                    ImGui::Checkbox("WEAPON  ", &vars.weaponesp);
                    if (vars.drawColor_weapon)
                    {

                    }
                    ImGui::SetCursorPos(ImVec2(13, 165));
                    ImGui::Checkbox("CHAMS  ", &vars.chams);
                    ImGui::SetCursorPos(ImVec2(13, 185));
                    ImGui::SliderInt("distance  ", &vars.max_distance, 0, 400);

                }
                ImGui::EndChild();
          
                       

                   
         
                break;
            case 2:

                ImGui::SetCursorPos(ImVec2(4, 4));
                ImGui::BeginChild("       ", ImVec2(440, 500)); // world esp
                {

                    ImGui::SetCursorPos(ImVec2(13, 25));
                    ImGui::Checkbox("RADAR ESP ", &vars.radar);
                    ImGui::SetCursorPos(ImVec2(13, 45));
                    ImGui::Checkbox("NODE ESP  ", &vars.nodeesp);
                    ImGui::SetCursorPos(ImVec2(13, 65));
                    ImGui::Checkbox("STONE ESP ", &vars.stone);
                    ImGui::SetCursorPos(ImVec2(13, 85));
                    ImGui::Checkbox("METAL ESP ", &vars.sulfur);
                    ImGui::SetCursorPos(ImVec2(13, 105));
                    ImGui::Checkbox("STASH ESP  ", &vars.stashesp);
                    ImGui::SetCursorPos(ImVec2(13, 125));
                    ImGui::Checkbox("HEMP ESP  ", &vars.hemp);
                    ImGui::SetCursorPos(ImVec2(13, 145));
                    ImGui::Checkbox("BOT ESP ", &vars.scientistesp);
                }
                break;
            case 3:

                ImGui::SetCursorPos(ImVec2(4, 4));
                ImGui::BeginChild("      ", ImVec2(440, 500)); // weapon tab
                {
                    ImGui::SetCursorPos(ImVec2(13, 25));
                    ImGui::Checkbox("NO RECOIL  ", &vars.no_recoil);
                    ImGui::SetCursorPos(ImVec2(13, 45));
                    ImGui::Checkbox("NO SPREAD  ", &vars.nospread);
                    ImGui::SetCursorPos(ImVec2(13, 65));
                    ImGui::Checkbox("FAT BULLET  ", &vars.thickbullet);
                    ImGui::SetCursorPos(ImVec2(13, 85));
                    ImGui::Checkbox("COOL EOKA  ", &vars.instanteoka);
                    ImGui::SetCursorPos(ImVec2(13, 105));
                    ImGui::Checkbox("AUTO  ", &vars.autooo);
                    ImGui::SetCursorPos(ImVec2(13, 125));
                    ImGui::Checkbox("RAPID FIRE  ", &vars.rapidfire);
                    ImGui::SetCursorPos(ImVec2(13, 145));
                    ImGui::Checkbox("SHOTTY NO SPREAD  ", &vars.shotty_ns);
                    ImGui::SetCursorPos(ImVec2(13, 163));
                    ImGui::Checkbox("Fast BOW  ", &vars.fastbow);
                    ImGui::SetCursorPos(ImVec2(13, 180));
                    ImGui::Checkbox("INSTA COMPOUND ", &vars.instacompound);
                    ImGui::SetCursorPos(ImVec2(13, 200));
                    ImGui::Checkbox("MOUNTABLE fire  ", &vars.mounted);
                    ImGui::SetCursorPos(ImVec2(13, 218));
                    ImGui::Checkbox("ANTIAIM  ", &vars.antiaim);
                    ImGui::SetCursorPos(ImVec2(13, 235));
                    ImGui::Checkbox("ALWAYS SHOOT  ", &vars.always_shoot);
                }
                break;

            case 4: 

                ImGui::SetCursorPos(ImVec2(4, 4));
                ImGui::BeginChild("     ", ImVec2(440, 500)); // misc tab
                {
                    ImGui::SetCursorPos(ImVec2(13, 25));
                    ImGui::Checkbox("ADMIN FLAGS  ", &vars.admin_flags);
                    ImGui::SetCursorPos(ImVec2(13, 45));
                    ImGui::Checkbox("SPYDERMAN  ", &vars.spyderman);
                    ImGui::SetCursorPos(ImVec2(13, 65));
                    ImGui::Checkbox("DOUBLE JUMP  ", &vars.doublejump);
                    ImGui::SetCursorPos(ImVec2(13, 85));
                    ImGui::Checkbox("OMNI SPRINT", &vars.omnisprint);
                    ImGui::SetCursorPos(ImVec2(13, 105));
                    ImGui::Checkbox("SKY", &vars.skychanger);
                    ImGui::SetCursorPos(ImVec2(13, 125));
                    ImGui::Checkbox("CROSSHAIR", &vars.crosshair);
                    ImGui::SetCursorPos(ImVec2(13, 142));
                    ImGui::Checkbox("FLY HACK  ", &vars.flyhack);
                    ImGui::SetCursorPos(ImVec2(13, 175));
                    ImGui::SliderFloat("FOV CHANGER  ", &vars.fov_amount, 90, 120);
                    ImGui::SetCursorPos(ImVec2(13, 195));
                    ImGui::SliderFloat("GRAVITY ", &vars.gravity_amount, 0.1, 2.5);


                    ImGui::SetCursorPos(ImVec2(13, 450));
                    ImGui::KeyBind("FLYKEY", vars.flyhackbind, ImVec2(50, 15));
                   
                }
                break;
            case 5: 
                ImGui::SetCursorPos(ImVec2(4, 4));
                ImGui::BeginChild("     ", ImVec2(440, 500)); // colors
            {
                ImGui::ColorEdit4(safe_str("CORNER"), vars.corner_color, ImGuiColorEditFlags_NoInputs);
                ImGui::ColorEdit4(safe_str("NAME"), vars.drawColor_name, ImGuiColorEditFlags_NoInputs);
                ImGui::ColorEdit4(safe_str("HEALTH"), vars.health_color, ImGuiColorEditFlags_NoInputs);
                ImGui::ColorEdit4(safe_str("WEAPON"), vars.drawColor_weapon, ImGuiColorEditFlags_NoInputs);
                ImGui::ColorEdit4(safe_str("CROSSHIAR"), vars.drawColor_crosshair, ImGuiColorEditFlags_NoInputs);

            }
         
            }
        }
    }
    ImGui::End();
}

void c_gui::drawESPOverlay()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    POINT mPos;
    GetCursorPos(&mPos);
    ImVec2 window_size = ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowPos(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2 - window_size.x / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - window_size.y / 2), ImGuiCond_Once);
    if (ImGui::Begin("##ESP", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove))
        ImGui::TextColored(ImColor(255, 20, 147), "SWOOP.SOLUTIONS");
        ImGui::TextColored(ImColor(255, 20, 147), "DEV = Daddy Swoop + diglevy");
        visuals->ESP();

    ImGui::End();
}

#endif // !gui_cpp