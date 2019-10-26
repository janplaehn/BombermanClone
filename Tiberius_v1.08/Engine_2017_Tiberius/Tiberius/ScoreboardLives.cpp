#include "stdafx.h"
#include "ScoreboardLives.h"
#include "RenderManager.h"
#include "Service.h"
#include "StateGame.h"
#include "GameManager.h"
#include <SDL_ttf.h>

ScoreboardLives::ScoreboardLives(StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	font = TTF_OpenFont("../Assets/fonts/scoreboard.ttf", FONTSIZE); //Reference: http://www.mattlag.com/bitfonts/
	surface = TTF_RenderText_Solid(font, "0", _textColor);
	m_xState = state;
	rect = { POSITION.x, POSITION.y, WIDTH, HEIGHT };
}

ScoreboardLives::~ScoreboardLives() {
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void ScoreboardLives::update() {
	if (surface != nullptr) {
		SDL_FreeSurface(surface);
	}
	str_time = "LIVES " + std::to_string(m_xState->m_xGameManager->getLives());
	surface = TTF_RenderText_Solid(font, str_time.c_str(), _textColor);
}

void ScoreboardLives::render() {
	m_xRenderManager->drawSurface(surface, rect);
}