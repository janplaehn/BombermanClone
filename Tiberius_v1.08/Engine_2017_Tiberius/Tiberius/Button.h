#pragma once
#include <string>
#include <SDL_ttf.h>

class RenderManager;
class Button
{
public:
	Button(int xpos, int ypos, std::string string);
	~Button();
	std::string str_button = "";
	const int HEIGHT = 20;
	const int WIDTH = 120;
	SDL_Point position;
	SDL_Rect rect;
	const int FONTSIZE = 12;
	TTF_Font* font = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Color _textColor;
	RenderManager* m_xRenderManager = nullptr;
	void setColor(SDL_Color color);
	void update();
	void render();
	bool isActive;
	bool isEnabled = true;
};

