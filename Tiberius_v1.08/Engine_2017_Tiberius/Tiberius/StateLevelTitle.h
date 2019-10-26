#pragma once
#include "IState.h"
#include <vector>

class StateManager;
class RenderManager;
class GameManager;
class LevelTitleText;
class LevelManager;
class Music;

class StateLevelTitle : public IState
{
public:
	StateLevelTitle();
	~StateLevelTitle();
	void Enter();
	bool Update(float p_fDelta);
	void Exit();
	std::string NextState();
private:
	LevelManager* m_xLevelManager = nullptr;
	RenderManager* m_xRenderManager = nullptr;
	StateManager* m_xStateManager = nullptr;
	LevelTitleText* m_xTitleText = nullptr;
	static std::string m_sNextState;

	Music* m_xTitleMusic = nullptr;
	unsigned long long startTime;
};



