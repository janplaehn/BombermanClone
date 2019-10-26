#pragma once

#include "StateMainMenu.h"
#include "StateLevelTitle.h"
#include "StateLevelSelect.h"
#include "StateGame.h"

class StateManager;

class StateOwner
{
public:
	StateOwner(StateManager& p_xStateManager);
	~StateOwner();
private:
	StateManager* m_xStateManager = nullptr;

	StateMainMenu m_xStateOne;
	StateLevelTitle m_xStateTwo;
	StateGame m_xStateThree;
	StateLevelSelect m_xStateFour;
	

};

