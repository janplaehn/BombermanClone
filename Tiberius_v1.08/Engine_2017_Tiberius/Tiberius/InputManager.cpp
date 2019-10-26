#include "stdafx.h"
#include "InputManager.h"
#include "Keyboard.h"
#include "Mouse.h"

InputManager::InputManager()
{
	m_xKeyboard = new Keyboard();
	m_xMouse = new Mouse();
}

InputManager::~InputManager()
{
	delete m_xMouse;
	m_xMouse = nullptr;
	delete m_xKeyboard;
	m_xKeyboard = nullptr;
}

bool InputManager::Initialize()
{
	return true;
}

void InputManager::Shutdown()
{
}

bool InputManager::IsKeyDown(SDL_Scancode p_eKey)
{
	return m_xKeyboard->IsKeyDown(p_eKey);
}

bool InputManager::IsKeyPressed(SDL_Scancode p_eKey)
{
	return m_xKeyboard->IsKeyPressed(p_eKey);
}

bool InputManager::IsKeyReleased(SDL_Scancode p_eKey)
{
	return m_xKeyboard->IsKeyReleased(p_eKey);
}

bool InputManager::IsMouseButtonDown(int p_iButton)
{
	return m_xMouse->IsMouseButtonDown(p_iButton);
}

bool InputManager::IsMouseButtonPressed(int p_iButton)
{
	return m_xMouse->IsMouseButtonPressed(p_iButton);
}

bool InputManager::IsMouseButtonReleased(int p_iButton)
{
	return m_xMouse->IsMouseButtonReleased(p_iButton);
}

SDL_Point InputManager::GetMousePosition()
{
	return m_xMouse->GetMousePosition();
}

SDL_Point InputManager::GetMouseMotion()
{
	return m_xMouse->GetMouseMotion();
}

void InputManager::HandleEvents(SDL_Event & p_Event)
{
	//TODO: Research possibility to check what kind of inputevent it is!!
	m_xKeyboard->HandleEvents(p_Event);
	m_xMouse->HandleEvents(p_Event);
}

void InputManager::LateUpdate(float p_fDelta)
{
	m_xKeyboard->LateUpdate(p_fDelta);
	m_xMouse->LateUpdate(p_fDelta);
}
