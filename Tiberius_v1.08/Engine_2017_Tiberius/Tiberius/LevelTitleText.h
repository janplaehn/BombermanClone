#pragma once
#include <string>
#include <SDL_ttf.h>

class RenderManager;
class LevelManager;
class LevelTitleText
{
public:
	std::string str_time = "";
	LevelTitleText();
	~LevelTitleText();
	const int HEIGHT = 20;
	const int WIDTH = 120;
	const SDL_Point POSITION = { 280, 150 };
	SDL_Rect rect;
	const int FONTSIZE = 12;
	TTF_Font* font = nullptr;
	SDL_Surface* surface = nullptr;
	LevelManager* m_xLevelManager = nullptr;
	SDL_Color _textColor{ 255, 255, 255, SDL_ALPHA_OPAQUE };
	RenderManager* m_xRenderManager = nullptr;
	void update();
	void render();
};

