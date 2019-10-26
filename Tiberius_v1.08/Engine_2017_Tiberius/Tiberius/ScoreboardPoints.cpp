#include "stdafx.h"
#include "ScoreboardPoints.h"
#include "RenderManager.h"
#include "Service.h"
#include "StateGame.h"
#include "GameManager.h"
#include <SDL_ttf.h>

ScoreboardPoints::ScoreboardPoints(StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	font = TTF_OpenFont("../Assets/fonts/scoreboard.ttf", FONTSIZE);		//Reference: http://www.mattlag.com/bitfonts/
	surface = TTF_RenderText_Solid(font, "0", _textColor);
	m_xState = state;
	rect = { POSITION.x, POSITION.y, WIDTH, HEIGHT };
}

ScoreboardPoints::~ScoreboardPoints() {
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void ScoreboardPoints::update() {
	if (surface != nullptr) {
		SDL_FreeSurface(surface);
	}
	str_time = "SCORE " + std::to_string(m_xState->m_xGameManager->getScore());
	surface = TTF_RenderText_Solid(font, str_time.c_str(), _textColor);
}

void ScoreboardPoints::render() {
	m_xRenderManager->drawSurface(surface, rect);
}