#pragma once

class RenderManager;
class InputManager;
class SpriteManager;
class StateManager;
class SoundManager;
class LevelManager;
class FontManager;

class Engine
{
public:
	Engine();
	~Engine();
	void Initialize();
	void Shutdown();
	void Run();
private:
	void HandleEvents();
	void CalculateDeltaTime();
	float m_fDeltaTime = 0.0f;
	bool m_bRunning = false;
	unsigned int m_iLastTick = 0;
	RenderManager* m_xRenderManager = nullptr;
	InputManager* m_xInputManager = nullptr;
	SpriteManager* m_xSpriteManager = nullptr;
	StateManager* m_xStateManager = nullptr;
	SoundManager* m_xSoundManager = nullptr;
	LevelManager* m_xLevelManager = nullptr;
	FontManager* m_xFontManager = nullptr;
};