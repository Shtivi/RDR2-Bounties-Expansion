#pragma once

class IPlayable
{
public:
	virtual void play() = 0;
	virtual void playSync() = 0;
	virtual bool isPlaying() = 0;
};

class SyncPlayable : public IPlayable
{
private:
	bool _isPlaying;

public:
	SyncPlayable();
	void playSync();
	bool isPlaying();
};

class Delay : public IPlayable
{
private:
	int millisecs;
	bool _isPlaying;

public:
	Delay(int milliseconds);
	void play();
	void playSync();
	bool isPlaying();
};

class ConversationLine : public IPlayable
{
private:
	Ped speaker;
	char* speechLineName;
	bool _isPlaying;

public:
	ConversationLine(Ped speaker, char* speechLine);
	bool isPlaying();
	void play();
	void playSync();
	Ped getSpeaker();

protected:
	virtual void before();
	virtual void after();
};

class Conversation
{
private:
	bool _isPlaying;
	bool _isEnded;
	vector<IPlayable*> lines;

public:
	Conversation();
	bool isPlaying();
	bool isEnded();
	void addLine(IPlayable* line);
	void addDelay(int milliseconds);
	void addLine(Ped speaker, char* speechLineName);
	void play();
};