#include "aimbot.hpp"
#include "common.hpp"

std::map<std::string, float> BulletSpeeds = {
		{ std::string("ammo.rifle"), 1.0f },
		{ std::string("ammo.rifle.hv"), 1.2f },
		{ std::string("ammo.rifle.explosive"), 0.6f },
		{ std::string("ammo.rifle.incendiary"), 0.6f },

		{ std::string("ammo.pistol"), 1.0f },
		{ std::string("ammo.pistol.hv"), 1.33333f },
		{ std::string("ammo.pistol.incendiary"), 0.75f },

		{ std::string("arrow.wooden"), 1.0f },
		{ std::string("arrow.hv"), 1.6f },
		{ std::string("arrow.fire"), 0.8f },
		{ std::string("arrow.bone"), 0.9f },

		{ std::string("ammo.handmade.shell"), 1.0f },
		{ std::string("ammo.shotgun.slug"), 2.25f },
		{ std::string("ammo.shotgun.fire"), 1.0f },
		{ std::string("ammo.shotgun"), 2.25f },

		{ std::string("ammo.nailgun.nails"), 1.0f }
};
float ProjectileSpeed_Normal() {
	std::string held_item = localPlayer2.getHeldItem().GetItemName();
	float Ammunition_Multiplier = BulletSpeeds[localPlayer2.getHeldItem().GetAmmoType()];

	if (held_item == "No Item")										return 300.0f;

	if (held_item == "rifle.ak")									return 375.0f * Ammunition_Multiplier;
	if (held_item == "rifle.lr300")									return 376.0f * Ammunition_Multiplier;
	if (held_item == "rifle.bolt")									return 656.f * Ammunition_Multiplier;
	if (held_item == "rifle.l96")									return 1125.0f * Ammunition_Multiplier;
	if (held_item == "rifle.m39")									return 469.0f * Ammunition_Multiplier;
	if (held_item == "rifle.semiauto")								return 375.0f * Ammunition_Multiplier;

	if (held_item == "lmg.m249")									return 488.0f * Ammunition_Multiplier;

	if (held_item == "smg.thompson")								return 300.0f * Ammunition_Multiplier;
	if (held_item == "smg.custom")									return 300.0f * Ammunition_Multiplier;
	if (held_item == "smg.mp5")										return 240.0f * Ammunition_Multiplier;

	if (held_item == "pistol.python")								return 300.0f * Ammunition_Multiplier;
	if (held_item == "pistol.semi")									return 300.0f * Ammunition_Multiplier;
	if (held_item == "pistol.revolver")								return 300.0f * Ammunition_Multiplier;
	if (held_item == "pistol.m92")									return 300.0f * Ammunition_Multiplier;
	if (held_item == "pistol.eoka")									return 225.0f * Ammunition_Multiplier;
	if (held_item == "pistol.nailgun")								return 50.0f;

	if (held_item == "crossbow")									return 75.0f * Ammunition_Multiplier;
	if (held_item == "bow.compound")								return 50.f * Ammunition_Multiplier;
	if (held_item == "bow.hunting")									return 50.0f * Ammunition_Multiplier;

	if (held_item == "shotgun.pump")								return 225.0f * Ammunition_Multiplier;
	if (held_item == "shotgun.spas12")								return 225.0f * Ammunition_Multiplier;
	if (held_item == "shotgun.waterpipe")							return 225.0f * Ammunition_Multiplier;
	if (held_item == "shotgun.doublebarrel")						return 225.0f * Ammunition_Multiplier;

	return 200.0f;
}

float GetGravityPS(int ammoid) {
	switch (ammoid) {
	case 14241751:
		return 1.f;
	case -1234735557:
		return 0.75f;
	case 215754713:
		return 0.75f;
	case -1023065463:
		return 0.5f;
	case -2097376851:
		return 0.75f;
	case -1321651331:
		return 1.25f;
	default:
		return 1.f;
	}
}

float AimFov(std::unique_ptr<baseEntity>& BPlayer, BonesList bone)
{
	Vector2 ScreenPos;
	if (!Utils::WorldToScreen(Utils::GetBonePosition(BPlayer->player, bone), ScreenPos)) return 1000.f;
	return Math::Calc2D_Dist(Vector2(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2), ScreenPos);
}

