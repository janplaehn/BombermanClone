#include "stdafx.h"
#include "StateLevelSelect.h"
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
#include <string>
#include "Engine.h"

std::string StateLevelSelect::m_sNextState = "LevelTitle";

StateLevelSelect::StateLevelSelect() {
	m_xButtonLevel1 = new Button(120, 300, "Level 1");
	m_xButtonLevel2 = new Button(280, 300, "Level 2");
	m_xButtonLevel3 = new Button(440, 300, "Level 3");
	m_xButtonLevel4 = new Button(120, 340, "Level 4");
	m_xButtonLevel5 = new Button(280, 340, "Level 5");
	m_xButtonLevel6 = new Button(440, 340, "Level 6");
	m_xButtonLevel7 = new Button(120, 380, "Level 7");
	m_xButtonLevel8 = new Button(280, 380, "Level 8");
	m_xButtonLevel9 = new Button(440, 380, "Level 9");
	m_xButtonMenu = new Button(280, 420, "Main Menu");

	m_xEngine = Service<Engine>::GetService();
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xInputManager = Service<InputManager>::GetService();
	m_xStateManager = Service<StateManager>::GetService();
	m_xBanner = Service<SpriteManager>::GetService()->CreateSprite("../Assets/banner.png", 0, 0, 400, 243);
	m_xTitleMusic = Service<SoundManager>::GetService()->CreateMusic("../Assets/music/menu.ogg");
	m_xErrorSound = Service<SoundManager>::GetService()->CreateSound("../Assets/sounds/error.ogg");
	m_xLevelManager = Service<LevelManager>::GetService();
}

StateLevelSelect::~StateLevelSelect() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xBanner);
	Service<SoundManager>::GetService()->DestroyMusic(m_xTitleMusic);
	Service<SoundManager>::GetService()->DestroySound(m_xErrorSound);
	delete m_xButtonLevel1;
	delete m_xButtonLevel2;
	delete m_xButtonLevel3;
	delete m_xButtonLevel4;
	delete m_xButtonLevel5;
	delete m_xButtonLevel6;
	delete m_xButtonLevel7;
	delete m_xButtonLevel8;
	delete m_xButtonLevel9;
	delete m_xButtonMenu;
}

void StateLevelSelect::Enter() {
	m_xTitleMusic->Play();
	m_xButtonLevel1->isActive = true;

	if (m_xLevelManager->getUnlockedLevelNumber() < 1) {
		m_xButtonLevel1->isEnabled = false;
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 2) {
		m_xButtonLevel2->isEnabled = false;
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 3) {
		m_xButtonLevel3->isEnabled = false;
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 4) {
		m_xButtonLevel4->isEnabled = false;
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 5) {
		m_xButtonLevel5->isEnabled = false;
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 6) {
		m_xButtonLevel6->isEnabled = false;
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 7) {
		m_xButtonLevel7->isEnabled = false;
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 8) {
		m_xButtonLevel8->isEnabled = false;
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 9) {
		m_xButtonLevel9->isEnabled = false;
	}
}

