#pragma once
#include <cstdint>

class c_aimbot
{
public:
	uintptr_t getTarget();
	void start();
};
inline c_aimbot* aimbot;