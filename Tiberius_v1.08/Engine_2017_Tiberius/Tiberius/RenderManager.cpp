#include "stdafx.h"
#include "RenderManager.h"
#include "Sprite.h"
#include "EngineConfig.h"
#include <cassert>
#include <iostream>

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager() {
}

bool RenderManager::Initialize()
{
	m_xWindow = SDL_CreateWindow(EngineConfig::WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, EngineConfig::WINDOW_WIDTH, EngineConfig::WINDOW_HEIGHT, 0);
	SDL_Surface* icon = IMG_Load("../Assets/icon.png");;
	SDL_SetWindowIcon(m_xWindow, icon);
	if (m_xWindow == nullptr)
		return false;
	m_xRenderer = SDL_CreateRenderer(m_xWindow, -1, SDL_VIDEO_OPENGL);
	if(m_xRenderer == nullptr)
		return false;
	return true;
}

void RenderManager::Shutdown()
{
	SDL_DestroyRenderer(m_xRenderer);
	m_xRenderer = nullptr;
	SDL_DestroyWindow(m_xWindow);
	m_xWindow = nullptr;
}

void RenderManager::Clear()
{
	SDL_SetRenderDrawColor(m_xRenderer, 56, 135, 0, 255);
	SDL_RenderClear(m_xRenderer);
}

void RenderManager::ClearBlack() {
	SDL_SetRenderDrawColor(m_xRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_xRenderer);
}

void RenderManager::Present()
{
	DrawData();
	SDL_RenderPresent(m_xRenderer);
}

void RenderManager::Draw(Sprite* p_xSprite, int p_iX, int p_iY)
{
	RenderData data{ p_xSprite, p_iX, p_iY };
	m_axRenderData.push_back(data);
	
}

void RenderManager::DebugDrawRect(int p_iX, int p_iY, int p_iW, int p_iH)
{
	SDL_Rect rect{ p_iX, p_iY, p_iW, p_iH };
	DebugDrawRect(rect);
}

void RenderManager::DebugDrawRect(SDL_Rect p_rect)
{
	SDL_SetRenderDrawColor(m_xRenderer, 0, 0, 0, 255);
	p_rect.x += m_CameraOffset.x;
	p_rect.y += m_CameraOffset.y;
	m_axDebugData.push_back(p_rect);
}

void RenderManager::drawSurface(SDL_Surface *surface, SDL_Rect &rect) {
	texture = SDL_CreateTextureFromSurface(m_xRenderer, surface);
	SDL_RenderCopy(m_xRenderer, texture, NULL, &rect);
	
}

void RenderManager::SetCameraPosition(int p_iX, int p_iY)
{
	m_CameraOffset.x = p_iX;
	m_CameraOffset.y = p_iY;
}

void RenderManager::ModifyCameraPosition(int p_iX, int p_iY)
{
	m_CameraOffset.x += p_iX;
	m_CameraOffset.y += p_iY;
}

SDL_Point RenderManager::GetCameraPosition()
{
	return m_CameraOffset;
}

SDL_Renderer * RenderManager::GetRenderer()
{
	return m_xRenderer;
}

void RenderManager::DrawData()
{
	for (RenderData data : m_axRenderData)
	{
		SDL_Rect dst{ data.x + m_CameraOffset.x,data.y + m_CameraOffset.y,
			static_cast<int>(data.sprite->GetWidth()*data.sprite->GetScale()),
			static_cast<int>(data.sprite->GetHeight()*data.sprite->GetScale()) };

		SDL_RenderCopyEx(m_xRenderer, data.sprite->GetTexture(), &data.sprite->GetArea(), &dst,
			data.sprite->GetAngle(), &data.sprite->GetOrigin(), data.sprite->GetFlip());
		
	}
	m_axRenderData.clear();

	for (SDL_Rect data : m_axDebugData)
	{
		SDL_RenderFillRect(m_xRenderer, &data);
	}
	m_axDebugData.clear();

}
