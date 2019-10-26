#include "stdafx.h"
#include "SoundManager.h"
#include "Sound.h"
#include "Music.h"

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

bool SoundManager::Initialize()
{
	return true;
}

void SoundManager::Shutdown()
{
	for (auto sound : m_xSounds)
	{
		delete sound;
		sound = nullptr;
	}
	m_xSounds.clear();
	for (auto pair : m_xSoundChunks)
	{
		Mix_FreeChunk(pair.second);
	}
	m_xSoundChunks.clear();

	for (auto music : m_xMusics)
	{
		delete music;
		music = nullptr;
	}
	m_xMusics.clear();
	for (auto pair : m_xMusicChunks)
	{
		Mix_FreeMusic(pair.second);
	}
	m_xMusicChunks.clear();
	
}

Sound * SoundManager::CreateSound(const std::string p_FilePath)
{
	auto it = m_xSoundChunks.find(p_FilePath);
	if (it == m_xSoundChunks.end())
	{
		Mix_Chunk* chunk = Mix_LoadWAV(p_FilePath.c_str());
		m_xSoundChunks.insert(std::pair<std::string, Mix_Chunk*>(p_FilePath, chunk));
		it = m_xSoundChunks.find(p_FilePath);
	}
	Sound* sound = new Sound(it->second);
	m_xSounds.push_back(sound);
	return sound;
}

void SoundManager::DestroySound(Sound * p_xSound)
{
	for (int i = 0; i<m_xSounds.size(); i++)
	{
		if (m_xSounds[i] == p_xSound)
		{
			delete m_xSounds[i];
			m_xSounds[i] = nullptr;
			m_xSounds.erase(m_xSounds.begin()+i);
			return;
		}
	}
}

Music * SoundManager::CreateMusic(const std::string p_FilePath)
{
	auto it = m_xMusicChunks.find(p_FilePath);
	if (it == m_xMusicChunks.end())
	{
		Mix_Music* chunk = Mix_LoadMUS(p_FilePath.c_str());
		m_xMusicChunks.insert(std::pair<std::string, Mix_Music*>(p_FilePath, chunk));
		it = m_xMusicChunks.find(p_FilePath);
	}
	Music* music = new Music(it->second);
	m_xMusics.push_back(music);
	return music;
}

void SoundManager::DestroyMusic(Music * p_xMusic)
{
	for (int i = 0; i<m_xMusics.size(); i++)
	{
		if (m_xMusics[i] == p_xMusic)
		{
			delete m_xMusics[i];
			m_xMusics[i] = nullptr;
			m_xMusics.erase(m_xMusics.begin() + i);
			return;
		}
	}
}
