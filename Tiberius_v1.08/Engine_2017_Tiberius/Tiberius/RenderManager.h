#pragma once

#include <list>

/*This manager handles everything that has to do with rendering of game objects in
the game. It draws sprites, shapes and fonts. This is to handle the layout of the
game as well of keeping track of RAII of graphic elements. */

class Sprite;

class RenderManager
{
public:
	RenderManager();
	~RenderManager();
	bool Initialize();
	/*Initialize creates a Window, sets a Window icon stored in Assets/icon.png and creates a Renderer.*/

	void Shutdown();
	/*Shutdown destroys the Window and the Renderer.*/

	void Clear();
	/*Clear sets the RenderDrawColor to a green colour and clears the renderer, which means painting it in
	that color.*/

	void ClearBlack();
	/*Clear sets the RenderDrawColor to a black colour and clears the renderer, which means painting it in
	that color.*/

	void Present();
	/*Present calls the function DrawData and updates the screen with SDL_RenderPresent.*/

	void Draw(Sprite* p_xSprite, int p_iX, int p_iY);
	/*Draw takes a sprite and a position, turns it into RenderData and adds it to the list m_axRenderData,
	so that it gets rendered, when DrawData is called.*/

	void DebugDrawRect(int p_iX, int p_iY, int p_iW, int p_iH);
	void DebugDrawRect(SDL_Rect p_rect);
	/*DebugDrawRect takes a Rect or x, y, w and h values of a rect and turns it into a rect then.
	Afterwards, it adds that rect to m_axDebugData, so that it gets rendered, when DrawData is called.*/

	void SetCameraPosition(int p_iX, int p_iY);
	/*SetCameraPosition takes two ints x and y and sets the CameraOffset of everything that is drawn.*/

	void ModifyCameraPosition(int p_iX, int p_iY);
	/*SetCameraPosition takes two ints x and y and increases or lowers the CameraOffset of everything
	that is drawn.*/

	void drawSurface(SDL_Surface *surface, SDL_Rect & rect);
	/*drawSurface takes a surface, turns it into a texture and renders it.*/

	SDL_Point GetCameraPosition();
	/*GetCameraPosition returns the CameraOffset as an SDL_Point.*/

	SDL_Renderer* GetRenderer();
	/*GetRenderer returns a pointer to the renderer.*/
	
private:
	struct RenderData
	{
		Sprite* sprite;
		int x;
		int y;
	};

	void DrawData();
	/*DrawData renders everything in m_axRenderData and m_axDebugData.*/

	SDL_Texture * texture = nullptr;
	std::list<RenderData> m_axRenderData;
	std::list<SDL_Rect> m_axDebugData;
	std::list<SDL_Texture*> m_axTextureData;
	SDL_Window* m_xWindow = nullptr;
	SDL_Renderer* m_xRenderer = nullptr;
	SDL_Point m_CameraOffset { 0,0 };
	
};

