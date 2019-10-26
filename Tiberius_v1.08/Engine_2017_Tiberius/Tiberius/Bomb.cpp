#include "stdafx.h"
#include "Bomb.h"
#include "EngineConfig.h"
#include "Service.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "RectangleCollider.h"
#include "StateGame.h"
#include "GameManager.h"
#include "PickUpSpeed.h"
#include "PickUpReach.h"
#include "PickUpNumber.h"
#include "Sprite.h"
#include "Explosion.h"
#include "SoundManager.h"
#include "Sound.h"
#include "Utility.h"


Bomb::Bomb(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xSprite = Service<SpriteManager>::GetService()->CreateSprite("../Assets/items/bomb.png", 0, 0, EngineConfig::TILE_WIDTH, EngineConfig::TILE_WIDTH);
	m_xCollider = new RectangleCollider(p_iX, p_iY, m_xSprite->GetWidth(), m_xSprite->GetHeight());
	m_position.x = p_iX;
	m_position.y = p_iY;
	m_eType = p_type;
	m_xState = state;
	fuseTime = 30;
	reach = 3;
	m_xExplosionSound = Service<SoundManager>::GetService()->CreateSound("../Assets/sounds/explode.ogg");
}

Bomb::~Bomb() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xSprite);
	delete m_xCollider;
	Service<SoundManager>::GetService()->DestroySound(m_xExplosionSound);
}

void Bomb::Update(float p_fDeltaTime) {
	fuseTime--;
	m_xSprite->animate(2);
	if (fuseTime < 0) {
		explode();
	}
	m_xCollider->SetPosition(m_position.x, m_position.y);
}

void Bomb::Render() {
	m_xRenderManager->Draw(m_xSprite, m_position.x, m_position.y);
}

Sprite * Bomb::GetSprite() {
	return m_xSprite;
}

ICollider* Bomb::GetCollider() {
	return m_xCollider;
}

void Bomb::OnCollision(IEntity* p_xOther) {
	if (p_xOther->GetType() == ENTITYTYPE::ENTITY_EXPLOSION) {
		fuseTime = 1;
	}
}

ENTITYTYPE Bomb::GetType() {
	return m_eType;
}

int Bomb::getFuseTime() {
	return fuseTime;
}

int Bomb::getXTile() {
	int xTile = (m_position.x + 20) / 40;
	return xTile;
}

int Bomb::getYTile() {
	int yTile = (m_position.y + 20) / 40;
	return yTile;
}

