#include "Main.h";

struct HelpTextArgs1
{
    alignas(8) int p0;
    alignas(8) int p1;
    alignas(8) int p2;
    alignas(8) int p3;
};

struct HelpTextArgs2
{
    alignas(8) int p0;
    alignas(8) const char* p1;
};

char helpMessageText[150];

void clearHelpMessage()
{
	for (int i = 0; i < 150; i++)
	{
		helpMessageText[i] = 0;
	}
}

void setHelpMessage(const char* text)
{
	int i = 0;
	while (i < 150 && text[i])
	{
		helpMessageText[i] = text[i];
		i++;
	}
}

void printHelpMessage()
{
	if (helpMessageText[0])
	{
        HelpTextArgs1 args1;

        args1.p0 = 10 * 1000;
        args1.p1 = 0;
        args1.p2 = 0;
        args1.p3 = 0;

        HelpTextArgs2 args2;

        args2.p0 = 0;
        args2.p1 = UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", helpMessageText);

        UIUNK::_0x049D5C615BD38BAD((Any*)&args1, (Any*)&args2, 1);		clearHelpMessage();
	}
}

void showHelpMessage(const char* text, int durationSeconds)
{
    HelpTextArgs1 args1;

    args1.p0 = durationSeconds * 1000;
    args1.p1 = 0;
    args1.p2 = 0;
    args1.p3 = 0;

    HelpTextArgs2 args2;

    args2.p0 = 0;
    args2.p1 = UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);

    UIUNK::_0x049D5C615BD38BAD((Any*)&args1, (Any*)&args2, 1);
}