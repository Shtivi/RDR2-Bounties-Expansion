#include "Main.h"

Prompt::Prompt(const char* text, Hash control)
	: Prompt(text, control, Standard)
{
}

Prompt::Prompt(const char* text, Hash control, PromptMode mode)
{
	handle = UI::_0x04F97DE45A519419(); // _UIPROMPT_REGISTER_BEGIN
	setControl(control);
	setText(text);
	setTargetEntity(NULL);
	setMode(mode);
	UI::_0xF7AA2696A22AD8B9(this->handle); // _UIPROMPT_REGISTER_END

	semiHoldShouldReturn = false;
	hide();
}

Entity Prompt::getTargetEntity()
{
	return this->targetEntity;
}

bool Prompt::getIsEnabled()
{
	return isEnabled;
}

void Prompt::setText(const char* text)
{
	this->text = text;
	const char* textLabel = UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);
	UI::_0x5DD02A8318420DD7(this->handle, (Any*)textLabel); // _UIPROMPT_SET_TEXT
}

void Prompt::setControl(Hash control)
{
	this->control = control;
	UI::_0xB5352B7494A08258(this->handle, control); // _UIPROMPT_SET_CONTROL_ACTION
}

void Prompt::setTargetEntity(Entity target)
{
	this->targetEntity = target;

	if (!target)
	{

		UI::_0x2F11D3A254169EA4(this->handle, 0, 0);
		return;
	}

	int targetEntityGroupId = UI::_0xB796970BD125FCE8(target); // _UIPROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY 
	if (targetEntityGroupId)
	{
		UI::_0x2F11D3A254169EA4(this->handle, targetEntityGroupId, 0); // _UIPROMPT_SET_GROUP
	}
}

void Prompt::setPriority(int priority) 
{
	UI::_0xCA24F528D0D16289(handle, priority); // _UIPROMPT_SET_PRIORITY
}

void Prompt::setMode(PromptMode mode)
{
	this->mode = mode;

	switch (mode)
	{
	case Standard:
		UI::_0xCC6656799977741B(handle, 1); // UIPROMOT_SET_STANDARD_MODE
		break;

	case Hold:
		UI::_0x94073D5CA3F16B7B(handle, 1); // _UIPROMPT_SET_HOLD_MODE
		break;
	case SemiHold:
		UI::_0x94073D5CA3F16B7B(handle, 1); // _UIPROMPT_SET_HOLD_MODE
		break;
	}
}

bool Prompt::isActivatedByPlayer()
{
	if (!this->isEnabled)
	{
		return false;
	}

	switch (mode)
	{
	case Standard:
		return UI::_0xC92AC953F0A982AE(handle, 0); // _UIPROMPT_HAS_STANDARD_MODE_COMPLETED
	case Hold:
		return UI::_0xE0F65F0640EF0617(handle); // _UIPROMPT_HAS_HOLD_MODE_COMPLETED
	case SemiHold:
		if (UI::_0xE0F65F0640EF0617(handle))
		{
			if (semiHoldShouldReturn == true)
			{
				return false;
			}

			semiHoldShouldReturn = true;
			return true;
		}
		else
		{
			semiHoldShouldReturn = false;
		}
	}
}

void Prompt::show()
{
	isEnabled = true;
	update();
}

void Prompt::hide()
{
	isEnabled = false;
	update();
}

void Prompt::update()
{
	UI::_0x8A0FB4D03A630D21(this->handle, isEnabled); // _UIPROMPT_SET_ENABLED
	UI::_0x71215ACCFDE075EE(this->handle, isEnabled); // _UIPROMPT_SET_VISIBLE
}