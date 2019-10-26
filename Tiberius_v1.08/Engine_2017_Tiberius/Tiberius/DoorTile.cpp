#include "stdafx.h"
#include "DoorTile.h"
#include "Service.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "RectangleCollider.h"
#include "GameManager.h"
#include "Sprite.h"
#include "SoundManager.h"
#include "Sound.h"
#include "StateGame.h"
#include "GameManager.h"
#include "LevelManager.h"
#include <iostream>

DoorTile::DoorTile(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xLevelManager = Service<LevelManager>::GetService();
	m_xSprite = Service<SpriteManager>::GetService()->CreateSprite("../Assets/tiles/door.png", 0, 0, 40, 40);
	m_xCollider = new RectangleCollider(p_iX, p_iY, m_xSprite->GetWidth(), m_xSprite->GetHeight());
	m_position.x = p_iX;
	m_position.y = p_iY;
	m_eType = p_type;
	m_xState = state;
	isOpen = false;
	hasWon = false;
	winningTime = 30;
	m_xWinJingle = Service<SoundManager>::GetService()->CreateSound("../Assets/music/win.ogg");
	m_xState->nextLevelRequested = false;
}

DoorTile::~DoorTile() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xSprite);
	delete m_xCollider;
	Service<SoundManager>::GetService()->DestroySound(m_xWinJingle);
}

void DoorTile::Update(float p_fDeltaTime) {
	if (m_xState->m_xGameManager->getIsOpen()) {
		m_xSprite->changeAnimation(1);
		winningTime--;
		if (hasWon) {
			if (winningTime == 28) {
				m_xWinJingle->Play();
			}
			else if (winningTime == 0) {
				m_xState->m_xGameManager->setLives(m_xState->m_xGameManager->getLives() + 1);
				m_xState->nextLevelRequested = true;
				return;
			}	
		}
	}
	else {
		m_xSprite->changeAnimation(0);
	}
	m_xCollider->SetPosition(m_position.x, m_position.y);
}

void DoorTile::Render() {
	m_xRenderManager->Draw(m_xSprite, m_position.x, m_position.y);
}

Sprite * DoorTile::GetSprite() {
	return m_xSprite;
}

ICollider* DoorTile::GetCollider() {
	return m_xCollider;
}

int DoorTile::getXTile() {
	int xTile = (m_position.x + 20) / 40;
	return xTile;
}

int DoorTile::getYTile() {
	int yTile = (m_position.y + 20) / 40;
	return yTile;
}

void DoorTile::OnCollision(IEntity* p_xOther) {
	if ((p_xOther->GetType() == ENTITYTYPE::ENTITY_PLAYER) && (m_xState->m_xGameManager->getIsOpen())) {
		m_xLevelManager->increaseUnlockedLevelNumber();
		isOpen = false;
		hasWon = true;
	}
}

ENTITYTYPE DoorTile::GetType() {
	return m_eType;
}

SDL_Point DoorTile::getPosition() {
	return m_position;
}
