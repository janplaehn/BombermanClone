#include "stdafx.h"
#include "Button.h"
#include "RenderManager.h"
#include "Service.h"
#include <SDL_ttf.h>

Button::Button(int xpos, int ypos, std::string string) {
	m_xRenderManager = Service<RenderManager>::GetService();
	font = TTF_OpenFont("../Assets/fonts/scoreboard.ttf", FONTSIZE);
	surface = TTF_RenderText_Solid(font, "0", _textColor);
	rect = { xpos, ypos, WIDTH, HEIGHT };
	isActive = false;
	isEnabled = true;
	_textColor = { 255, 255, 255, SDL_ALPHA_OPAQUE };
	str_button = string;
}


Button::~Button() {
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void Button::setColor(SDL_Color color) {
	_textColor = color;
}

void Button::update() {
	if (surface != nullptr) {
		SDL_FreeSurface(surface);
	}
	surface = TTF_RenderText_Solid(font, str_button.c_str(), _textColor);

	if (isActive) {
		if (isEnabled) {
			_textColor = { 45, 95, 29, SDL_ALPHA_OPAQUE };
		}
		else {
			_textColor = { 51, 60, 51, SDL_ALPHA_OPAQUE };
		}		
	}
	else {
		if (isEnabled) {
			_textColor = { 255, 255, 255, SDL_ALPHA_OPAQUE };
		}
		else {
			_textColor = { 125, 125, 125, SDL_ALPHA_OPAQUE };
		}
	}
}

void Button::render() {
	m_xRenderManager->drawSurface(surface, rect);
}