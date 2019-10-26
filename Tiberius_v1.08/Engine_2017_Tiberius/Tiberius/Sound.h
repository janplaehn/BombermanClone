#pragma once

class Sound
{
public:
	Sound(Mix_Chunk* p_chunk);
	~Sound();
	void Play();
	void Stop();
private:
	Mix_Chunk* m_chunk = nullptr;
	int m_iChannel = -1;
};
