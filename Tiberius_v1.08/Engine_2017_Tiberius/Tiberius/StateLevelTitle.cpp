#include "stdafx.h"
#include "StateLevelTitle.h"
#include "RenderManager.h"
#include "Service.h"
#include "LevelTitleText.h"
#include "Sound.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "EngineConfig.h"
#include "Utility.h"
#include <ctime>
#include "Music.h"
#include "StateManager.h"
#include <iostream>

std::string StateLevelTitle::m_sNextState = "Game";

StateLevelTitle::StateLevelTitle() {
	m_xTitleText = new LevelTitleText();

	m_xLevelManager = Service<LevelManager>::GetService();
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xStateManager = Service<StateManager>::GetService();
	m_xTitleMusic = Service<SoundManager>::GetService()->CreateMusic("../Assets/music/fanfare.ogg");
}

StateLevelTitle::~StateLevelTitle() {
}

void StateLevelTitle::Enter() {
	startTime = Utility::get_time();
	m_xTitleMusic->Play();
}

bool StateLevelTitle::Update(float p_fDelta) {
	m_xRenderManager->ClearBlack();
	m_xTitleText->update();
	m_xTitleText->render();

	unsigned long long currentTime = Utility::get_time();
	unsigned long long elapsedTime = currentTime - startTime;
	if (elapsedTime > 3000) {
		if (m_xLevelManager->getCurrentLevel() >= 10) {
			m_xStateManager->SetState("MainMenu");
		}
		else {
			m_xStateManager->SetState(m_sNextState);
		}
	}
	return true;
}

void StateLevelTitle::Exit() {
}

std::string StateLevelTitle::NextState() {
	return m_sNextState;
}


