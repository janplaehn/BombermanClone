#include "stdafx.h"
#include "ScoreboardTime.h"
#include "RenderManager.h"
#include "Service.h"
#include "StateGame.h"
#include "GameManager.h"
#include <SDL_ttf.h>


ScoreboardTime::ScoreboardTime(StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	font = TTF_OpenFont("../Assets/fonts/scoreboard.ttf", FONTSIZE);		//Reference: http://www.mattlag.com/bitfonts/
	surface = TTF_RenderText_Solid(font, "0", _textColor);
	m_xState = state;
	rect = { POSITION.x, POSITION.y, WIDTH, HEIGHT };
}

ScoreboardTime::~ScoreboardTime() {
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void ScoreboardTime::update() {
	str_time = "TIME " +  std::to_string(m_xState->m_xGameManager->getRemainingTime());
	surface = TTF_RenderText_Solid(font, str_time.c_str(), _textColor);
}

void ScoreboardTime::render() {
	m_xRenderManager->drawSurface(surface, rect);
}
