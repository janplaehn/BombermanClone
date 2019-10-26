#include "stdafx.h"
#include "StateOwner.h"
#include "StateManager.h"


StateOwner::StateOwner(StateManager& p_xStateManager)
{
	m_xStateManager = &p_xStateManager;
	m_xStateManager->AddState("MainMenu", &m_xStateOne);
	m_xStateManager->AddState("LevelTitle", &m_xStateTwo);
	m_xStateManager->AddState("Game", &m_xStateThree);
	m_xStateManager->AddState("LevelSelect", &m_xStateFour);
	m_xStateManager->SetState("MainMenu");
}

StateOwner::~StateOwner()
{
	m_xStateManager->RemoveState("Game");
	m_xStateManager->RemoveState("LeveltTitle");
	m_xStateManager->RemoveState("MainMenu");
	m_xStateManager->RemoveState("LevelSelect");
}
