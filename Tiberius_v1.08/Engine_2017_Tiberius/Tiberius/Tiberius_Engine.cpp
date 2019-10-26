/*
	v 1.02 
	- Changes/fixes since lecture 2017-11-21
		-	Moved the dynamic object creation of RenderManager from Engine::Initialize to Engine::Engine
		-	Moved the dynamic object removal of RenderManager from Engine::Shutdown to Engine::~Engine	
		-   Changed Engine::Initialize to return void type instead of bool
		-	Removed the assert from RenderManager::Initialize and changed it to return false if instead

    v 1.03 
	- Changes/fixes since lecture 2017-11-24
	    -   RenderManager::Draw now also takes 2 ints (position) as parameter for destination rectangle to draw to (width and height taken from the sprite)
		-   Sprite Class, changed public member variables to be private and added multiple get/set functions
		-   SpriteManager::CreateSprite, added 4 integers to argument list of the function that is used to define the source area of the texture loaded
		
	v 1.04 
	- Changes/fixes since lecture 2017-11-28
	    -   Cleaned up some test code and added comments for test code in Engine::Run
		-   Cleaned up IEntity.h, removed IEntity.cpp since we will have templated function in .h file
		
	v 1.05 
	- Changes/fixes since lecture 2017-12-01
	    -   Cleaned up test code from Engine.h and Engine.cpp, moved to the example CONCRETE_State, removed some includes
		-   Created folder structure an sorted .h / .cpp files in the solution into the folder structure
		-   Added/Changed a A LOT of test code to CONCRETE_State, to be able to move between two states to see it is working
		-   Added functionality to Press W to switch between State1 and State2
		-   Made CollisionManager uncopyable and corrected the name
		-   Cleaned up std::cout code from various parts of the project
		-   Added version numbers to this change log, and current version
		-   Added copyright and license to StateManager.h and StateManager.cpp

	v 1.06 
	- Changes/fixes since lecture 2017-12-05
	    -   Finished SoundManager implementation
		-   Moved sound test code from Engine class to CONCRETE_State / SoundManager
		-   Added SoundManager new/delete/SetService in Engine.cpp
		-   Added EngineConfig.cpp and moved all definitions from EngineConfig.h to the .cpp file
		-   Added Audio configurations to EngineConfig, Mix_Init in Engine.cpp and the SoundManager class uses these
	
	v 1.07 
	- Changes/fixes since lecture 2017-12-08
		- Added important non copy information to the CONCRETE_State and CONCRETE_Entity classes
		- Refactoredd and removed all naming convention using p for pointer (m_px -> m_x and m_apx -> m_ax)
		- Added IMG_Init flag param to EngineConfig class, Engine class uses these when initialising IMG_Init
		- Moved OpenAudio from AudioManager to Engine, apparantly you should OpenAudio 
		  before using Mix_Init and CloseAudio before Mix_Quit! Who would have guessed! I♥LOGIC
	
	v 1.08 
	- Changes during lecture 2017-12-12
		- Updated RenderManager with SDL_RenderCopyEx, to be able to flip and rotate sprites, update sprite class with origin, flip and angle
		- Implemented Camera / Offset functionality inside the RenderManager
		- Implemented Collision Pairs (std::vector<std::pair<entity_type1, entity_type2>>), you must now add collisionpairs of entity types to get collision responses
		- Implement Rendering Layer inside the RenderManager, it now does not render instantly everything sent to it, but stores the data
		  in a list. It then renders the list before presenting, there is currently no sorting happening this needs to be implemented if you
		  want to use it. Added layer into the sprite class: suggestion to render layer 0 furthest away, 1 ontop of layer 0, 2 ontop of layer 1 < less,
		  another is to render higher Y position sprites before lower ones, or a combination of the two.
	 - Changes/fixes since lecture 2017-12-12
	    - Added list of SDL_Rect in RenderManager, to gather and render all debugdraws after all sprite draws.

		Current Version 1.08
*/



#include "stdafx.h"
#include "Engine.h"

int main(int ac, char** av)
{
	Engine xTiberius;
	xTiberius.Initialize();
	xTiberius.Run();
	xTiberius.Shutdown();

    return 0;
}

