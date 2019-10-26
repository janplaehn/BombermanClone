#include "stdafx.h"
#include "StateMainMenu.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Sound.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "EngineConfig.h"
#include "IEntity.h"
#include <chrono>
#include <ctime>
#include "Music.h"
#include "StateManager.h"
#include "Button.h"
#include "LevelManager.h"
#include "Engine.h"

std::string StateMainMenu::m_sNextState = "LevelTitle";

StateMainMenu::StateMainMenu() {
	m_xButtonSingleplayer = new Button(280, 300, "Start Game");
	m_xButtonMultiplayer = new Button(280, 340, "Level Select");
	m_xButtonQuit = new Button(280, 380, "Quit Game");

	m_xButtonSingleplayer->isActive = true;

	m_xEngine = Service<Engine>::GetService();
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xInputManager = Service<InputManager>::GetService();
	m_xStateManager = Service<StateManager>::GetService();
	m_xBanner = Service<SpriteManager>::GetService()->CreateSprite("../Assets/banner.png", 0, 0, 400, 243);
	m_xTitleMusic = Service<SoundManager>::GetService()->CreateMusic("../Assets/music/menu.ogg");
	m_xLevelManager = Service<LevelManager>::GetService();
}

StateMainMenu::~StateMainMenu() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xBanner);
	Service<SoundManager>::GetService()->DestroyMusic(m_xTitleMusic);
	delete m_xButtonSingleplayer;
	delete m_xButtonMultiplayer;
	delete m_xButtonQuit;
}

void StateMainMenu::Enter() {
	m_xTitleMusic->Play();
}

bool StateMainMenu::Update(float p_fDelta) {
	m_xRenderManager->ClearBlack();

	m_xButtonSingleplayer->update();
	m_xButtonMultiplayer->update();
	m_xButtonQuit->update();

	m_xButtonSingleplayer->render();
	m_xButtonMultiplayer->render();
	m_xButtonQuit->render();

	m_xRenderManager->Draw(m_xBanner, 140, 20);

	if (m_xInputManager->IsKeyPressed(SDL_SCANCODE_UP) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_W) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_A) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_LEFT)) {
		if (m_xButtonSingleplayer->isActive) {
			m_xButtonSingleplayer->isActive = false;
			m_xButtonQuit->isActive = true;
		}
		else if (m_xButtonMultiplayer->isActive) {
			m_xButtonMultiplayer->isActive = false;
			m_xButtonSingleplayer->isActive = true;
		}
		else if (m_xButtonQuit->isActive) {
			m_xButtonQuit->isActive = false;
			m_xButtonMultiplayer->isActive = true;
		}
	}
	if (m_xInputManager->IsKeyPressed(SDL_SCANCODE_DOWN) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_S) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_D) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_RIGHT)) {
		if (m_xButtonSingleplayer->isActive) {
			m_xButtonSingleplayer->isActive = false;
			m_xButtonMultiplayer->isActive = true;
		}
		else if (m_xButtonMultiplayer->isActive) {
			m_xButtonMultiplayer->isActive = false;
			m_xButtonQuit->isActive = true;
		}
		else if (m_xButtonQuit->isActive) {
			m_xButtonQuit->isActive = false;
			m_xButtonSingleplayer->isActive = true;
		}
	}
	if (m_xInputManager->IsKeyPressed(SDL_SCANCODE_SPACE) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_RETURN)) {
		if (m_xButtonSingleplayer->isActive) {
			m_xLevelManager->setCurrentLevel(1);
			m_xStateManager->SetState("LevelTitle");
		}
		else if (m_xButtonMultiplayer->isActive) {
			m_xStateManager->SetState("LevelSelect");
		}
		else if (m_xButtonQuit->isActive) {
			m_xEngine->Shutdown();
		}
	}
	return true;
}

void StateMainMenu::Exit() {
	
}

std::string StateMainMenu::NextState() {
	return m_sNextState;
}







