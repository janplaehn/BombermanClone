#pragma once
class Music
{
public:
	Music(Mix_Music* p_music);
	~Music();
	void Play();
	void Stop();
private:
	Mix_Music* m_music = nullptr;
};

