#include "Main.h";

void drawText(char* text, float x, float y, int r, int g, int b, int a, bool centered, float sx, float sy)
{
	UI::SET_TEXT_COLOR_RGBA(r, g, b, a);
	UI::SET_TEXT_SCALE(sx, sy);
	UI::SET_TEXT_CENTRE(centered);
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, "LITERAL_STRING", text), x, y);
}

void drawSprite(char* category, char* sprite, float x, float y, float scalex, float scaley, float rotation, int r, int g, int b, int a)
{
	float fX = x + scalex / 2;
	float fY = y + scaley / 2;
	if (!TEXTURE::HAS_STREAMED_TEXTURE_DICT_LOADED(sprite))
		TEXTURE::REQUEST_STREAMED_TEXTURE_DICT(sprite, 0);
	GRAPHICS::DRAW_SPRITE(category, sprite, fX, fY, scalex, scaley, rotation, r, g, b, a, 1);
	TEXTURE::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(category);
}

void drawRect(float x, float y, float width, float height, int r, int g, int b, int a)
{
	float fX = x + width / 2;
	float fY = y + height / 2;
	GRAPHICS::DRAW_RECT(fX, fY, width, height, r, g, b, a, true, 0);
}

void drawTitle(const char* title)
{
	drawText((char*)title, menuX + 0.13f, 0.076f, 255, 255, 255, 255, true, 0.5f, 0.5f);
	drawRect(menuX, 0.066f, MENU_WIDTH, 0.104f, 0, 0, 0, MENU_ALPHA);
	drawSprite("generic_textures", "menu_header_1a", menuX, 0.058f, MENU_WIDTH, 0.074f, 0, 255, 255, 255, 255);
	drawSprite("generic_textures", "hud_menu_4a", menuX, 0.131f + 0.027f, MENU_WIDTH, 0.002f, 0, 255, 255, 255, 255);
}

void drawHeader(const char* header)
{
	drawText((char*)header, menuX + 0.13f, 0.076f + 0.0575f, 255, 255, 255, 255, true, 0.3f, 0.3f);
}