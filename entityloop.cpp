#include "entityloop.hpp"
#include "common.hpp"

void c_entityloop::PlayerLoop()
{
	std::unique_ptr<std::vector<baseEntity>> entList = std::make_unique<std::vector<baseEntity>>();

	auto i = read<uintptr_t>(g_base + 0x314CC88); //bn
	auto want = read<uintptr_t>(i + 0xB8);
	auto ggg = read<uintptr_t>(want + 0x0);
	auto to = read<uintptr_t>(ggg + 0x10);

	while (true)
	{
		auto die = read<uintptr_t>(to + 0x28);
		auto objList = read<uintptr_t>(die + 0x18);
		auto objListSize = read<uint32_t>(die + 0x10);

		for (auto i = 0; i < objListSize; i++)
		{
			auto curObject = read<uintptr_t>(objList + (0x20 + (i * 8)));
			auto baseObject = read<uintptr_t>(curObject + 0x10);
			auto object = read<uintptr_t>(baseObject + 0x30);
			auto tag = read<WORD>(object + 0x54);
			auto prefab = read_nat(object + 0x60);


			if (tag == 6)
			{

				auto objectClass = read<uintptr_t>(object + 0x30);
				auto entity = read<uintptr_t>(objectClass + 0x18);
				auto transform = read<uintptr_t>(objectClass + 0x8);
				std::unique_ptr<baseEntity> BPlayer = std::make_unique<baseEntity>(entity, transform);

				if (read<bool>(BPlayer->playerModel + 0x289))
				{
					//if(localPlayer2.player = NULL)
					localPlayer2 = *BPlayer;
				}
				entList->push_back(*BPlayer);
				SleepEx(5, false);
			}
			else if (prefab.find("assets/") != std::string::npos) {
				if (prefab.find("stone-ore") != std::string::npos) {
					//do later
				}
				else if (prefab.find("metal-ore") != std::string::npos) {
					//do later
				}
				else if (prefab.find("sulfur-ore") != std::string::npos) {
					//do later
				}
			}

			
		}
		*player_list = *entList;
		//std::cout << player_list.get()->size() << "\n";
		entList->clear();

		SleepEx(100, false);
	}
}