#pragma once

const float menuX = 0.052f;
const float MENU_WIDTH = 0.260f;
const int MENU_ALPHA = 190;

void drawText(char* text, float x, float y, int r, int g, int b, int a, bool centered = false, float sx = 0.342f, float sy = 0.342f);
void drawSprite(char* category, char* sprite, float x, float y, float scalex, float scaley, float rotation, int r, int g, int b, int a);
void drawRect(float x, float y, float width, float height, int r, int g, int b, int a);

void drawTitle(const char* title);
void drawHeader(const char* header);