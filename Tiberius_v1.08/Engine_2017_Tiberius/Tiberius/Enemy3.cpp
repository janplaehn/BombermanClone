#include "stdafx.h"
#include "Enemy3.h"
#include "CollisionManager.h"
#include "Service.h"
#include "RenderManager.h"
#include "GameManager.h"
#include "SpriteManager.h"
#include "RectangleCollider.h"
#include "Sprite.h"
#include "Utility.h"
#include "StateGame.h"

Enemy3::Enemy3(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xSprite = Service<SpriteManager>::GetService()->CreateSprite("../Assets/characters/enemy3.png", 0, 0, 38, 38);
	m_xCollider = new RectangleCollider(p_iX, p_iY, m_xSprite->GetWidth(), m_xSprite->GetHeight());
	m_position.x = p_iX;
	m_position.y = p_iY;
	m_eType = p_type;
	direction = UP;
	m_iSpeed = 2;
	m_xState = state;
	isAlive = true;
	deathTime = 5;
}

Enemy3::~Enemy3() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xSprite);
	delete m_xCollider;
}

int Enemy3::getXTile() {
	int xTile = (m_position.x + 20) / 40;
	return xTile;
}

int Enemy3::getYTile() {
	int yTile = (m_position.y + 20) / 40;
	return yTile;
}

SDL_Point Enemy3::getPosition() {
	return m_position;
}

void Enemy3::Update(float p_fDeltaTime) {
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

void Enemy3::Render() {
	m_xRenderManager->Draw(m_xSprite, m_position.x, m_position.y);
}

Sprite * Enemy3::GetSprite() {
	return m_xSprite;
}

ICollider* Enemy3::GetCollider() {
	return m_xCollider;
}

void Enemy3::OnCollision(IEntity* p_xOther) {
	if (p_xOther->GetType() == ENTITYTYPE::ENTITY_WALL || p_xOther->GetType() == ENTITYTYPE::ENTITY_DOOR || p_xOther->GetType() == ENTITYTYPE::ENTITY_BRICK || p_xOther->GetType() == ENTITYTYPE::ENTITY_BOMB) {
		int tempposx = (m_position.x + 20) / 40;
		m_position.x = tempposx * 40 + 1;
		int tempposy = (m_position.y + 20) / 40;
		m_position.y = tempposy * 40 + 1;
		int tempdirection = direction;
		while (direction == tempdirection) {
			int temp = Utility::random(0, 9);
			if (temp <= 3) {
				direction = LEFT;
			}
			else if (temp == 4) {
				direction = UP;
			}
			else if (temp == 5) {
				direction = DOWN;
			}
			else if (temp >= 5) {
				direction = RIGHT;
			}
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

ENTITYTYPE Enemy3::GetType() {
	return m_eType;
}