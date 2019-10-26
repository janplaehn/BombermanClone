#pragma once
#include "IEntity.h"

class RenderManager;
class RectangleCollider;
class StateGame;
class Sound;

class PickUpNumber : public IEntity {
public:
	PickUpNumber(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state);
	~PickUpNumber();
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
	bool wasCollected;
	Sound* m_xPickupSound = nullptr;
	Sprite* m_xSprite = nullptr;
	RectangleCollider* m_xCollider = nullptr;
	SDL_Point m_position;
	RenderManager* m_xRenderManager = nullptr;
	StateGame* m_xState = nullptr;
	ENTITYTYPE m_eType;
};

