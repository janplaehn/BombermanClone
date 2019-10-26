#pragma once
#include "IEntity.h"

class RenderManager;
class RectangleCollider;
class StateGame;

class Enemy5 : public IEntity
{
public:
	Enemy5(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state);
	~Enemy5();
	void Update(float p_fDeltaTime);
	void Render();
	Sprite* GetSprite();
	ICollider* GetCollider();
	void OnCollision(IEntity* p_xOther);
	ENTITYTYPE GetType();
	SDL_Point getPosition();
	bool isAlive;
	int deathTime;
	virtual int getXTile() override;
	virtual int getYTile() override;
private:
	StateGame* m_xState;
	Sprite* m_xSprite = nullptr;
	RectangleCollider* m_xCollider = nullptr;
	SDL_Point m_position;
	int m_iSpeed = 0;
	RenderManager* m_xRenderManager = nullptr;
	SDL_Scancode m_leftKey;
	SDL_Scancode m_rightKey;
	ENTITYTYPE m_eType;


	int direction;
	enum directions {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

};

