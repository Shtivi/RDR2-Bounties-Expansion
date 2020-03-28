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