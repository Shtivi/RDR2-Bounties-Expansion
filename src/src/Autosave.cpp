#include "Main.h";

std::time_t lastSaveTime = std::time(0);

void autosaveModProgress(ModProgress* progress)
{
	std::time_t now = std::time(0);
	if (now >= lastSaveTime + AUTOSAVE_INTERVAL_SEC)
	{
		progress->save();
		lastSaveTime = now;
	}
}