#pragma once
#include "IEntity.h"

class RenderManager;
class LevelManager;
class RectangleCollider;
class StateGame;
class Sound;

class DoorTile : public IEntity {
public:
	DoorTile(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state);
	~DoorTile();
	void Update(float p_fDeltaTime);
	void Render();
	Sprite* GetSprite();
	ICollider* GetCollider();
	void OnCollision(IEntity* p_xOther);
	ENTITYTYPE GetType();
	bool isOpen;
	bool hasWon;
	int winningTime;
	SDL_Point getPosition();
	virtual int getXTile() override;
	virtual int getYTile() override;
private:
	Sound* m_xWinJingle = nullptr;
	Sprite* m_xSprite = nullptr;
	RectangleCollider* m_xCollider = nullptr;
	SDL_Point m_position;
	RenderManager* m_xRenderManager = nullptr;
	LevelManager* m_xLevelManager = nullptr;
	StateGame* m_xState = nullptr;
	ENTITYTYPE m_eType;

};

