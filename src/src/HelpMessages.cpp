#include "Main.h";

struct helpMsgUnk {
	int unk;
	char* txt;
};


void showHelpMessage(const char* text, int durationSeconds)
{
	char* a = (char*)malloc(32);
	for (int i = 0; i < 32; i++)
	{
		a[i] = 0;
	}
	long long* c = (long long*)a;
	*c = durationSeconds * 1000;
	
	helpMsgUnk b;
	b.unk = 0;
	b.txt = (char*)UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);

	UIUNK::_0x049D5C615BD38BAD((Any*)c, (Any*)&b, 1);
}