bool StateLevelSelect::Update(float p_fDelta) {
	m_xRenderManager->ClearBlack();

	m_xButtonLevel1->update();
	m_xButtonLevel2->update();
	m_xButtonLevel3->update();
	m_xButtonLevel4->update();
	m_xButtonLevel5->update();
	m_xButtonLevel6->update();
	m_xButtonLevel7->update();
	m_xButtonLevel8->update();
	m_xButtonLevel9->update();
	m_xButtonMenu->update();



	m_xButtonLevel1->render();
	m_xButtonLevel2->render();
	m_xButtonLevel3->render();
	m_xButtonLevel4->render();
	m_xButtonLevel5->render();
	m_xButtonLevel6->render();
	m_xButtonLevel7->render();
	m_xButtonLevel8->render();
	m_xButtonLevel9->render();
	m_xButtonMenu->render();


	m_xRenderManager->Draw(m_xBanner, 140, 20);

	if (m_xInputManager->IsKeyPressed(SDL_SCANCODE_UP) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_W) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_A) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_LEFT)) {
		if (m_xButtonLevel1->isActive) {
			m_xButtonLevel1->isActive = false;
			m_xButtonMenu->isActive = true;
		}
		else if (m_xButtonLevel2->isActive) {
			m_xButtonLevel2->isActive = false;
			m_xButtonLevel1->isActive = true;
		}
		else if (m_xButtonLevel3->isActive) {
			m_xButtonLevel3->isActive = false;
			m_xButtonLevel2->isActive = true;
		}
		else if (m_xButtonLevel4->isActive) {
			m_xButtonLevel4->isActive = false;
			m_xButtonLevel3->isActive = true;
		}
		else if (m_xButtonLevel5->isActive) {
			m_xButtonLevel5->isActive = false;
			m_xButtonLevel4->isActive = true;
		}
		else if (m_xButtonLevel6->isActive) {
			m_xButtonLevel6->isActive = false;
			m_xButtonLevel5->isActive = true;
		}
		else if (m_xButtonLevel7->isActive) {
			m_xButtonLevel7->isActive = false;
			m_xButtonLevel6->isActive = true;
		}
		else if (m_xButtonLevel8->isActive) {
			m_xButtonLevel8->isActive = false;
			m_xButtonLevel7->isActive = true;
		}
		else if (m_xButtonLevel9->isActive) {
			m_xButtonLevel9->isActive = false;
			m_xButtonLevel8->isActive = true;
		}
		else if (m_xButtonMenu->isActive) {
			m_xButtonMenu->isActive = false;
			m_xButtonLevel9->isActive = true;
		}
	}
	if (m_xInputManager->IsKeyPressed(SDL_SCANCODE_DOWN) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_S) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_D) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_RIGHT)) {
		if (m_xButtonLevel1->isActive) {
			m_xButtonLevel1->isActive = false;
			m_xButtonLevel2->isActive = true;
		}
		else if (m_xButtonLevel2->isActive) {
			m_xButtonLevel2->isActive = false;
			m_xButtonLevel3->isActive = true;
		}
		else if (m_xButtonLevel3->isActive) {
			m_xButtonLevel3->isActive = false;
			m_xButtonLevel4->isActive = true;
		}
		else if (m_xButtonLevel4->isActive) {
			m_xButtonLevel4->isActive = false;
			updateColor();
			m_xButtonLevel5->isActive = true;
		}
		else if (m_xButtonLevel5->isActive) {
			m_xButtonLevel5->isActive = false;
			m_xButtonLevel6->isActive = true;
		}
		else if (m_xButtonLevel6->isActive) {
			m_xButtonLevel6->isActive = false;
			m_xButtonLevel7->isActive = true;
		}
		else if (m_xButtonLevel7->isActive) {
			m_xButtonLevel7->isActive = false;
			m_xButtonLevel8->isActive = true;
		}
		else if (m_xButtonLevel8->isActive) {
			m_xButtonLevel8->isActive = false;
			m_xButtonLevel9->isActive = true;
		}
		else if (m_xButtonLevel9->isActive) {
			m_xButtonLevel9->isActive = false;
			m_xButtonMenu->isActive = true;
		}
		else if (m_xButtonMenu->isActive) {
			m_xButtonMenu->isActive = false;
			m_xButtonLevel1->isActive = true;
		}
	}
	if (m_xInputManager->IsKeyPressed(SDL_SCANCODE_SPACE) || m_xInputManager->IsKeyPressed(SDL_SCANCODE_RETURN)) {
		if (m_xButtonLevel1->isActive) {
			if (m_xLevelManager->getUnlockedLevelNumber() >= 1) {
				m_xLevelManager->setCurrentLevel(1);
				m_xStateManager->SetState("LevelTitle");
			}
			else m_xErrorSound->Play();
		}
		else if (m_xButtonLevel2->isActive) {
			if (m_xLevelManager->getUnlockedLevelNumber() >= 2) {
				m_xLevelManager->setCurrentLevel(2);
				m_xStateManager->SetState("LevelTitle");
			}
			else m_xErrorSound->Play();
		}
		else if (m_xButtonLevel3->isActive) {
			if (m_xLevelManager->getUnlockedLevelNumber() >= 3) {
				m_xLevelManager->setCurrentLevel(3);
				m_xStateManager->SetState("LevelTitle");
			}
			else m_xErrorSound->Play();
		}
		else if (m_xButtonLevel4->isActive) {
			if (m_xLevelManager->getUnlockedLevelNumber() >= 4) {
				m_xLevelManager->setCurrentLevel(4);
				m_xStateManager->SetState("LevelTitle");
			}
			else m_xErrorSound->Play();
		}
		else if (m_xButtonLevel5->isActive) {
			if (m_xLevelManager->getUnlockedLevelNumber() >= 5) {
				m_xLevelManager->setCurrentLevel(5);
				m_xStateManager->SetState("LevelTitle");
			}
			else m_xErrorSound->Play();
		}
		else if (m_xButtonLevel6->isActive) {
			if (m_xLevelManager->getUnlockedLevelNumber() >= 6) {
				m_xLevelManager->setCurrentLevel(6);
				m_xStateManager->SetState("LevelTitle");
			}
			else m_xErrorSound->Play();
		}
		else if (m_xButtonLevel7->isActive) {
			if (m_xLevelManager->getUnlockedLevelNumber() >= 7) {
				m_xLevelManager->setCurrentLevel(7);
				m_xStateManager->SetState("LevelTitle");
			}
			else m_xErrorSound->Play();
		}
		else if (m_xButtonLevel8->isActive) {
			if (m_xLevelManager->getUnlockedLevelNumber() >= 8) {
				m_xLevelManager->setCurrentLevel(8);
				m_xStateManager->SetState("LevelTitle");
			}
			else m_xErrorSound->Play();
		}
		else if (m_xButtonLevel9->isActive) {
			if (m_xLevelManager->getUnlockedLevelNumber() >= 9) {
				m_xLevelManager->setCurrentLevel(9);
				m_xStateManager->SetState("LevelTitle");
			}
			else m_xErrorSound->Play();
		}
		else if (m_xButtonMenu->isActive) {
			m_xStateManager->SetState("MainMenu");
		}
	}
	return true;
}

