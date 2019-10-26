#include "stdafx.h"
#include "Enemy5.h"
#include "CollisionManager.h"
#include "Service.h"
#include "RenderManager.h"
#include "GameManager.h"
#include "SpriteManager.h"
#include "RectangleCollider.h"
#include "Sprite.h"
#include "Utility.h"
#include "StateGame.h"

Enemy5::Enemy5(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xSprite = Service<SpriteManager>::GetService()->CreateSprite("../Assets/characters/enemy5.png", 0, 0, 38, 38);
	m_xCollider = new RectangleCollider(p_iX, p_iY, m_xSprite->GetWidth(), m_xSprite->GetHeight());
	m_position.x = p_iX;
	m_position.y = p_iY;
	m_eType = p_type;
	direction = UP;
	m_iSpeed = 7;
	m_xState = state;
	isAlive = true;
	deathTime = 5;
	int getXTile();
	int getYTile();
}

Enemy5::~Enemy5() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xSprite);
	delete m_xCollider;
}

int Enemy5::getXTile() {
	int xTile = (m_position.x + 20) / 40;
	return xTile;
}

int Enemy5::getYTile() {
	int yTile = (m_position.y + 20) / 40;
	return yTile;
}

SDL_Point Enemy5::getPosition() {
	return m_position;
}

void Enemy5::Update(float p_fDeltaTime) {
	if (isAlive) {
		switch (direction) {
		case UP:
			m_position.y -= m_iSpeed;
			m_xSprite->changeAnimation(0);
			break;
		case RIGHT:
			m_position.x += m_iSpeed;
			m_xSprite->changeAnimation(1);
			break;
		case DOWN:
			m_position.y += m_iSpeed;
			m_xSprite->changeAnimation(1);
			break;
		case LEFT:
			m_position.x -= m_iSpeed;
			m_xSprite->changeAnimation(0);
			break;
		}
		m_xSprite->animate(2);
	}
	else {
		m_xSprite->changeAnimation(2);
		m_xSprite->animate(4);
		deathTime--;
		if (deathTime <= 0) {
			m_xState->removeEntity(this);
		}
	}
	m_xCollider->SetPosition(m_position.x, m_position.y);
}

void Enemy5::Render() {
	m_xRenderManager->Draw(m_xSprite, m_position.x, m_position.y);
}

Sprite * Enemy5::GetSprite() {
	return m_xSprite;
}

ICollider* Enemy5::GetCollider() {
	return m_xCollider;
}

void Enemy5::OnCollision(IEntity* p_xOther) {
	if (p_xOther->GetType() == ENTITYTYPE::ENTITY_WALL || p_xOther->GetType() == ENTITYTYPE::ENTITY_DOOR || p_xOther->GetType() == ENTITYTYPE::ENTITY_BRICK) {
		int tempposx = (m_position.x + 20) / 40;
		m_position.x = tempposx * 40 + 1;
		int tempposy = (m_position.y + 20) / 40;
		m_position.y = tempposy * 40 + 1;
		int tempdirection = direction;
		while (direction == tempdirection) {
			direction = Utility::random(0, 3);
		}
	}
	if (p_xOther->GetType() == ENTITYTYPE::ENTITY_EXPLOSION) {
		if ((p_xOther->getXTile() == this->getXTile()) && (p_xOther->getYTile() == this->getYTile())) {
			m_xState->m_xGameManager->setEnemyNumber(m_xState->m_xGameManager->getEnemyNumber() - 1);
			m_xState->m_xGameManager->setScore(m_xState->m_xGameManager->getScore() + 100);
			isAlive = false;
		}
	}
}

ENTITYTYPE Enemy5::GetType() {
	return m_eType;
}