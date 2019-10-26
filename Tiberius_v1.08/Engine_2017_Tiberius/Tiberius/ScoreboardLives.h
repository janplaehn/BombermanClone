#pragma once
#include <string>
#include <SDL_ttf.h>

class GameManager;
class RenderManager;
class StateGame;
class ScoreboardLives {
public:
	std::string str_time = "";
	ScoreboardLives(StateGame* state);
	~ScoreboardLives();
	const int HEIGHT = 20;
	const int WIDTH = 80;
	const SDL_Point POSITION = { 280, 10 };
	SDL_Rect rect;
	const int FONTSIZE = 12;
	TTF_Font* font = nullptr;
	StateGame* m_xState = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Color _textColor{ 255, 255, 255, SDL_ALPHA_OPAQUE };
	RenderManager* m_xRenderManager = nullptr;
	void update();
	void render();
};

