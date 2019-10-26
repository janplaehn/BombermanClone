#include "stdafx.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "RenderManager.h"

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
}

bool SpriteManager::Initialize(RenderManager * p_xRenderManager)
{
	if (p_xRenderManager == nullptr)
		return false;
	m_xRenderManager = p_xRenderManager;
	return true;
}

void SpriteManager::Shutdown()
{
	for (auto sprite : m_Sprites)
	{
		delete sprite;
		sprite = nullptr;
	}
	m_Sprites.clear();
	for(auto pair : m_Textures)
	{
		SDL_DestroyTexture(pair.second);
	}
	m_Textures.clear();
}

Sprite * SpriteManager::CreateSprite(const std::string p_FilePath, int p_iX, int p_iY, int p_iW, int p_iH)
{
	auto it = m_Textures.find(p_FilePath);
	if (it == m_Textures.end())
	{
		SDL_Surface* surface = IMG_Load(p_FilePath.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_xRenderManager->GetRenderer(), surface);
		SDL_FreeSurface(surface);
		m_Textures.insert(std::pair<std::string, SDL_Texture*>(p_FilePath, texture));
		it = m_Textures.find(p_FilePath);
	}
	Sprite* sprite = new Sprite(it->second, p_iX, p_iY, p_iW, p_iH);
	m_Sprites.push_back(sprite);
	return sprite;
}

void SpriteManager::DestroySprite(Sprite * p_xSprite)
{
	for(int i = 0; i<m_Sprites.size(); i++)
	{
		if (m_Sprites[i] == p_xSprite)
		{
			std::vector<Sprite*>::iterator it = m_Sprites.begin(); // iterator points to first element in vector
			it = it + i; // the + move the iterator pointer forward in memory i * by bytes of the datatype
			delete m_Sprites[i];
			m_Sprites[i] = nullptr;
			m_Sprites.erase(it);
			return;
		}
	}
}

