#include "stdafx.h"
#include "StateGame.h"
#include "WallTile.h"
#include "BrickTile.h"
#include "DoorTile.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Enemy6.h"
#include "Enemy7.h"
#include "Player1.h"
#include "Bomb.h"
#include "ScoreboardTime.h"
#include "ScoreboardLives.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "CollisionManager.h"
#include "LevelManager.h"
#include "Sound.h"
#include "SoundManager.h"
#include <iostream>
#include "EntityManager.h"
#include "GameManager.h"
#include "EngineConfig.h"
#include "StateManager.h"
#include "IEntity.h"
#include "Utility.h"
#include <ctime>
#include "ScoreboardPoints.h"
#include "Music.h"

std::string StateGame::m_sNextState = "State1";

StateGame::StateGame() {
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_WALL);
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_BRICK);
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_ENEMY, ENTITYTYPE::ENTITY_WALL);
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_ENEMY, ENTITYTYPE::ENTITY_BRICK);
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_EXPLOSION, ENTITYTYPE::ENTITY_BRICK);
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_EXPLOSION, ENTITYTYPE::ENTITY_ENEMY);
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_ENEMY, ENTITYTYPE::ENTITY_BOMB);
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_ENEMY);
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_EXPLOSION);
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_BOMB, ENTITYTYPE::ENTITY_EXPLOSION);
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_PICKUP);
	CollisionManager::AddCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_DOOR);

	levelResetRequested = false;
	nextLevelRequested = false;
	backToMenuRequested = false;
	m_xGameManager = new GameManager();
	m_xScoreboardTime = new ScoreboardTime(this);
	m_xScoreboardPoints = new ScoreboardPoints(this);
	m_xScoreboardLives = new ScoreboardLives(this);

	m_xRenderManager = Service<RenderManager>::GetService();
	m_xLevelManager = Service<LevelManager>::GetService();
	m_xInputManager = Service<InputManager>::GetService();
	m_xStateManager = Service<StateManager>::GetService();
	m_xGameMusic = Service<SoundManager>::GetService()->CreateMusic("../Assets/music/game.ogg");
}

StateGame::~StateGame() {
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_WALL);
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_BRICK);
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_ENEMY, ENTITYTYPE::ENTITY_WALL);
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_ENEMY, ENTITYTYPE::ENTITY_BRICK);
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_EXPLOSION, ENTITYTYPE::ENTITY_BRICK);
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_EXPLOSION, ENTITYTYPE::ENTITY_ENEMY);
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_ENEMY, ENTITYTYPE::ENTITY_BOMB);
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_ENEMY);
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_EXPLOSION);
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_BOMB, ENTITYTYPE::ENTITY_EXPLOSION);
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_PICKUP);
	CollisionManager::RemoveCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_DOOR);

	delete m_xGameManager;

	Service<SoundManager>::GetService()->DestroyMusic(m_xGameMusic);

	delete m_xScoreboardTime;
	delete m_xScoreboardPoints;
}

void StateGame::Enter() {
	levelResetRequested = false;
	nextLevelRequested = false;
	backToMenuRequested = false;
	m_xEntityManager = new EntityManager();
	startTime = Utility::get_time();
	setupBorder();
	setupLevel();
	m_xGameMusic->Play();
	m_xGameManager->setRemainingTime(400);
	m_xGameManager->setCurrentBombNumber(0);
	m_xGameManager->setBombReach(2);
	m_xGameManager->setMaxBombNumber(1);
	m_xGameManager->setIsOpen(false);
}

void StateGame::Exit() {
	std::vector<IEntity*> entities = m_xEntityManager->GetAllEntities();
	for (IEntity* entity : entities) {
		m_xEntityManager->RemoveEntity(entity);
		delete entity;
	}
	delete m_xEntityManager;
}

bool StateGame::Update(float p_fDelta) {
	m_xEntityManager->Update(p_fDelta);
	CheckCollision();

	m_xScoreboardTime->update();
	m_xScoreboardPoints->update();
	m_xScoreboardLives->update();

	if (!(levelResetRequested || nextLevelRequested || backToMenuRequested)) {
		m_xEntityManager->Render();
		m_xScoreboardTime->render();
		m_xScoreboardPoints->render();
		m_xScoreboardLives->render();
	}


	unsigned long long currentTime = Utility::get_time();
	unsigned long long elapsedTime = currentTime - startTime;
	m_xGameManager->setRemainingTime(300 - int (elapsedTime/1000));
	
	if (levelResetRequested) {
		resetLevel();
		levelResetRequested = false;
	}
	if (nextLevelRequested) {
		nextLevel();
		nextLevelRequested = false;
	}
	if (backToMenuRequested) {
		backToMenu();
		backToMenuRequested = false;
	}
	return true;
}

std::string StateGame::NextState() {
	return m_sNextState;
}

void StateGame::addEntity(IEntity * p_xEntity) {
	m_xEntityManager->AddEntity(p_xEntity);
}

void StateGame::removeEntity(IEntity * p_xEntity) {
	m_xEntityManager->RemoveEntity(p_xEntity);
}

void StateGame::nextLevel() {
	m_xLevelManager->setCurrentLevel(m_xLevelManager->getCurrentLevel() + 1);
	m_xStateManager->SetState("LevelTitle");
}

void StateGame::resetLevel() {
	m_xStateManager->SetState("LevelTitle");
}

void StateGame::backToMenu() {
	m_xStateManager->SetState("MainMenu");
}

