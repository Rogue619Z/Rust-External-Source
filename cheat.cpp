#pragma once
#include "common.hpp"
#include <array>


void c_cheat::create()
{
		auto local_player = reinterpret_cast<c_baseplayer*>(init->local_player());

		if (local_player != 0 /*in server wont be 0*/)
		{
			local_player->set_spyderman(vars.spyderman);
			if (localPlayer2.getHeldItem().IsWeapon())
			{
				local_player->set_recoil(vars.no_recoil);
				local_player->set_nospread(vars.nospread);
				local_player->set_thickbullet(vars.thickbullet);
				local_player->set_instanteoka(vars.instanteoka);
			}
			local_player->set_flag(4, vars.admin_flags);
			local_player->set_fov(vars.fov_amount, vars.set_zoom, vars.zoombind);
			local_player->set_gravity(vars.gravity_amount);
			local_player->set_doublejump(vars.doublejump);
			local_player->set_always_shoot(vars.always_shoot);
			local_player->antiaim(vars.antiaim);
			local_player->set_rapid(vars.rapidfire);
			//local_player->autoo(vars.autooo);
			//local_player->set_shottyNS(vars.shotty_ns);



		}
}