void Bomb::explode() {
	m_xExplosionSound->Play();
	//TOP
	for (int i = 0; i < m_xState->m_xGameManager->getBombReach(); i++) {
		if (m_xState->field[getXTile()][getYTile() - i] == ENTITYTYPE::ENTITY_FLOOR) {
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x, m_position.y - EngineConfig::TILE_WIDTH * i, m_xState));
		}
		else if (m_xState->field[getXTile()][getYTile() - i] ==  ENTITYTYPE::ENTITY_BRICK) {
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x, m_position.y - EngineConfig::TILE_WIDTH * i, m_xState));
			m_xState->field[getXTile()][getYTile() - i] = ENTITYTYPE::ENTITY_FLOOR;
			spawnPickup(m_position.x, m_position.y - EngineConfig::TILE_WIDTH * i);
			i = reach;
			break;
		}
		else if (m_xState->field[getXTile()][getYTile() - i] == ENTITYTYPE::ENTITY_DOOR) {
			m_xState->m_xGameManager->setIsOpen(true);
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x, m_position.y - EngineConfig::TILE_WIDTH * i, m_xState));
			i = reach;
			break;
		}
		else if (m_xState->field[getXTile()][getYTile() - i] == ENTITYTYPE::ENTITY_WALL) {
			i = reach;
			break;
		}
	}
	//BOTTOM
	for (int i = 0; i < m_xState->m_xGameManager->getBombReach(); i++) {
		if (m_xState->field[getXTile()][getYTile() + i] == ENTITYTYPE::ENTITY_FLOOR) {
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x, m_position.y + EngineConfig::TILE_WIDTH * i, m_xState));
		}
		else if (m_xState->field[getXTile()][getYTile() + i] == ENTITYTYPE::ENTITY_BRICK) {
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x, m_position.y + EngineConfig::TILE_WIDTH * i, m_xState));
			m_xState->field[getXTile()][getYTile() + i] = ENTITYTYPE::ENTITY_FLOOR;
			spawnPickup(m_position.x, m_position.y + EngineConfig::TILE_WIDTH * i);
			i = reach;
			break;
		}
		else if (m_xState->field[getXTile()][getYTile() + i] == ENTITYTYPE::ENTITY_DOOR) {
			m_xState->m_xGameManager->setIsOpen(true);
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x, m_position.y + EngineConfig::TILE_WIDTH * i, m_xState));
			i = reach;
			break;
		}
		else if (m_xState->field[getXTile()][getYTile() + i] == ENTITYTYPE::ENTITY_WALL) {
			i = reach;
			break;
		}
	}
	//LEFT
	for (int i = 0; i < m_xState->m_xGameManager->getBombReach(); i++) {
		if (m_xState->field[getXTile() - i][getYTile()] == ENTITYTYPE::ENTITY_FLOOR) {
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x - EngineConfig::TILE_WIDTH * i, m_position.y, m_xState));
		}
		else if (m_xState->field[getXTile() - i][getYTile()] == ENTITYTYPE::ENTITY_BRICK) {
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x - EngineConfig::TILE_WIDTH * i, m_position.y, m_xState));
			m_xState->field[getXTile() - i][getYTile()] = ENTITYTYPE::ENTITY_FLOOR;
			spawnPickup((m_position.x - EngineConfig::TILE_WIDTH * i), m_position.y);
			i = reach;
			break;
		}
		else if (m_xState->field[getXTile() - i][getYTile()] == ENTITYTYPE::ENTITY_DOOR) {
			m_xState->m_xGameManager->setIsOpen(true);
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x - EngineConfig::TILE_WIDTH * i, m_position.y, m_xState));
			i = reach;
			break;
		}
		else if (m_xState->field[getXTile() - i][getYTile()] == ENTITYTYPE::ENTITY_WALL) {
			i = reach;
			break;
		}
	}
	//RIGHT
	for (int i = 0; i < m_xState->m_xGameManager->getBombReach(); i++) {
		if (m_xState->field[getXTile() + i][getYTile()] == ENTITYTYPE::ENTITY_FLOOR) {
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x + EngineConfig::TILE_WIDTH * i, m_position.y, m_xState));
		}
		else if (m_xState->field[getXTile() + i][getYTile()] == ENTITYTYPE::ENTITY_BRICK) {
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x + EngineConfig::TILE_WIDTH * i, m_position.y, m_xState));
			m_xState->field[getXTile() + i][getYTile()] = ENTITYTYPE::ENTITY_FLOOR;
			spawnPickup((m_position.x + EngineConfig::TILE_WIDTH * i), m_position.y);
			i = reach;
			break;
		}
		else if (m_xState->field[getXTile() + i][getYTile()] == ENTITYTYPE::ENTITY_DOOR) {
			m_xState->m_xGameManager->setIsOpen(true);
			m_xState->addEntity(new Explosion(ENTITYTYPE::ENTITY_EXPLOSION, m_position.x + EngineConfig::TILE_WIDTH * i, m_position.y, m_xState));
			i = reach;
			break;
		}
		else if (m_xState->field[getXTile() + i][getYTile()] == ENTITYTYPE::ENTITY_WALL) {
			i = reach;
			break;
		}
	}
	m_xState->m_xGameManager->setCurrentBombNumber(m_xState->m_xGameManager->getCurrentBombNumber() - 1);
	m_xState->removeEntity(this);
}

void Bomb::spawnPickup(int xpos, int ypos) {
	int pickupchance;
	pickupchance = Utility::random(0, 7);
	switch (pickupchance) {
	case 1:
		m_xState->addEntity(new PickUpSpeed(ENTITYTYPE::ENTITY_PICKUP, xpos, ypos, m_xState));
		break;
	case 2:
		m_xState->addEntity(new PickUpReach(ENTITYTYPE::ENTITY_PICKUP, xpos, ypos, m_xState));
		break;
	case 3:
		m_xState->addEntity(new PickUpNumber(ENTITYTYPE::ENTITY_PICKUP, xpos, ypos, m_xState));
		break;
	}
}

SDL_Point Bomb::getPosition() {
	return m_position;
}
