#pragma once

enum ENTITYTYPE
{
	ENTITY_PLAYER,
	ENTITY_FLOOR,
	ENTITY_ENEMY,
	ENTITY_WALL,
	ENTITY_BRICK,
	ENTITY_BOMB,
	ENTITY_EXPLOSION,
	ENTITY_PICKUP,
	ENTITY_DOOR,
	ENTITY_OTHER
};

class Sprite;
class ICollider;

class IEntity
{
public:
	virtual ~IEntity() {};
	virtual void Update(float p_fDeltaTime) = 0;
	virtual void Render() = 0;
	virtual Sprite* GetSprite() = 0;
	virtual ICollider* GetCollider() = 0;
	virtual SDL_Point getPosition();
	virtual void OnCollision(IEntity* p_xOther) = 0;
	virtual ENTITYTYPE GetType() = 0;
	virtual void changeDirection();
	virtual int getFuseTime();
	virtual void increaseSpeed();
	virtual int getSpeed();
	virtual int getXTile() = 0;
	virtual int getYTile() = 0;
};
