#include "Main.h";

BountiesMenu* menu;

void initializeUI()
{
	//inspectPosterPrompt = new Prompt("Inspect bounty", GAMEPLAY::GET_HASH_KEY("INPUT_MERCY_KILL"), SemiHold);
	//inspectPosterPrompt->hide();

	menu = new BountiesMenu();

	clearHelpMessage();
}

void showSubtitle(const char* text)
{
	UILOG::_0xFA233F8FE190514C((Any*)UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", text)); // _UILOG_SET_CACHED_OBJECTIVE
	UILOG::_0xE9990552DEC71600(); // _UILOG_PRINT_CACHED_OBJECTIVE
	UILOG::_0xDFF0D417277B41F8(); // _UILOG_CLEAR_CACHED_OBJECTIVE
}

void displayDebugText(const char* text)
{
	UI::DRAW_TEXT((char*)UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", text), 0, 0);
}