void Normalize(float& Yaw, float& Pitch) {
	if (Pitch < -89) Pitch = -89;
	else if (Pitch > 89) Pitch = 89;
	if (Yaw < -360) Yaw += 360;
	else if (Yaw > 360) Yaw -= 360;
}

Vector3 Prediction(const Vector3& LP_Pos, std::unique_ptr<baseEntity>& Player, BonesList Bone) {
	Vector3 BonePos = Utils::GetBonePosition(Player->player, Bone);
	float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);

	if (Dist > 0.001f) {
		float BulletTime = Dist / ProjectileSpeed_Normal();
		Vector3 vel = Player->getNewVelocity();
		Vector3 PredictVel = vel * BulletTime * 0.7f;
		BonePos += PredictVel;
		float gravity = GetGravityPS(localPlayer2.getHeldItem().GetAmmoTypeID());
		BonePos.y += (4.905 * BulletTime * BulletTime) * gravity;
	} return BonePos;
}

void SilentAimbotTarget(std::unique_ptr<baseEntity>& BPlayer, BonesList Bone) {
	Vector3 Local = Utils::GetBonePosition(localPlayer2.player, BonesList::neck);
	Vector3 PlayerPos = Prediction(Local, BPlayer, Bone);

	Vector2 AngleToAim = Math::CalcAngle(Local, PlayerPos);
	Normalize(AngleToAim.y, AngleToAim.x);
	if (isnan(AngleToAim.x) || isnan(AngleToAim.y))
		return;
	Vector4 toQuat = Math::QuaternionLookRotation((PlayerPos - Local).normalized(), Vector3(0, 1, 0));
	localPlayer2.setEyeAngles(toQuat);

}

void AimbotTarget(std::unique_ptr<baseEntity>& BPlayer, BonesList Bone) {
	Vector3 Local = Utils::GetBonePosition(localPlayer2.player, BonesList::head);
	Vector3 PlayerPos = Prediction(Local, BPlayer, Bone);

	Vector2 AngleToAim = Math::CalcAngle(Local, PlayerPos);
	Normalize(AngleToAim.y, AngleToAim.x);
	if (isnan(AngleToAim.x) || isnan(AngleToAim.y))
		return;

	localPlayer2.setViewAngles(AngleToAim);
}

uintptr_t c_aimbot::getTarget()
{
	float lastFOV = FLT_MAX;

	uintptr_t target;

	for (auto i = 0; i < player_list->size(); i++)
	{

		std::unique_ptr<baseEntity> BPlayer = std::make_unique<baseEntity>(player_list->at(i));

		if (read<bool>(BPlayer->playerModel + 0x289))
		{
			continue;
		}

		if (!BPlayer->IsInView()) continue;

		if (BPlayer->isSleeping()) continue;

		//if (BPlayer->health > 0.0f) continue;

		auto CrosshairDistanceToPlayer = AimFov(BPlayer, BonesList::head);
		if (CrosshairDistanceToPlayer < lastFOV && CrosshairDistanceToPlayer > 0.0f && CrosshairDistanceToPlayer <= vars.fovamount)
		{
			lastFOV = CrosshairDistanceToPlayer;
			target = BPlayer->player;
		}
	}
	return target;
}

void c_aimbot::start()
{
	while (true)
	{
			uintptr_t target = getTarget();


			for (auto i = 0; i < player_list->size(); i++)
			{
				std::unique_ptr<baseEntity> BPlayer = std::make_unique<baseEntity>(player_list->at(i));

				if (BPlayer->player != target)
					continue;

				if (target != NULL)
					//std::cout << "jit found";

					if (GetAsyncKeyState(vars.aimbotkey) && target)
					{
						auto dist = (int)Math::Distance(&localPlayer2.position, &BPlayer->position);

						//if (BPlayer->isSameTeam(localPlayer2.player)) continue;
					
						if (&vars.aimbot)
						{
							if (BPlayer->player && dist <= vars.aimbotDist && !vars.silentaim)
								AimbotTarget(BPlayer, BonesList::head);
							else if (BPlayer->player && dist <= vars.aimbotDist && vars.silentaim)
								SilentAimbotTarget(BPlayer, BonesList::head);
						}
					}
			}
		SleepEx(5, false);
	}
}
