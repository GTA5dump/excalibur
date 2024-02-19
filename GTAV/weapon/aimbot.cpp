#include "pch.h"
#include "aimbot.h"
#include "rage/invoker/natives.h"
#include "rage/engine.h"
#include "util/util.h"
#include "menu/util/control.h"

using namespace base::gui;
using namespace menu::weapon::aimbot::vars;

namespace menu::weapon::aimbot::vars {
	variables m_vars;

	const char* aimbotType[] = {
		"Snap", "Silent"
	}; std::size_t aimbot_id = 0;
	 
	const char* targetNames[] = {
		"Players", "Peds", "Enemys", "Police"
	};

	const char* TargetList[3]
	{
		"Player",
		"Ped",
		"Both"
	};

	const char* SelectList[2]
	{
		"Single",
		"Multiple"
	};

	std::size_t TargetListPos = 2;
	std::size_t SelectListPos = 1;
	std::size_t ModeListPos = 0;
}

namespace menu {
	void aimbot_menu::render() {
		renderer::addSubmenu("Aimbot", "Aimbot", [](core* core) {
			core->addOption(toggleOption("Toggle Aimbot")
				.addToggle(&m_vars.m_toggle));

			core->addOption(scrollOption<const char*, std::size_t>("Type")
				.addScroll(&aimbotType).setPosition(&aimbot_id));

			core->addOption(scrollOption<const char*, std::size_t>("Selection")
				.addScroll(&SelectList).setPosition(&SelectListPos));

			core->addOption(scrollOption<const char*, std::size_t>("Target")
				.addScroll(&TargetList).setPosition(&TargetListPos));

			core->addOption(numberOption<int>("Shoot Delay")
				.addNumber(&m_vars.shoot_delay).addMin(1)
				.addMax(100));

			core->addOption(numberOption<float>("FOV")
				.addNumber(&m_vars.fov).addMin(1)
				.addMax(1000).setPrecision(0));

			core->addOption(numberOption<float>("Distance")
				.addNumber(&m_vars.distance).addMin(1)
				.addMax(1000).setPrecision(0));
		});
	}

