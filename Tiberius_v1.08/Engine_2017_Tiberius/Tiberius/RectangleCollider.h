#pragma once

#include "ICollider.h"

class RectangleCollider : public ICollider
{
public:
	RectangleCollider(int p_iX, int p_iY, int p_iW, int p_iH);
	~RectangleCollider();
	SDL_Rect GetRectangle();
	void SetPosition(int p_iX, int p_iY);
	void SetSize(int p_iW, int p_iH);
	void SetSize(int p_iW, int p_iH, float p_fScale);
	COLLIDERTYPE GetType();
private:
	SDL_Rect m_Bounds;
};

