#include "stdafx.h"
#include "Player1.h"
#include "CollisionManager.h"
#include "Service.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "GameManager.h"
#include "RectangleCollider.h"
#include "SoundManager.h"
#include "StateGame.h"
#include "Sprite.h"
#include "Bomb.h"
#include "Sound.h"
#include "Music.h"
#include "Utility.h"
#include "EntityManager.h"

Player1::Player1(ENTITYTYPE p_type,
	 SDL_Scancode p_up, SDL_Scancode p_left, SDL_Scancode p_down, SDL_Scancode p_right,
	int p_iX, int p_iY, GameManager* gamemanager, StateGame* state) {
	m_xInputManager = Service<InputManager>::GetService();
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xSprite = Service<SpriteManager>::GetService()->CreateSprite("../Assets/characters/player1.png", 0, 0, 38, 38);
	m_xCollider = new RectangleCollider(p_iX, p_iY, m_xSprite->GetWidth(), m_xSprite->GetHeight());
	m_upKey = p_up;
	m_leftKey = p_left;
	m_downKey = p_down;
	m_rightKey = p_right;
	m_position.x = p_iX;
	m_position.y = p_iY;
	m_eType = p_type;
	m_xState = state;
	m_xGameManager = gamemanager;
	m_iSpeed = 8;
	m_xPlaceBombSound = Service<SoundManager>::GetService()->CreateSound("../Assets/sounds/placeBomb.ogg");
	m_xMoveXsound = Service<SoundManager>::GetService()->CreateSound("../Assets/sounds/moveX.ogg");
	m_xMoveYsound = Service<SoundManager>::GetService()->CreateSound("../Assets/sounds/moveY.ogg");
	m_xDeathJingle = Service<SoundManager>::GetService()->CreateSound("../Assets/music/death.ogg");
	isAlive = true;
	deathTime = 6;
	if (m_position.x >= 250 && m_position.x <= 410) {
		m_xRenderManager->SetCameraPosition(-(m_position.x - 250), 0);
	}
	else {
		m_xRenderManager->SetCameraPosition(0, 0);
	}
}

Player1::~Player1() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xSprite);
	delete m_xCollider;
	Service<SoundManager>::GetService()->DestroySound(m_xPlaceBombSound);
	Service<SoundManager>::GetService()->DestroySound(m_xMoveXsound);
	Service<SoundManager>::GetService()->DestroySound(m_xMoveYsound);
	Service<SoundManager>::GetService()->DestroySound(m_xDeathJingle);
}

void Player1::increaseSpeed() {
	m_iSpeed += 1;
}

int Player1::getSpeed() {
	return m_iSpeed;
}

SDL_Point Player1::getPosition() {
	return m_position;
}


void Player1::Update(float p_fDeltaTime) {
	if (isAlive) {
		if (m_xInputManager->IsKeyDown(m_upKey)) {
			m_position.y -= m_iSpeed;
			m_xSprite->changeAnimation(2);
			m_xSprite->animate(2);
			m_xMoveYsound->Play();
		}
		if (m_xInputManager->IsKeyDown(m_leftKey)) {
			m_position.x -= m_iSpeed;
			m_xSprite->changeAnimation(3);
			m_xSprite->animate(2);
			m_xMoveXsound->Play();
		}
		if (m_xInputManager->IsKeyDown(m_downKey)) {
			m_position.y += m_iSpeed;
			m_xSprite->changeAnimation(0);
			m_xSprite->animate(2);
			m_xMoveYsound->Play();
		}
		if (m_xInputManager->IsKeyDown(m_rightKey)) {
			m_position.x += m_iSpeed;
			m_xSprite->changeAnimation(1);
			m_xSprite->animate(2);
			m_xMoveXsound->Play();
		}
		if (!(m_xInputManager->IsKeyDown(m_rightKey) || m_xInputManager->IsKeyDown(m_leftKey) || m_xInputManager->IsKeyDown(m_upKey) || m_xInputManager->IsKeyDown(m_downKey))) {
			m_xSprite->animate(0);
		}
		if (m_xInputManager->IsKeyPressed(SDL_SCANCODE_SPACE) && (m_xGameManager->getCurrentBombNumber() < m_xGameManager->getMaxBombNumber())) {
			int tempposx = (m_xGameManager->getplayerposx() + 20) / 40;
			int tempposy = (m_xGameManager->getplayerposy() + 20) / 40;
			m_xState->m_xEntityManager->AddEntity(new Bomb(ENTITYTYPE::ENTITY_BOMB, tempposx * 40, tempposy * 40, m_xState));
			m_xGameManager->setCurrentBombNumber(m_xGameManager->getCurrentBombNumber() + 1);
			m_xPlaceBombSound->Play();
		}
	}
	else {
		m_xSprite->changeAnimation(4);
		m_xSprite->animate(5);
		deathTime--;
		if (m_xGameManager->getRemainingTime() <= 0) {
			isAlive = false;
		}
		if (deathTime == 5) {
			m_xDeathJingle->Play();
			m_xState->m_xGameManager->setLives(m_xState->m_xGameManager->getLives() - 1);
		}
		if (deathTime <= 0) {
			m_xSprite->hide();
		}
		if (deathTime <= (-20)) {
			if (m_xState->m_xGameManager->getLives() >= 0) {
				m_xState->levelResetRequested = true;
				return;
			}
			else {
				m_xGameManager->setLives(2);
				m_xGameManager->setScore(1000);
				m_xState->backToMenuRequested = true;
				return;
			}		
		}
	}
	m_xCollider->SetPosition(m_position.x, m_position.y);
	m_xGameManager->setplayerposx(m_position.x);
	m_xGameManager->setplayerposy(m_position.y);
	if (m_position.x >= 250 && m_position.x <= 410) {
		m_xRenderManager->SetCameraPosition(-(m_position.x - 250), 0);
	}
}

void Player1::Render() {
	m_xRenderManager->Draw(m_xSprite, m_position.x, m_position.y);
}

Sprite * Player1::GetSprite() {
	return m_xSprite;
}

ICollider* Player1::GetCollider() {
	return m_xCollider;
}

int Player1::getXTile() {
	int xTile = (m_position.x + 20) / 40;
	return xTile;
}

int Player1::getYTile() {
	int yTile = (m_position.y + 20) / 40;
	return yTile;
}

void Player1::OnCollision(IEntity* p_xOther) {
	if (p_xOther->GetType() == ENTITYTYPE::ENTITY_WALL || p_xOther->GetType() == ENTITYTYPE::ENTITY_BRICK || p_xOther->GetType() == ENTITYTYPE::ENTITY_DOOR) {
		int tempposx = (m_position.x + 20) / 40;
		m_position.x = tempposx * 40 + 1;
		int tempposy = (m_position.y + 20) / 40;
		m_position.y = tempposy * 40 + 1;
		}
	if (p_xOther->GetType() == ENTITYTYPE::ENTITY_ENEMY || p_xOther->GetType() == ENTITYTYPE::ENTITY_EXPLOSION) {
		if ((p_xOther->getXTile() == this->getXTile()) && (p_xOther->getYTile() == this->getYTile())) {
			isAlive = false;
		}
	}
}

ENTITYTYPE Player1::GetType() {
	return m_eType;
}