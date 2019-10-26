#include "stdafx.h"
#include "PickUpSpeed.h"
#include "Service.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "RectangleCollider.h"
#include "SoundManager.h"
#include "Sound.h"
#include "Sprite.h"
#include "StateGame.h"
#include "EngineConfig.h"

PickUpSpeed::PickUpSpeed(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xSprite = Service<SpriteManager>::GetService()->CreateSprite("../Assets/items/speed.png", 0, 0, EngineConfig::TILE_WIDTH, EngineConfig::TILE_WIDTH);
	m_xCollider = new RectangleCollider(p_iX, p_iY, m_xSprite->GetWidth(), m_xSprite->GetHeight());
	m_position.x = p_iX;
	m_position.y = p_iY;
	m_eType = p_type;
	m_xState = state;
	m_xPickupSound = Service<SoundManager>::GetService()->CreateSound("../Assets/sounds/pickup.ogg");
}

PickUpSpeed::~PickUpSpeed() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xSprite);
	delete m_xCollider;
	Service<SoundManager>::GetService()->DestroySound(m_xPickupSound);
}

int PickUpSpeed::getXTile() {
	int xTile = (m_position.x + 20) / 40;
	return xTile;
}

int PickUpSpeed::getYTile() {
	int yTile = (m_position.y + 20) / 40;
	return yTile;
}

SDL_Point PickUpSpeed::getPosition() {
	return m_position;
}

void PickUpSpeed::Update(float p_fDeltaTime) {
	m_xCollider->SetPosition(m_position.x, m_position.y);
}

void PickUpSpeed::Render() {
	m_xRenderManager->Draw(m_xSprite, m_position.x, m_position.y);
}

Sprite * PickUpSpeed::GetSprite() {
	return m_xSprite;
}

ICollider* PickUpSpeed::GetCollider() {
	return m_xCollider;
}

void PickUpSpeed::OnCollision(IEntity* p_xOther) {
	if (p_xOther->GetType() == ENTITYTYPE::ENTITY_PLAYER) {
		m_xPickupSound->Play();
		p_xOther->increaseSpeed();
		m_xState->removeEntity(this);
	}
}

ENTITYTYPE PickUpSpeed::GetType() {
	return m_eType;
}
