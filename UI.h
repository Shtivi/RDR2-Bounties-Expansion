#pragma once

extern Prompt* inspectPosterPrompt;
extern BountiesMenu* menu;

void initializeUI();
void showSubtitle(const char* text);
void displayDebugText(const char* text);
//void showHelpMessage(const char* text, int durationSeconds = 10);
void clearHelpMessage();
void setHelpMessage(const char* text);
void printHelpMessage();