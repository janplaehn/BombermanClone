#include "stdafx.h"
#include "GameState.h"
#include "FloorTile.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "CollisionManager.h"
#include "Sound.h"
#include "SoundManager.h"
#include <iostream>
#include "EntityManager.h"

std::string GameState::GameState = "State1";

GAME_State::GAME_State() {
	//m_Playfield = new GAME_Entity(EENTITYTYPE::ENTITY_BACKGROUND, 512, 512);
	m_xPlayer = new GAME_Entity(EENTITYTYPE::ENTITY_PLAYER, SDL_SCANCODE_A, SDL_SCANCODE_D, 100, 100);
	m_xEnemy = new GHOSTBLINKY_Entity(EENTITYTYPE::ENTITY_ENEMY, SDL_SCANCODE_J, SDL_SCANCODE_L, 300, 100);
	CollisionManager::AddCollisionPair(EENTITYTYPE::ENTITY_PLAYER, EENTITYTYPE::ENTITY_ENEMY);
	m_pxEntityManager = new EntityManager();

	//m_pxEntityManager->addEntity(m_Playfield);
	m_pxEntityManager->addEntity(m_xPlayer);
	m_pxEntityManager->addEntity(m_xEnemy);

	m_pxRenderManager = Service<RenderManager>::getService();
	m_pxInputManager = Service<InputManager>::getService();
	m_pxMySprite = Service<SpriteManager>::getService()->createSprite("../Assets/pacman_title.png", 0, 0, 32, 32);
	m_pxCollisionSound = Service<SoundManager>::getService()->createSound("../Assets/TheAmazingSound.ogg");
}

GAME_State::~GAME_State() {
	CollisionManager::RemoveCollisionPair(EENTITYTYPE::ENTITY_PLAYER, EENTITYTYPE::ENTITY_ENEMY);
	delete m_pxEntityManager;
	m_pxEntityManager = nullptr;

	/*delete m_Playfield;
	m_Playfield = nullptr;*/

	delete m_xPlayer;
	m_xPlayer = nullptr;
	delete m_xEnemy;
	m_xEnemy = nullptr;
}

void GAME_State::Enter() {
	std::cout << "GAME_State::Enter" << std::endl;
}

bool GAME_State::Update(float p_fDelta) {
	m_pxEntityManager->Update(p_fDelta);
	checkCollision();
	m_pxEntityManager->Render();

	m_pxRenderManager->DebugDrawRect(10, 10, 50, 50);
	m_pxRenderManager->DebugDrawRect(70, 30, 30, 30);
	if (m_pxInputManager->isKeyDown(SDL_SCANCODE_SPACE))
	{
		(m_fAngle > 360) ? m_fAngle = 0.0f : m_fAngle += 0.1f;
	}

	if (m_pxInputManager->isKeyPressed(SDL_SCANCODE_W))
	{
		(m_sNextState == "State1") ? m_sNextState = "State2" : m_sNextState = "State1";
		return false;
	}
	if (m_pxInputManager->isKeyDown(SDL_SCANCODE_F))
	{
		m_pxRenderManager->ModifyCameraPosition(-5, 0);
	}
	if (m_pxInputManager->isKeyDown(SDL_SCANCODE_H))
	{
		m_pxRenderManager->ModifyCameraPosition(5, 0);
	}
	if (m_pxInputManager->isKeyDown(SDL_SCANCODE_T))
	{
		m_pxRenderManager->ModifyCameraPosition(0, 5);
	}
	if (m_pxInputManager->isKeyDown(SDL_SCANCODE_G))
	{
		m_pxRenderManager->ModifyCameraPosition(0, -5);
	}
	float x = sin(m_fAngle) * 35;
	float y = cos(m_fAngle) * 35;

	m_pxMySprite->setPoint(16 + static_cast<int>(x), 64 + static_cast<int>(y));
	m_pxRenderManager->Draw(m_pxMySprite, m_pxInputManager->getMousePosition().x - static_cast<int>(m_pxMySprite->getWidth() / 2) + x, m_pxInputManager->getMousePosition().y - static_cast<int>(m_pxMySprite->getHeight() / 2) + y);

	return true;
}

void GAME_State::Exit() {
	std::cout << "GAME_State::Exit" << std::endl;
}

std::string GAME_State::nextState() {
	return m_sNextState;
}


void GAME_State::checkCollision() {
#pragma region REGION - LOOP ENTITYMANAGERS ENTITIES FOR COLLISION
	std::vector<Entity*> entities = m_pxEntityManager->getAllEntities();
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		for (unsigned int j = 0; j < entities.size(); j++)
		{
			if (j == i)
				continue;

			if (CollisionManager::CheckCollision(entities[i], entities[j]))
			{
				entities[i]->onCollision(entities[j]);
				entities[j]->onCollision(entities[i]);
			}
		}
	}
#pragma endregion

	if (CollisionManager::CheckCollision(m_xPlayer, m_xEnemy))
	{
		m_pxRenderManager->DebugDrawRect(38, 38, 20, 20);
		m_pxRenderManager->DebugDrawRect(78, 38, 20, 20);
		m_pxRenderManager->DebugDrawRect(30, 70, 40, static_cast<int>(40 + m_fTime));
		m_xPlayer->onCollision(m_xEnemy);
		m_xEnemy->onCollision(m_xPlayer);
		m_pxCollisionSound->Play();
		m_fTime += 0.25f;
	}
	else
	{
		m_fTime = 0.0f;
		m_pxRenderManager->DebugDrawRect(40, 40, 5, 5);
		m_pxRenderManager->DebugDrawRect(80, 40, 5, 5);
		m_pxRenderManager->DebugDrawRect(60, 100, 10, 10);
	}
}