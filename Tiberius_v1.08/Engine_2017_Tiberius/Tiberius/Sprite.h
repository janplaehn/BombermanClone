#pragma once

enum ORIGIN //At the moment we will use this for our rotation only
{
	Center,
	TopLeft
};

class Sprite
{
public:
	Sprite(SDL_Texture* p_Texture, int p_iX, int p_iY, int p_iW, int p_iH);
	~Sprite();
	void SetArea(int p_iX, int p_iY, int p_iW, int p_iH);
	SDL_Rect GetArea();

	void SetSize(int p_iW, int p_iH);
	void SetWidth(int p_iW);
	int GetWidth();
	void SetHeight(int p_iH);
	int GetHeight();
	void SetPoint(int p_iX, int p_iY);
	void SetX(int p_iX);
	void SetY(int p_iY);
	void SetScale(float p_fScale);
	void animate(int frames);
	void changeAnimation(int animation);
	void hide();
	float GetScale();
	void SetAngle(double p_dAngle);
	double GetAngle();

	void SetSortingLayer(unsigned int p_iLayer);
	unsigned int GetLayer();

	void SetOrigin(int p_iX, int p_iY);
	void SetOrigin(ORIGIN p_eOrigin);
	SDL_Point GetOrigin();
	void SetFlip(SDL_RendererFlip p_Flip);
	SDL_RendererFlip GetFlip();
	SDL_Texture* GetTexture();
private:
	Sprite() = delete;
	SDL_Texture* m_Texture = nullptr;
	SDL_Rect m_Area;
	double m_dAngle = 0;
	SDL_Point m_Origin {0,0};
	float m_fScale = 1.0f;
	SDL_RendererFlip m_Flip = SDL_FLIP_NONE;
	ORIGIN m_eOrigin = ORIGIN::TopLeft;
	unsigned int m_iSortingLayer = 0;
};


