#include "stdafx.h"
#include "Sprite.h"
#include "EngineConfig.h"

Sprite::Sprite(SDL_Texture * p_Texture, int p_iX, int p_iY, int p_iW, int p_iH)
{
	m_Texture = p_Texture;
	m_Area.x = p_iX;
	m_Area.y = p_iY;
	m_Area.w = p_iW;
	m_Area.h = p_iH;
}

Sprite::~Sprite()
{
}

void Sprite::SetArea(int p_iX, int p_iY, int p_iW, int p_iH)
{
	SetPoint(p_iX, p_iY);
	SetSize(p_iW, p_iH);
}

void Sprite::SetSize(int p_iW, int p_iH)
{
	SetWidth(p_iW);
	SetHeight(p_iH);
}

void Sprite::SetWidth(int p_iW)
{
	m_Area.w = p_iW;
}

void Sprite::SetHeight(int p_iH)
{
	m_Area.h = p_iH;
}

void Sprite::SetPoint(int p_iX, int p_iY)
{
	SetX(p_iX);
	SetY(p_iY);
}

void Sprite::SetX(int p_iX)
{
	m_Area.x = p_iX;
}

void Sprite::SetY(int p_iY)
{
	m_Area.y = p_iY;
}

void Sprite::SetScale(float p_fScale)
{
	m_fScale = p_fScale;
	SetOrigin(m_eOrigin);
}

void Sprite::animate(int frames) {
	if (m_Area.x < EngineConfig::TILE_WIDTH*frames) {
		m_Area.x += EngineConfig::TILE_WIDTH;
	}
	else {
		m_Area.x = 0;
	}	
}

void Sprite::changeAnimation(int animation) {
	m_Area.y = EngineConfig::TILE_WIDTH*animation;
}

void Sprite::hide()
{
		m_Area.x = -40;
		m_Area.y = -40;
}

float Sprite::GetScale()
{
	return m_fScale;
}

void Sprite::SetAngle(double p_dAngle)
{
	m_dAngle = p_dAngle;
}

double Sprite::GetAngle()
{
	return m_dAngle;
}

void Sprite::SetSortingLayer(unsigned int p_iLayer)
{
	m_iSortingLayer = p_iLayer;
}

unsigned int Sprite::GetLayer()
{
	return m_iSortingLayer;
}

void Sprite::SetOrigin(int p_iX, int p_iY)
{
	m_Origin.x = p_iX;
	m_Origin.y = p_iY;
}

void Sprite::SetOrigin(ORIGIN p_eOrigin)
{
	m_eOrigin = p_eOrigin;
	if (m_eOrigin == ORIGIN::Center)
	{
		m_Origin.x = static_cast<int>(GetWidth() * m_fScale / 2);
		m_Origin.y = static_cast<int>(GetHeight() * m_fScale / 2);
	}
	else if (m_eOrigin == ORIGIN::TopLeft)
	{
		m_Origin.x = 0;
		m_Origin.y = 0;
	}
}

SDL_Point Sprite::GetOrigin()
{
	return m_Origin;
}

void Sprite::SetFlip(SDL_RendererFlip p_Flip)
{
	m_Flip = p_Flip;
}

SDL_RendererFlip Sprite::GetFlip()
{
	return m_Flip;
}

SDL_Rect Sprite::GetArea()
{
	return m_Area;
}

int Sprite::GetWidth()
{
	return m_Area.w;
}

int Sprite::GetHeight()
{
	return m_Area.h;
}

SDL_Texture * Sprite::GetTexture()
{
	return m_Texture;
}

