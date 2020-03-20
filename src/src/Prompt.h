#pragma once

enum PromptMode
{
	Standard,
	Hold,
	SemiHold
};

class Prompt
{
	public:
		int handle;

	private: 
		bool isEnabled;
		const char* text;
		Hash control;
		Entity targetEntity;
		PromptMode mode;
		bool semiHoldShouldReturn;

	public: 
		Prompt(const char* text, Hash control);
		Prompt(const char* text, Hash control, PromptMode mode);

		Entity getTargetEntity();
		bool getIsEnabled();

		void setText(const char* text);
		void setControl(Hash control);
		void setTargetEntity(Entity entity);
		void setPriority(int priority);
		void setMode(PromptMode mode);

		bool isActivatedByPlayer();
		void show();
		void hide();

	private:
		void update();
};