#pragma once
#include "IEntity.h"

class GameManager;
class InputManager;
class RenderManager;
class RectangleCollider;
class StateGame;
class Sound;

class Player1 : public IEntity {
public:
	Player1(ENTITYTYPE p_type,
		SDL_Scancode p_up, SDL_Scancode p_left, SDL_Scancode p_down, SDL_Scancode p_right,
		int p_iX, int p_iY, GameManager* gamemanager, StateGame* state);

	~Player1();
	void Update(float p_fDeltaTime);
	void Render();
	Sprite* GetSprite();
	Sound* m_xPlaceBombSound = nullptr;
	Sound* m_xMoveXsound;
	Sound* m_xMoveYsound;
	Sound* m_xDeathJingle;
	ICollider* GetCollider();
	void OnCollision(IEntity* p_xOther);
	ENTITYTYPE GetType();
	int m_iSpeed;
	virtual void increaseSpeed();
	virtual int getSpeed();
	virtual int getXTile() override;
	virtual int getYTile() override;
private:
	bool isAlive;
	Sprite* m_xSprite = nullptr;
	RectangleCollider* m_xCollider = nullptr;
	SDL_Point m_position;
	InputManager* m_xInputManager = nullptr;
	RenderManager* m_xRenderManager = nullptr;
	GameManager* m_xGameManager = nullptr;
	StateGame* m_xState = nullptr;
	SDL_Scancode m_upKey;
	SDL_Scancode m_leftKey;
	SDL_Scancode m_downKey;
	SDL_Scancode m_rightKey;
	SDL_Scancode m_bombKey;
	ENTITYTYPE m_eType;
	SDL_Point getPosition();
	int deathTime;
};

