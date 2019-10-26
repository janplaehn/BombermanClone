#pragma once
#include "IState.h"
#include <vector>

class IEntity;
class CONCRETE_Entity;
class WallTile;
class RenderManager;
class InputManager;
class EntityManager;
class LevelManager;
class GameManager;
class StateManager;
class ScoreboardPoints;
class ScoreboardTime;
class ScoreboardLives;
class Sprite;
class Music;
class Sound;

class StateGame :	public IState {
public:
	StateGame();
	~StateGame();
	void Enter();
	bool Update(float p_fDelta);
	void Exit();
	std::string NextState();
	EntityManager* m_xEntityManager = nullptr;
	GameManager* m_xGameManager = nullptr;
	void addEntity(IEntity * p_xEntity);
	void removeEntity(IEntity * p_xEntity);
	void nextLevel();
	void resetLevel();
	void backToMenu();
	unsigned char field[22][12];
	bool levelResetRequested;
	bool nextLevelRequested;
	bool backToMenuRequested;
private:
	void CheckCollision();
	CONCRETE_Entity* m_xPlayer;
	CONCRETE_Entity* m_xEnemy;
	WallTile* wallTile;
	RenderManager* m_xRenderManager = nullptr;
	InputManager* m_xInputManager = nullptr;
	Sprite* m_xMySprite = nullptr;
	ScoreboardTime* m_xScoreboardTime = nullptr;
	ScoreboardPoints* m_xScoreboardPoints = nullptr;
	ScoreboardLives* m_xScoreboardLives = nullptr;
	LevelManager* m_xLevelManager = nullptr;
	StateManager* m_xStateManager = nullptr;
	float m_fAngle = 0.0f;
	float m_fTime = 0.0f;
	static std::string m_sNextState;
	Music* m_xGameMusic = nullptr;
	unsigned long long startTime;
	void setupBorder();
	void setupLevel();
	enum tiles {FLOOR, WALL, BRICK, PLAYER, ENEMY1, ENEMY2, ENEMY3, ENEMY4, ENEMY5, ENEMY6, ENEMY7, DOOR};
};



