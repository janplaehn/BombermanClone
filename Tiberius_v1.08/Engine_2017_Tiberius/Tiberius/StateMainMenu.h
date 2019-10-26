#pragma once
#include "IState.h"
#include <vector>

class StateManager;
class IEntity;
class CONCRETE_Entity;
class WallTile;
class RenderManager;
class InputManager;
class EntityManager;
class GameManager;
class Sprite;
class Music;
class Engine;
class Button;
class LevelManager;

class StateMainMenu : public IState
{
public:
	StateMainMenu();
	~StateMainMenu();
	void Enter();
	bool Update(float p_fDelta);
	void Exit();
	std::string NextState();
	unsigned char field[17][12];

	Button* m_xButtonSingleplayer = nullptr;
	Button* m_xButtonMultiplayer = nullptr;
	Button* m_xButtonQuit = nullptr;

private:



	CONCRETE_Entity* m_xPlayer;
	CONCRETE_Entity* m_xEnemy;
	WallTile* wallTile;
	RenderManager* m_xRenderManager = nullptr;
	InputManager* m_xInputManager = nullptr;
	Engine* m_xEngine = nullptr;
	Sprite* m_xBanner = nullptr;
	StateManager* m_xStateManager = nullptr;
	float m_fAngle = 0.0f;
	float m_fTime = 0.0f;
	static std::string m_sNextState;

	Music* m_xTitleMusic = nullptr;
	LevelManager* m_xLevelManager = nullptr;
	std::vector<int> level1;


};



