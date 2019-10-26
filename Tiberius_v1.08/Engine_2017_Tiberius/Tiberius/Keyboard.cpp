#include "stdafx.h"
#include "Keyboard.h"


Keyboard::Keyboard()
{
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		m_bKeys[i] = false;
		m_bKeysLastFrame[i] = false;
	}
}

Keyboard::~Keyboard()
{
}

bool Keyboard::IsKeyDown(SDL_Scancode p_eKey)
{
	return m_bKeys[p_eKey];
}

bool Keyboard::IsKeyPressed(SDL_Scancode p_eKey)
{
	return (m_bKeys[p_eKey] == true
		&& m_bKeysLastFrame[p_eKey] == false);
}

bool Keyboard::IsKeyReleased(SDL_Scancode p_eKey)
{
	return (m_bKeys[p_eKey] == false
		&& m_bKeysLastFrame[p_eKey] == true);
}

void Keyboard::HandleEvents(SDL_Event & p_Event)
{
	if (p_Event.type == SDL_KEYDOWN)
	{
		SetKey(p_Event.key.keysym.scancode, true);
	}
	else if (p_Event.type == SDL_KEYUP)
	{
		SetKey(p_Event.key.keysym.scancode, false);
	}	
}

void Keyboard::LateUpdate(float p_fDelta)
{
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		m_bKeysLastFrame[i] = m_bKeys[i];
	}
}

void Keyboard::SetKey(SDL_Scancode p_eKey, bool p_bValue)
{
	m_bKeys[p_eKey] = p_bValue;
}