	void aimbot_menu::update() {
		render();

		Vector3 aim_lock;
		Vector2 mouse_movement;
		float local_fov_change = m_vars.fov;

		if (m_vars.m_toggle) {
			switch (aimbot_id) {
			case 0:
				for (auto ped : control::get_entities(false, true)) {
					if (!ENTITY::IS_ENTITY_DEAD(ped, 0)) {
						int relation = PED::GET_RELATIONSHIP_BETWEEN_PEDS(ped, PLAYER::PLAYER_PED_ID());
						int type = PED::GET_PED_TYPE(ped);
						Vector3 world_position = ENTITY::GET_ENTITY_COORDS(ped, false);

						if (SYSTEM::VDIST2(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true), world_position) > (m_vars.distance * m_vars.distance))
							continue;

						if (PED::IS_PED_A_PLAYER(ped) && m_vars.on_player) {
							goto aimbot_handler;
						}
						else if (((relation == 4) || (relation == 5)) && m_vars.on_enemy) // relation 4 and 5 are for enemies
						{
							goto aimbot_handler;
						}
						else if (((type == 6 && !PED::IS_PED_MODEL(ped, rage::joaat("s_m_y_uscg_01"))) || type == 27 || // s_m_y_uscg_01 = us coast guard 1 (technically military)
							PED::IS_PED_MODEL(ped, rage::joaat("s_m_y_ranger_01")) || PED::IS_PED_MODEL(ped, rage::joaat("s_f_y_ranger_01"))) // ranger models
							&& m_vars.on_police)
						{
							goto aimbot_handler;
						}
						else if (m_vars.on_ped && !PED::IS_PED_A_PLAYER(ped))

							// Update aim lock coords
							aimbot_handler:
						{
							if (!ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(PLAYER::PLAYER_PED_ID(), ped, 17))
								continue;

							// Jump to here to handle instead of continue statements
							aim_lock =
								ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(ped, PED::GET_PED_BONE_INDEX(ped, m_vars.selected_bone));
							if ((aim_lock.x != 0) && (aim_lock.y != 0) && (aim_lock.z != 0)) // Ensure none of the coords are = to 0
							{
								Vector2 screen_dim, movement;
								GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(aim_lock, &screen_dim.x, &screen_dim.y);
								if ((screen_dim.x >= 0) && (screen_dim.y >= 0)) {
									math::vector2<int> io = { *patterns::resolution_x, *patterns::resolution_y };
									math::vector2<float> center(io.x / 2.f, io.y / 2.f); // Use ImGui to get the display size
									//Screen dim is a float between 0-1, multiply the float by screen coords
									screen_dim.x *= io.x;
									screen_dim.y *= io.y;

									if (screen_dim.x > center.x) //If the location is greater than the center (right side)
									{ // Get the amount of distance we need to move, so center of the screen - our location
										movement.x = -(center.x - screen_dim.x);
										if (movement.x + center.x > center.x * 2)
											movement.x = 0;
									}
									else
									{ // if the location is on the left side
										movement.x = screen_dim.x - center.x;
										if (movement.x + center.x < 0)
											movement.x = 0;
									}

									// Same thing here but for y, so switch right with up and left with down
									if (screen_dim.y > center.y)
									{
										movement.y = -(center.y - screen_dim.y);
										if (movement.y + center.y > center.y * 2)
											movement.x = 0;
									}
									else
									{
										movement.y = screen_dim.y - center.y;
										if (movement.y + center.y < 0)
											movement.y = 0;
									}

									if (sqrt(pow(movement.x, 2) + pow(movement.y, 2)) < local_fov_change)
									{ // sqrt of movment x and y ^ 2, handles fov math
										local_fov_change = sqrt(pow(movement.x, 2) + pow(movement.y, 2));
										mouse_movement.x = movement.x;
										mouse_movement.y = movement.y;
									}
								}
							}
						}
					}
				}
				if (PAD::GET_DISABLED_CONTROL_NORMAL(0, (int)eControllerInputs::INPUT_AIM))
				{
					static bool update_time_now = true;
					static std::chrono::system_clock::time_point current_time;

					if (update_time_now)
					{
						current_time = std::chrono::system_clock::now();
						update_time_now = false; //lockout
					}

					std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - current_time;
					if (elapsed_time.count() > 0.f)
					{
						INPUT mouse_handle; // MOUSEINPUT mi;
						mouse_handle.type = INPUT_MOUSE;
						mouse_handle.mi.dwFlags = MOUSEEVENTF_MOVE; // Type = Mouse movement, and the event  is emulating the mouse movement

						// Update the mouse by moving it with how much we need / smoothing speed
						mouse_handle.mi.dx = mouse_movement.x / (m_vars.m_smoothing ? m_vars.m_smooth_speed : 2);
						mouse_handle.mi.dy = mouse_movement.y / (m_vars.m_smoothing ? m_vars.m_smooth_speed : 2);
						SendInput(1, &mouse_handle, sizeof(mouse_handle)); //handles the input

						//Reset our variables
						mouse_movement.x = 0, mouse_movement.y = 0;
						update_time_now = true; //reset our time
					}
				}
				break;
				case 1:
					int ped_amt;
					if (Util::is_key_pressed(VK_RBUTTON))
					{
						if (ModeListPos == 1 && Util::is_key_pressed(VK_LBUTTON)) PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), FALSE);
						const int numElements = 10;
						const int arrSize = numElements * 2 + 2;
						int veh[arrSize];
						veh[0] = numElements;
						int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), veh, -1);
						Ped closest = 0;
						if (veh != NULL)
						{
							for (int i = 0; i < count; i++)
							{
								int offsettedID = i * 2 + 2;
								if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
								{
									ped_amt = -1;
									for (int j = -1; j <= 2; ++j)
									{

										Any ped = veh[offsettedID];

										Vector3 ped_coords = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
										Vector3 self_head_coords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), 0x796e, { 0, 0, 0 });
										Vector3 ped_head_coords = PED::GET_PED_BONE_COORDS(ped, 0x796e, { 0, 0, 0 });
										//GRAPHICS::DRAW_LINE(ped_head_coords, self_head_coords, 255, 0, 0, 200);



										Vector3 self_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
										if (closest == 0) closest = ped;
										else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords, ped_coords, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords, ENTITY::GET_ENTITY_COORDS(closest, TRUE), TRUE) || SelectListPos == 1) closest = ped;//                                                                                                                            
										Hash weaponhash;
										WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
										if (!WEAPON::IS_WEAPON_VALID(weaponhash)) continue;
										float screenX, screenY;
										BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true), &screenX, &screenY);
										if (ModeListPos == 0) onScreen = TRUE;
										switch ((unsigned long long)TargetListPos) {
										case 0:
											if (!PED::IS_PED_A_PLAYER(ped)) continue;
											break;
										case 1:
											if (PED::IS_PED_A_PLAYER(ped)) continue;
											break;
										case 2:

											break;
										}
										PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), FALSE);
										int bones[] = { 0x0,0x2e28,0xe39f,0xf9bb,0x3779,0x83c,0xfedd,0xe175,0xb3fe,0xca72,0x9000,0xcc4d,0x512d,0x8aae,0x60e6,0x3fcf,0x5c57,0x192a,0xe0fd,0x5c01,0x60f0,0x60f1,0x60f2,0xfcd9,0xb1c5,0xeeeb,0x49d9,0x67f2, 0xff9, 0xffa, 0x67f3, 0x1049, 0x104a, 0x67f4, 0x1059, 0x105a, 0x67f5, 0x1029, 0x102a, 0x67f6, 0x1039, 0x103a, 0xeb95, 0x8cbd, 0xee4f, 0x1470, 0x58b7, 0x29d2, 0x9d4d, 0x6e5c, 0xdead, 0xe5f2, 0xfa10, 0xfa11, 0xe5f3, 0xfa60, 0xfa61, 0xe5f4, 0xfa70,0xfa71, 0xe5f5,0xfa40, 0xfa41,0xe5f6,0xfa50, 0xfa51,0x6f06, 0x188e,0xab22,0x90ff,0xbb0, 0x9995,0x796e, 0x322c,0xfe2c, 0xe3db,0xb2b6, 0x62ac,0x542e, 0x74ac,0xaa10, 0x6b52,0x4b88, 0x54c,0x2ba6, 0x9149,0x4ed2, 0xf18f,0x4f37, 0x4537,0xb4a0, 0x4324,0x508f,0xb93b,0xc33b,0xb987,0x8b93,0xdd1c };

										if (((closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen) || SelectListPos == 1))
										{
											if (!ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(PLAYER::PLAYER_PED_ID(), closest, 1000)) continue;


											Vector3 target_coords = PED::GET_PED_BONE_COORDS(closest, 0x796e, { 0, 0, 0 });


											if ((Util::is_key_pressed(VK_LBUTTON)) && GetTickCount() % (m_vars.shoot_delay > 0 ? m_vars.shoot_delay : 1) == 0)
											{

												MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(self_head_coords, target_coords, 50, 1, weaponhash, PLAYER::PLAYER_PED_ID(), 1, 1, 0xbf800000);


											}
										}
									}
								}
							}


						}
					}
					break;
			}
		}

	}
}