void StateLevelSelect::Exit() {
}

std::string StateLevelSelect::NextState() {
	return m_sNextState;
}

void StateLevelSelect::updateColor() {
	if (m_xLevelManager->getUnlockedLevelNumber() < 1) {
		m_xButtonLevel1->setColor({ 128, 128, 128, SDL_ALPHA_OPAQUE });
	}
	else {
		m_xButtonLevel1->setColor({ 255, 255, 255, SDL_ALPHA_OPAQUE });
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 2) {
		m_xButtonLevel2->setColor({ 128, 128, 128, SDL_ALPHA_OPAQUE });
	}
	else {
		m_xButtonLevel2->setColor({ 255, 255, 255, SDL_ALPHA_OPAQUE });
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 3) {
		m_xButtonLevel3->setColor({ 128, 128, 128, SDL_ALPHA_OPAQUE });
	}
	else {
		m_xButtonLevel3->setColor({ 255, 255, 255, SDL_ALPHA_OPAQUE });
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 4) {
		m_xButtonLevel4->setColor({ 128, 128, 128, SDL_ALPHA_OPAQUE });
	}
	else {
		m_xButtonLevel4->setColor({ 255, 255, 255, SDL_ALPHA_OPAQUE });
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 5) {
		m_xButtonLevel5->setColor({ 128, 128, 128, SDL_ALPHA_OPAQUE });
	}
	else {
		m_xButtonLevel5->setColor({ 255, 255, 255, SDL_ALPHA_OPAQUE });
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 6) {
		m_xButtonLevel6->setColor({ 128, 128, 128, SDL_ALPHA_OPAQUE });
	}
	else {
		m_xButtonLevel7->setColor({ 255, 255, 255, SDL_ALPHA_OPAQUE });
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 7) {
		m_xButtonLevel7->setColor({ 128, 128, 128, SDL_ALPHA_OPAQUE });
	}
	else {
		m_xButtonLevel7->setColor({ 255, 255, 255, SDL_ALPHA_OPAQUE });
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 8) {
		m_xButtonLevel8->setColor({ 128, 128, 128, SDL_ALPHA_OPAQUE });
	}
	else {
		m_xButtonLevel8->setColor({ 255, 255, 255, SDL_ALPHA_OPAQUE });
	}
	if (m_xLevelManager->getUnlockedLevelNumber() < 9) {
		m_xButtonLevel9->setColor({ 128, 128, 128, SDL_ALPHA_OPAQUE });
	}
	else {
		m_xButtonLevel9->setColor({ 255, 255, 255, SDL_ALPHA_OPAQUE });
	}
}







