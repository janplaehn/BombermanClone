#include "stdafx.h"
#include "PickUpNumber.h"
#include "Service.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "GameManager.h"
#include "RectangleCollider.h"
#include "SoundManager.h"
#include "Sound.h"
#include "Sprite.h"
#include "StateGame.h"
#include "EngineConfig.h"

PickUpNumber::PickUpNumber(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xSprite = Service<SpriteManager>::GetService()->CreateSprite("../Assets/items/number.png", 0, 0, EngineConfig::TILE_WIDTH, EngineConfig::TILE_WIDTH);
	m_xCollider = new RectangleCollider(p_iX, p_iY, m_xSprite->GetWidth(), m_xSprite->GetHeight());
	m_position.x = p_iX;
	m_position.y = p_iY;
	m_eType = p_type;
	m_xState = state;
	m_xPickupSound = Service<SoundManager>::GetService()->CreateSound("../Assets/sounds/pickup.ogg");
	wasCollected = false;
}

PickUpNumber::~PickUpNumber() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xSprite);
	delete m_xCollider;
	Service<SoundManager>::GetService()->DestroySound(m_xPickupSound);
}

void PickUpNumber::Update(float p_fDeltaTime) {
	m_xCollider->SetPosition(m_position.x, m_position.y);
	if (wasCollected) {
		m_xPickupSound->Play();
		m_xState->m_xGameManager->setMaxBombNumber(m_xState->m_xGameManager->getMaxBombNumber() + 1);
		m_xState->removeEntity(this);
		wasCollected = false;
	}
}

void PickUpNumber::Render() {
	m_xRenderManager->Draw(m_xSprite, m_position.x, m_position.y);
}

Sprite * PickUpNumber::GetSprite() {
	return m_xSprite;
}

ICollider* PickUpNumber::GetCollider() {
	return m_xCollider;
}

int PickUpNumber::getXTile() {
	int xTile = (m_position.x + 20) / 40;
	return xTile;
}

int PickUpNumber::getYTile() {
	int yTile = (m_position.y + 20) / 40;
	return yTile;
}

void PickUpNumber::OnCollision(IEntity* p_xOther) {
	if (p_xOther->GetType() == ENTITYTYPE::ENTITY_PLAYER) {
		wasCollected = true;
	}
}

ENTITYTYPE PickUpNumber::GetType() {
	return m_eType;
}

SDL_Point PickUpNumber::getPosition() {
	return m_position;
}