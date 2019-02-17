#pragma once

class ICallbacks
{
public:

	virtual void SpecialKeyboardCB(int Key, int x, int y) = 0;

	virtual void OnKeyboard(unsigned char Key, int x, int y) = 0;

	virtual void PassiveMouseCB(int x, int y) = 0;

	virtual void RenderSceneCB() = 0;

	virtual void IdleCB() = 0;

	virtual void MouseAction(int button, int state, int x, int y) = 0;

	virtual void PassiveMouseDuringAction(int x, int y) = 0;
};