#include "stdafx.h"
#include "Music.h"

Music::Music(Mix_Music * p_music)
{
	m_music = p_music;
}

Music::~Music()
{
}

void Music::Play()
{
	Mix_PlayMusic(m_music,-1);
}

void Music::Stop()
{
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}
}
