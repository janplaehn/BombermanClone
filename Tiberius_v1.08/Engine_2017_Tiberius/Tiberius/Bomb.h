#pragma once
#include "IEntity.h"

class RenderManager;
class RectangleCollider;
class StateGame;
class Sound;

class Bomb : public IEntity {
public:
	Bomb(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state);
	~Bomb();
	void Update(float p_fDeltaTime);
	void Render();
	Sprite* GetSprite();
	ICollider* GetCollider();
	void OnCollision(IEntity* p_xOther);
	ENTITYTYPE GetType();	
	int getFuseTime();
	virtual int getXTile() override;
	virtual int getYTile() override;
	SDL_Point getPosition();
private:
	Sound* m_xExplosionSound = nullptr;
	Sprite* m_xSprite = nullptr;
	RectangleCollider* m_xCollider = nullptr;
	SDL_Point m_position;
	RenderManager* m_xRenderManager = nullptr;
	StateGame* m_xState = nullptr;
	ENTITYTYPE m_eType;
	void explode();
	int fuseTime;
	int reach;
	void spawnPickup(int xpos, int ypos);
	
};

