// dllmain.cpp : Defines the entry point for the DLL application.
#include "../Includes.h"
#include "../Menu/Menu.h"

void ScriptMain()
{
	Menu* vehicleMenu = new Menu({ "doors", "window", "lights", "engine" });
	Menu* doorsSubMenu = new Menu({ "back", "FL", "FR", "RL", "RR", "hood", "trunk", "close" });
	Menu* windowsSubMenu = new Menu({ "back", "FL", "FR", "RL", "RR", "close" });

	INIReader reader("VehicleControl.ini");

	Player lPlayer = PLAYER::PLAYER_ID();
	Ped lPlayerPed = PLAYER::GET_PLAYER_PED(lPlayer);

	bool isEngineOn = true;
	int lightsIndex = 0;
	
	//INI stuff
	int OpenMenu = reader.GetInteger("Keys", "OpenMenu", VK_F4);
	int SelectItem = reader.GetInteger("Keys", "SelectItem", VK_RETURN);
	int MoveDown = reader.GetInteger("Keys", "MoveDown", VK_RIGHT);
	int MoveUp = reader.GetInteger("Keys", "MoveUp", VK_LEFT);

	if (reader.ParseError() != 0)
		Beep(500, 500);

	srand(GetTickCount());
	while (true)
	{
		//Actual mod
		if (PED::IS_PED_IN_ANY_VEHICLE(lPlayerPed, FALSE))
		{
			if (IsKeyJustUp(OpenMenu) && !doorsSubMenu->isVisible && !windowsSubMenu->isVisible)
			{
				vehicleMenu->index = 0;
				vehicleMenu->isVisible = !vehicleMenu->isVisible;
			}

			if (IsKeyJustUp(VK_RETURN))
			{
				Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(lPlayerPed, FALSE);

				if (vehicleMenu->isVisible)
					switch (vehicleMenu->index)
					{
					case 0: //Doors
						vehicleMenu->isVisible = false;
						doorsSubMenu->isVisible = true;
						break;
					case 1: //Windows
						vehicleMenu->isVisible = false;
						windowsSubMenu->isVisible = true;
						break;
					case 2: //Lights
						if (lightsIndex == 0)
						{
							lightsIndex = 1;
							VEHICLE::SET_VEHICLE_LIGHTS(playerVehicle, lightsIndex);
						}
						else
						{
							lightsIndex = 0;
							VEHICLE::SET_VEHICLE_LIGHTS(playerVehicle, lightsIndex);
						}
						break;
					case 3: //Engine
						if (VEHICLE::_IS_VEHICLE_ENGINE_ON(playerVehicle))
							VEHICLE::SET_VEHICLE_ENGINE_ON(playerVehicle, FALSE, FALSE, TRUE);
						else
							VEHICLE::SET_VEHICLE_ENGINE_ON(playerVehicle, TRUE, FALSE, TRUE);
						break;
					}

				else if (doorsSubMenu->isVisible)
				{
					if (doorsSubMenu->index > 0 && doorsSubMenu->index < doorsSubMenu->GetMenuElementCount() - 1)
					{
						VEHICLE::SET_VEHICLE_DOOR_OPEN(playerVehicle, doorsSubMenu->index - 1, FALSE, FALSE);
					}
					else if (doorsSubMenu->index == 0)
					{
						vehicleMenu->isVisible = true;
						doorsSubMenu->isVisible = false;
					}
					else
						VEHICLE::SET_VEHICLE_DOORS_SHUT(playerVehicle, FALSE);
				}

				else if (windowsSubMenu->isVisible)
				{
					if (windowsSubMenu->index > 0 && windowsSubMenu->index < windowsSubMenu->GetMenuElementCount() - 1)
					{
						VEHICLE::ROLL_DOWN_WINDOW(playerVehicle, windowsSubMenu->index - 1);
					}
					else if (windowsSubMenu->index == 0)
					{
						vehicleMenu->isVisible = true;
						windowsSubMenu->isVisible = false;
					}
					else
					{
						for (int i = 0; i < 4; i++)
						{ 
							VEHICLE::ROLL_UP_WINDOW(playerVehicle, i);
						}
					}
				}
			}
		}
		else
		{
			vehicleMenu->isVisible = false;
			doorsSubMenu->isVisible = false;
			windowsSubMenu->isVisible = false;
			isEngineOn = true;
		}

		vehicleMenu->Handle();
		doorsSubMenu->Handle();
		windowsSubMenu->Handle();

		WAIT(0);
	}
 }

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		scriptRegister(hModule, ScriptMain);
		keyboardHandlerRegister(OnKeyboardMessage);
		break;
    case DLL_PROCESS_DETACH:
		scriptUnregister(hModule);
		keyboardHandlerUnregister(OnKeyboardMessage);
        break;
    }
    return TRUE;
}