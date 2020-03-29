#pragma once

struct ConversationLine
{
public:
	Ped speaker;
	char* speechLineName;
};

class Conversation
{
private:
	vector<ConversationLine> lines;

public:
	Conversation();
	void addLine(ConversationLine line);
	void addLine(Ped speaker, char* speechLineName);
	void play();
};