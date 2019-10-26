#include "stdafx.h"
#include "Mouse.h"


Mouse::Mouse()
{
	for (int i = 0; i < MAXBUTTONS; i++)
	{
		m_bButtons[i] = false;
		m_bButtonsLastFrame[i] = false;
	}
}


Mouse::~Mouse()
{
}

bool Mouse::IsMouseButtonDown(int p_iButton)
{
	if (p_iButton >= MAXBUTTONS)
		return false;
	
	return m_bButtons[p_iButton];
}

bool Mouse::IsMouseButtonPressed(int p_iButton)
{
	if (p_iButton >= MAXBUTTONS)
		return false;

	return (m_bButtons[p_iButton] == true
		&& m_bButtonsLastFrame[p_iButton] == false);
}

bool Mouse::IsMouseButtonReleased(int p_iButton)
{
	if (p_iButton >= MAXBUTTONS)
		return false;

	return (m_bButtons[p_iButton] == false
		&& m_bButtonsLastFrame[p_iButton] == true);
}

SDL_Point Mouse::GetMousePosition()
{
	return m_Position;
}

SDL_Point Mouse::GetMouseMotion()
{
	return m_Motion;
}

void Mouse::HandleEvents(SDL_Event & p_Event)
{
	if (p_Event.type == SDL_MOUSEBUTTONDOWN)
	{
		SetButton(p_Event.button.button-1, true);
	}
	else if(p_Event.type == SDL_MOUSEBUTTONUP)
	{
		SetButton(p_Event.button.button-1, false);
	}
	else if (p_Event.type == SDL_MOUSEMOTION)
	{
		m_Position.x = p_Event.motion.x;
		m_Position.y = p_Event.motion.y;
		m_Motion.x = p_Event.motion.xrel;
		m_Motion.y = p_Event.motion.yrel;
	}
	else if (p_Event.type == SDL_MOUSEWHEEL)
	{
		//TODO: Implement functionality for mouse Wheel
	}
}

void Mouse::LateUpdate(float p_fDelta)
{
	for (int i = 0; i < MAXBUTTONS; i++)
	{
		m_bButtonsLastFrame[i] = m_bButtons[i];
	}
}

void Mouse::SetButton(int p_iButtonIndex, bool p_bValue)
{
	if (p_iButtonIndex >= MAXBUTTONS)
		return;

	m_bButtons[p_iButtonIndex] = p_bValue;
}
