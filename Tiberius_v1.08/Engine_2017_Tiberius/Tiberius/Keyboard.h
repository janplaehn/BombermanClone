#pragma once

class Keyboard
{
public:
	Keyboard();
	~Keyboard();
	bool IsKeyDown(SDL_Scancode p_eKey);
	bool IsKeyPressed(SDL_Scancode p_eKey);
	bool IsKeyReleased(SDL_Scancode p_eKey);
	void HandleEvents(SDL_Event &p_Event);
	void LateUpdate(float p_fDelta);
private:
	void SetKey(SDL_Scancode p_eKey, bool p_bValue);
	bool m_bKeys[SDL_NUM_SCANCODES];
	bool m_bKeysLastFrame[SDL_NUM_SCANCODES];

};

