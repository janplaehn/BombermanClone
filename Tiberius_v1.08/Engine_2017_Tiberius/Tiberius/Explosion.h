#pragma once
#include "IEntity.h"

class RenderManager;
class RectangleCollider;
class StateGame;
class GameManager;

class Explosion : public IEntity {
public:
	Explosion(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state);
	~Explosion();
	void Update(float p_fDeltaTime);
	void Render();
	Sprite* GetSprite();
	ICollider* GetCollider();
	void OnCollision(IEntity* p_xOther);
	ENTITYTYPE GetType();	
	SDL_Point getPosition();
	virtual int getXTile() override;
	virtual int getYTile() override;
private:
	int lifeTime;
	Sprite* m_xSprite = nullptr;
	RectangleCollider* m_xCollider = nullptr;
	SDL_Point m_position;
	RenderManager* m_xRenderManager = nullptr;
	StateGame* m_xState = nullptr;
	GameManager* gameManager = nullptr;
	ENTITYTYPE m_eType;

};

