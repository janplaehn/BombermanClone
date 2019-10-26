#include "stdafx.h"
#include "Sound.h"

Sound::Sound(Mix_Chunk * p_chunk)
{
	m_chunk = p_chunk;
}

Sound::~Sound()
{
}

void Sound::Play()
{
	m_iChannel = Mix_PlayChannel(-1, m_chunk, 0);
}

void Sound::Stop()
{
	if (m_iChannel == -1)
		return;

	if (Mix_Playing(m_iChannel))
	{
		Mix_HaltChannel(m_iChannel);
		m_iChannel = -1;
	}
}
