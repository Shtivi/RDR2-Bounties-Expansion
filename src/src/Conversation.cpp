#include "Main.h";
#include <thread>

Conversation::Conversation()
{
}

void Conversation::addLine(ConversationLine line)
{
	lines.insert(lines.end(), line);
}

void Conversation::addLine(Ped speaker, char* speechLineName)
{
	ConversationLine line;
	line.speaker = speaker;
	line.speechLineName = speechLineName;
	addLine(line);
}

void Conversation::play()
{
	ConversationLine* currLine;
	ConversationLine* prevLine = NULL;
	vector<ConversationLine>::iterator lineItr = lines.begin();
	while (lineItr != lines.end())
	{
		currLine = &(*lineItr);

		if (prevLine == NULL)
		{
			playAmbientSpeech(currLine->speaker, currLine->speechLineName);
			prevLine = currLine;
		}
		else
		{
			while (AUDIO::IS_ANY_SPEECH_PLAYING(prevLine->speaker))
			{
				this_thread::sleep_for(100ms);
			}
			playAmbientSpeech(currLine->speaker, currLine->speechLineName);
			prevLine = currLine;
		}

		lineItr++;
	}
}