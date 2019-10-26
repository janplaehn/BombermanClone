#pragma once

#include <string>
#include <vector>
#include <map>

/*The SpriteManager handles creation and deletion of textures/sprites using a vector that holds
all sprites. This way the program does not have to create entirely new objects each time a sprite is used,
but reuse sprites that are already loaded. It also makes organizing sprites easuer during development*/


class Sprite;
class RenderManager;

class SpriteManager
{
public:
	SpriteManager();
	~SpriteManager();
	bool Initialize(RenderManager* p_xRenderManager);
	/*Initialize takes a pointer to a RenderManager and stores it in m_xRenderManager. If the pointer is not
	a nullptr, it returns true.*/

	void Shutdown();
	/*Shutdown deletes all Sprites in m_Sprites and all textures in m_Textures.*/

	Sprite* CreateSprite(const std::string p_FilePath, int p_iX, int p_iY, int p_iW, int p_iH);
	/*CreateSprite takes a filepath to an image file and creates a surface from it. it then turns that surface into a texture and
	stores it in m_Textures. It also creates a new sprite using the texture, and the coordinates, width and height of
	which part of the texture should be displayed and stores the new sprite in m_Sprites.*/

	void DestroySprite(Sprite* p_xSprite);
	/*Destroy Sprite takes a pointer to a sprite as an argument. It then looks for that Sprite in m_Sprites and
	deletes it.*/

private:
	std::vector<Sprite*> m_Sprites;
	std::map<std::string, SDL_Texture*> m_Textures;
	RenderManager* m_xRenderManager = nullptr;
};

