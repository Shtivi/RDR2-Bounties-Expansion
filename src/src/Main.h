#pragma once
// Natives
#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\..\inc\main.h"
#include "entity.h"
#include "Math.h"

// Scripts
#include "script.h"
#include "keyboard.h"

// Windows Header Files:
#include <windows.h>
#include <Mmsystem.h>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <Psapi.h>
#include <timeapi.h>
#include <time.h>
#include "../../inc/MinHook/MinHook.h"
#pragma comment(lib, "../../inc/MinHook/libMinHook.x64.lib")

#include "Math.h";
#include "world.h";
#include "blips.h";
#include "Logger.h";
#include "Prompt.h";
#include "GUIDrawer.h";
#include "AttachedRope.h";
#include "AttachedRopesHanding.h";
#include "BountyDefinitions.h";

#include "ModProgress.h";
#include "MapArea.h";
#include "MapAreasManager.h";
#include "BountyMissionData.h";
#include "BaseMissionExecutor.h";
#include "EliasTraditionExecutor.h";
#include "TurkishRunnerExecutor.h";
#include "BountyMissionsFactory.h";
#include "Autosave.h";
#include "BountiesManager.h";
#include "BountiesMenu.h";
#include "UI.h";