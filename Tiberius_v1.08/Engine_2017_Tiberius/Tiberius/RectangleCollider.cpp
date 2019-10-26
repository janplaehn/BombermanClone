#include "stdafx.h"
#include "RectangleCollider.h"


RectangleCollider::RectangleCollider(int p_iX, int p_iY, int p_iW, int p_iH)
{
	SetPosition(p_iX, p_iY);
	SetSize(p_iW, p_iH);
}


RectangleCollider::~RectangleCollider()
{
}

SDL_Rect RectangleCollider::GetRectangle()
{
	return m_Bounds;
}

void RectangleCollider::SetPosition(int p_iX, int p_iY)
{
	m_Bounds.x = p_iX;
	m_Bounds.y = p_iY;
}

void RectangleCollider::SetSize(int p_iW, int p_iH)
{
	(p_iW <= 0) ? m_Bounds.w = 1 : m_Bounds.w = p_iW;
	(p_iH <= 0) ? m_Bounds.h = 1 : m_Bounds.h = p_iH;
}

void RectangleCollider::SetSize(int p_iW, int p_iH, float p_fScale)
{
	SetSize( static_cast<int>(p_iW * p_fScale),static_cast<int>(p_iH * p_fScale) );
}

COLLIDERTYPE RectangleCollider::GetType()
{
	return COLLIDERTYPE::RECTANGLE;
}
