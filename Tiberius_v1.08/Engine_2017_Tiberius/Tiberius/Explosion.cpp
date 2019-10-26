#include "stdafx.h"
#include "Explosion.h"
#include "Service.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "RectangleCollider.h"
#include "StateGame.h"
#include "PickUpSpeed.h"
#include "GameManager.h"
#include "Sprite.h"
#include "EngineConfig.h"

Explosion::Explosion(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xSprite = Service<SpriteManager>::GetService()->CreateSprite("../Assets/items/explosion.png", 0, 0, EngineConfig::TILE_WIDTH, EngineConfig::TILE_WIDTH);
	m_xCollider = new RectangleCollider(p_iX + 2, p_iY + 2, m_xSprite->GetWidth() - 4, m_xSprite->GetHeight() - 4);
	m_position.x = p_iX;
	m_position.y = p_iY;
	m_eType = p_type;
	m_xState = state;
	lifeTime = 2;
}

Explosion::~Explosion() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xSprite);
	delete m_xCollider;
}

void Explosion::Update(float p_fDeltaTime) {
	lifeTime--;
	m_xSprite->animate(2);
	m_xCollider->SetPosition(m_position.x, m_position.y);
	if (lifeTime < 0) {
		m_xSprite->hide();
		m_xState->removeEntity(this);
	}
}

void Explosion::Render() {
	m_xRenderManager->Draw(m_xSprite, m_position.x, m_position.y);
}

int Explosion::getXTile() {
	int xTile = m_position.x / 40;
	return xTile;
}

int Explosion::getYTile() {
	int yTile = (m_position.y + 20) / 40;
	return yTile;
}

Sprite * Explosion::GetSprite() {
	return m_xSprite;
}

ICollider* Explosion::GetCollider() {
	return m_xCollider;
}

void Explosion::OnCollision(IEntity* p_xOther) {
	if (p_xOther->GetType() == ENTITYTYPE::ENTITY_BRICK) {
		if (p_xOther->getYTile() == this->getYTile() && p_xOther->getXTile() == this->getXTile()) {
			m_xState->m_xGameManager->setScore(m_xState->m_xGameManager->getScore() + 150);
			m_xState->removeEntity(p_xOther);
		}	
	}
}

ENTITYTYPE Explosion::GetType() {
	return m_eType;
}

SDL_Point Explosion::getPosition() {
	return m_position;
}
