#include "stdafx.h"
#include "PickUpReach.h"
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

PickUpReach::PickUpReach(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xSprite = Service<SpriteManager>::GetService()->CreateSprite("../Assets/items/reach.png", 0, 0, EngineConfig::TILE_WIDTH, EngineConfig::TILE_WIDTH);
	m_xCollider = new RectangleCollider(p_iX, p_iY, m_xSprite->GetWidth(), m_xSprite->GetHeight());
	m_position.x = p_iX;
	m_position.y = p_iY;
	m_eType = p_type;
	m_xState = state;
	m_xPickupSound = Service<SoundManager>::GetService()->CreateSound("../Assets/sounds/pickup.ogg");
	wasCollected = false;
}

PickUpReach::~PickUpReach() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xSprite);
	delete m_xCollider;
	Service<SoundManager>::GetService()->DestroySound(m_xPickupSound);
}

void PickUpReach::Update(float p_fDeltaTime) {
	if (wasCollected) {
		m_xPickupSound->Play();
		if (m_xState->m_xGameManager->getBombReach() <= 4) {
			m_xState->m_xGameManager->setBombReach(m_xState->m_xGameManager->getBombReach() + 1);
			wasCollected = false;
		}
		m_xState->removeEntity(this);
	}
	m_xCollider->SetPosition(m_position.x, m_position.y);
}

SDL_Point PickUpReach::getPosition() {
	return m_position;
}

int PickUpReach::getXTile() {
	int xTile = (m_position.x + 20) / 40;
	return xTile;
}

int PickUpReach::getYTile() {
	int yTile = (m_position.y + 20) / 40;
	return yTile;
}

void PickUpReach::Render() {
	m_xRenderManager->Draw(m_xSprite, m_position.x, m_position.y);
}

Sprite * PickUpReach::GetSprite() {
	return m_xSprite;
}

ICollider* PickUpReach::GetCollider() {
	return m_xCollider;
}

void PickUpReach::OnCollision(IEntity* p_xOther) {
	if (p_xOther->GetType() == ENTITYTYPE::ENTITY_PLAYER) {
		wasCollected = true;
	}
}

ENTITYTYPE PickUpReach::GetType() {
	return m_eType;
}