void StateGame::CheckCollision() {
	#pragma region REGION - LOOP ENTITYMANAGERS ENTITIES FOR COLLISION
	std::vector<IEntity*> entities = m_xEntityManager->GetAllEntities();
	for (unsigned int i = 0; i < entities.size(); i++) {
		for (unsigned int j =0; j < entities.size(); j++) {
			if (j == i) {
				continue;
			}
			if (CollisionManager::CheckCollision(entities[i], entities[j])) {
				entities[i]->OnCollision(entities[j]);
				entities[j]->OnCollision(entities[i]);
			}		
		}
	}
	#pragma endregion
}

void StateGame::setupBorder() {
	for (int tileX = 0; tileX <= 22; tileX++) {
		m_xEntityManager->AddEntity(new WallTile(ENTITYTYPE::ENTITY_WALL, tileX*40, 1*40));
		field[tileX][1] = ENTITYTYPE::ENTITY_WALL;
	}
	for (int tileX = 0; tileX <= 22; tileX++) {
		m_xEntityManager->AddEntity(new WallTile(ENTITYTYPE::ENTITY_WALL, tileX * 40, 11 * 40));
		field[tileX][11] = ENTITYTYPE::ENTITY_WALL;
	}
	for (int tileY = 2; tileY <= 10; tileY++) {
		m_xEntityManager->AddEntity(new WallTile(ENTITYTYPE::ENTITY_WALL, 0*40 , tileY * 40));
		field[0][tileY] = ENTITYTYPE::ENTITY_WALL;
	}
	for (int tileY = 2; tileY <= 10; tileY++) {
		m_xEntityManager->AddEntity(new WallTile(ENTITYTYPE::ENTITY_WALL, 20 * 40, tileY * 40));
		field[19][tileY] = ENTITYTYPE::ENTITY_WALL;
	}
}

void StateGame::setupLevel() {
		int tileX = 1;
		int tileY = 2;
		std::vector<int> tiles = m_xLevelManager->getLevelTiles();
	for (int tile : tiles) {
		switch (tile) {
		case FLOOR:
			field[tileX][tileY] = ENTITYTYPE::ENTITY_FLOOR;
			break;
		case WALL:
			m_xEntityManager->AddEntity(new WallTile(ENTITYTYPE::ENTITY_WALL, tileX*40, tileY*40));
			field[tileX][tileY] = ENTITYTYPE::ENTITY_WALL;
			break;
		case BRICK:
			m_xEntityManager->AddEntity(new BrickTile(ENTITYTYPE::ENTITY_BRICK, tileX * 40, tileY * 40, this));
			field[tileX][tileY] = ENTITYTYPE::ENTITY_BRICK;
			break;
		case PLAYER:
			m_xEntityManager->AddEntity(new Player1(ENTITYTYPE::ENTITY_PLAYER, SDL_SCANCODE_W, SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, tileX * 40 + 1, tileY * 40 + 1, m_xGameManager, this));
			field[tileX][tileY] = ENTITYTYPE::ENTITY_FLOOR;
			break;
		case ENEMY1:
			m_xEntityManager->AddEntity(new Enemy1(ENTITYTYPE::ENTITY_ENEMY, tileX * 40 + 1, tileY * 40 + 1, this));
			field[tileX][tileY] = ENTITYTYPE::ENTITY_FLOOR;
			break;
		case ENEMY2:
			m_xEntityManager->AddEntity(new Enemy2(ENTITYTYPE::ENTITY_ENEMY, tileX * 40 + 1, tileY * 40 + 1, this));
			field[tileX][tileY] = ENTITYTYPE::ENTITY_FLOOR;
			break;
		case ENEMY3:
			m_xEntityManager->AddEntity(new Enemy3(ENTITYTYPE::ENTITY_ENEMY, tileX * 40 + 1, tileY * 40 + 1, this));
			field[tileX][tileY] = ENTITYTYPE::ENTITY_FLOOR;
			m_xGameManager->setEnemyNumber(m_xGameManager->getEnemyNumber() + 1);
			break;
		case ENEMY4:
			m_xEntityManager->AddEntity(new Enemy4(ENTITYTYPE::ENTITY_ENEMY, tileX * 40 + 1, tileY * 40 + 1, this));
			field[tileX][tileY] = ENTITYTYPE::ENTITY_FLOOR;
			m_xGameManager->setEnemyNumber(m_xGameManager->getEnemyNumber() + 1);
			break;
		case ENEMY5:
			m_xEntityManager->AddEntity(new Enemy5(ENTITYTYPE::ENTITY_ENEMY, tileX * 40 + 1, tileY * 40 + 1, this));
			field[tileX][tileY] = ENTITYTYPE::ENTITY_FLOOR;
			m_xGameManager->setEnemyNumber(m_xGameManager->getEnemyNumber() + 1);
			break;
		case ENEMY6:
			m_xEntityManager->AddEntity(new Enemy6(ENTITYTYPE::ENTITY_ENEMY, tileX * 40 + 1, tileY * 40 + 1, this));
			field[tileX][tileY] = ENTITYTYPE::ENTITY_FLOOR;
			m_xGameManager->setEnemyNumber(m_xGameManager->getEnemyNumber() + 1);
			break;
		case ENEMY7:
			m_xEntityManager->AddEntity(new Enemy7(ENTITYTYPE::ENTITY_ENEMY, tileX * 40 + 1, tileY * 40 + 1, this));
			field[tileX][tileY] = ENTITYTYPE::ENTITY_FLOOR;
			m_xGameManager->setEnemyNumber(m_xGameManager->getEnemyNumber() + 1);
			break;
		case DOOR:
			m_xEntityManager->AddEntity(new DoorTile(ENTITYTYPE::ENTITY_DOOR, tileX * 40, tileY * 40, this));
			field[tileX][tileY] = ENTITYTYPE::ENTITY_DOOR;
			break;
		default:
			break;
		}
		if (tileX >= 19) {
			tileY++;
			tileX = 1;
		}
		else {
			tileX++;
		}
		
	}
}