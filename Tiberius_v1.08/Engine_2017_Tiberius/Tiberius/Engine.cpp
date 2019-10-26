#include "stdafx.h"
#include "Engine.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "SpriteManager.h"
#include "StateManager.h"
#include "SoundManager.h"
#include "LevelManager.h"
#include "FontManager.h"
#include "Service.h"
#include "StateOwner.h"
#include "EngineConfig.h"
#include <cassert>

Engine::Engine()
{
	m_xRenderManager = new RenderManager();
	m_xInputManager = new InputManager();
	m_xSpriteManager = new SpriteManager(); 
	m_xStateManager = new StateManager();
	m_xSoundManager = new SoundManager();
	m_xLevelManager = new LevelManager();
	m_xFontManager = new FontManager();

	Service<SpriteManager>::SetService(m_xSpriteManager);
	Service<InputManager>::SetService(m_xInputManager);
	Service<RenderManager>::SetService(m_xRenderManager);
	Service<LevelManager>::SetService(m_xLevelManager);
	Service<StateManager>::SetService(m_xStateManager);
	Service<SoundManager>::SetService(m_xSoundManager);
	Service<FontManager>::SetService(m_xFontManager);
	Service<Engine>::SetService(this);
}

Engine::~Engine()
{
	Service<SoundManager>::SetService(nullptr);
	delete m_xSoundManager;
	m_xSoundManager = nullptr;

	delete m_xStateManager;
	m_xStateManager = nullptr;

	Service<SpriteManager>::SetService(nullptr);
	delete m_xSpriteManager;
	m_xSpriteManager = nullptr;

	Service<InputManager>::SetService(nullptr);
	delete m_xInputManager;
	m_xInputManager = nullptr;

	Service<StateManager>::SetService(nullptr);
	delete m_xStateManager;
	m_xStateManager = nullptr;

	Service<RenderManager>::SetService(nullptr);
	delete m_xRenderManager;
	m_xRenderManager = nullptr;

	Service<LevelManager>::SetService(nullptr);
	delete m_xLevelManager;
	m_xLevelManager = nullptr;

	Service<Engine>::SetService(nullptr);
}

void Engine::Initialize()
{
	int init_result = SDL_Init(SDL_INIT_EVERYTHING);
	assert(init_result == 0 && "SDL_Init Failed");

	int audio_result = Mix_OpenAudio(EngineConfig::AUDIO_FREQUENCY, EngineConfig::AUDIO_FORMAT, EngineConfig::AUDIO_CHANNELS, EngineConfig::AUDIO_CHUNKSIZE);
	assert(audio_result != -1 && "Mix_OpenAudio Failed");

	int mix_result = Mix_Init(EngineConfig::AUDIO_FLAGS);
	assert(mix_result != 0 && "Mix_Init Failed");
	
	int img_result = IMG_Init(EngineConfig::IMAGE_FLAGS);
	assert(img_result != 0 && "IMG_Init Failed");

	bool render_result = m_xRenderManager->Initialize();
	assert(render_result != 0 && "RenderManager Initialization Failed");
	
	bool input_result = m_xInputManager->Initialize();
	assert(input_result != 0 && "InputManager Initialization Failed");

	bool sprite_result = m_xSpriteManager->Initialize(m_xRenderManager);
	assert(sprite_result != 0 && "SpriteManager Initialization Failed");

	bool sound_result = m_xSoundManager->Initialize();
	assert(sound_result != 0 && "SoundManager Initialization Failed");
}

void Engine::Shutdown()
{
	m_xSoundManager->Shutdown();
	m_xSpriteManager->Shutdown();
	m_xInputManager->Shutdown();
	m_xRenderManager->Shutdown();
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
	m_bRunning = false;
}

void Engine::Run()
{
	m_bRunning = true;

	StateOwner xStateOwner(*m_xStateManager);

	while(m_bRunning)
	{
		CalculateDeltaTime();
		HandleEvents();
		m_xRenderManager->Clear();
		m_xStateManager->Update(m_fDeltaTime);
		m_xInputManager->LateUpdate(m_fDeltaTime);
		m_xRenderManager->Present();
		SDL_Delay(128);
	}
}

void Engine::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) == 1)
	{
		if (event.type == SDL_QUIT)
		{
			m_bRunning = false;
		}
		else
		{
			m_xInputManager->HandleEvents(event);
		}
	}
}

void Engine::CalculateDeltaTime()
{
	unsigned int ticks = SDL_GetTicks() - m_iLastTick;
	m_fDeltaTime = ticks * 0.001f;
	m_iLastTick = SDL_GetTicks();
}
