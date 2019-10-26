#include "stdafx.h"
#include "IEntity.h"

SDL_Point IEntity::getPosition()
{
	return SDL_Point();
}

void IEntity::changeDirection()
{
}

int IEntity::getFuseTime()
{
	return 60;
}

void IEntity::increaseSpeed()
{
}

int IEntity::getSpeed()
{
	return 0;
}
