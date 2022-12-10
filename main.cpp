#pragma once
#include "main.hpp"
#define safe_str

void createOverlay()
{
	cscene->create();
}

void createLoop()
{
	gameloop->PlayerLoop();
}

void createAimbot()
{
	aimbot->start();
}

int main()
{
	HWND hwnd = nullptr;

		system("Color 9");
		SetConsoleTitleA("SWOOP.SOLUTIONS");
		std::cout << ("----->Thanks for Buying SWOOP.SOLUTION<------") << std::endl;
		Sleep(600);
		std::cout << ("----->please start rust<------") << std::endl;
		while (!hwnd)
		{
			hwnd = FindWindowA(safe_str("UnityWndClass"), safe_str("Rust"));
			Sleep(80);
		}
		Sleep(1000);
		std::cout << ("----->Found Rust<------") << std::endl;
		Sleep(600);
		std::cout << ("----->Push F3 To start the cheat<------") << std::endl;
		Sleep(900);
		while (true)
		{
			if (GetAsyncKeyState(VK_F3))
				break;

			Sleep(50);
		}
		std::cout << ("----->LOADING LOADING<------") << std::endl;
		Sleep(2000);
		Beep(629, 256);
		std::cout << ("----->READY TO BEAM<------") << std::endl;
		Beep(629, 256);

		bool cheatLaunched;
		if (init->cheat())
		{
			std::thread newrth(createOverlay);
			newrth.detach();
			std::thread newrth2(createLoop);
			newrth2.detach();
			std::thread newrth3(createAimbot);
			newrth3.detach();
			while (true)
			{
				//createLoop();
				SleepEx(1, false);
			}
		}
		else
		{
			system("cls");
			std::cout << "Couldn't Communicate With Driver";
		}
		return TRUE;
	}
