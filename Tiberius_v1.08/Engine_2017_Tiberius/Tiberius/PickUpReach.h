#pragma once
#include "IEntity.h"

class RenderManager;
class RectangleCollider;
class StateGame;
class Sound;

class PickUpReach : public IEntity {
public:
	PickUpReach(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state);
	~PickUpReach();
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
	Sound* m_xPickupSound = nullptr;
	bool wasCollected;
	Sprite* m_xSprite = nullptr;
	RectangleCollider* m_xCollider = nullptr;
	SDL_Point m_position;
	RenderManager* m_xRenderManager = nullptr;
	StateGame* m_xState = nullptr;
	SDL_Scancode m_leftKey;
	SDL_Scancode m_rightKey;
	ENTITYTYPE m_eType;

};

