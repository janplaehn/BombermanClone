#pragma once
class Mouse
{
	static const int MAXBUTTONS = 5;
public:
	Mouse();
	~Mouse();
	bool IsMouseButtonDown(int p_iButton);
	bool IsMouseButtonPressed(int p_iButton);
	bool IsMouseButtonReleased(int p_iButton);
	SDL_Point GetMousePosition();
	SDL_Point GetMouseMotion();
	void HandleEvents(SDL_Event &p_Event);
	void LateUpdate(float p_fDelta);
private:
	void SetButton(int p_iButtonIndex, bool p_bValue);
	SDL_Point m_Position;
	SDL_Point m_Motion;
	bool m_bButtons[MAXBUTTONS];
	bool m_bButtonsLastFrame[MAXBUTTONS];
};

