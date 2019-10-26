#include "stdafx.h"
#include "LevelTitleText.h"
#include "RenderManager.h"
#include "Service.h"
#include "LevelManager.h"
#include <SDL_ttf.h>

LevelTitleText::LevelTitleText() {
	m_xRenderManager = Service<RenderManager>::GetService();
	font = TTF_OpenFont("../Assets/fonts/scoreboard.ttf", FONTSIZE);		//Reference: http://www.mattlag.com/bitfonts/
	surface = TTF_RenderText_Solid(font, "0", _textColor);
	rect = { POSITION.x, POSITION.y, WIDTH, HEIGHT };
	m_xLevelManager = Service<LevelManager>::GetService();
}

LevelTitleText::~LevelTitleText() {
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void LevelTitleText::update() {
	if (surface != nullptr) {
		SDL_FreeSurface(surface);
	}
	if (m_xLevelManager->getCurrentLevel() == 0) {
		str_time = "MULTIPLAYER";
	}
	if (m_xLevelManager->getCurrentLevel() >= 10) {
		str_time = "THX FOR PLAYING!";
	}
	else {
		str_time = "STAGE " + std::to_string(m_xLevelManager->getCurrentLevel());
	}
	surface = TTF_RenderText_Solid(font, str_time.c_str(), _textColor);
}

void LevelTitleText::render() {
	m_xRenderManager->drawSurface(surface, rect);
}