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
class Sound; 
class Engine;
class Button;
class LevelManager;

class StateLevelSelect : public IState
{
public:
	StateLevelSelect();
	~StateLevelSelect();
	void Enter();
	bool Update(float p_fDelta);
	void Exit();
	std::string NextState();
	unsigned char field[17][12];

	Button* m_xButtonLevel1 = nullptr;
	Button* m_xButtonLevel2 = nullptr;
	Button* m_xButtonLevel3 = nullptr;
	Button* m_xButtonLevel4 = nullptr;
	Button* m_xButtonLevel5 = nullptr;
	Button* m_xButtonLevel6 = nullptr;
	Button* m_xButtonLevel7 = nullptr;
	Button* m_xButtonLevel8 = nullptr;
	Button* m_xButtonLevel9 = nullptr;
	Button* m_xButtonMenu = nullptr;

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
	Sound* m_xErrorSound = nullptr;
	LevelManager* m_xLevelManager = nullptr;
	std::vector<int> level1;
	void updateColor();


};



