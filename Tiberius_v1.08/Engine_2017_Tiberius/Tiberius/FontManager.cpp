#include "stdafx.h"
#include "FontManager.h"
#include <SDL_ttf.h>


FontManager::FontManager() {
	TTF_Init();
}


FontManager::~FontManager() {
	TTF_Quit();
}
