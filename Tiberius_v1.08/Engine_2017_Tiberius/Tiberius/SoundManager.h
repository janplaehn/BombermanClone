#pragma once

#include <string>
#include <vector>
#include <map>

/* This manager handles everything that has to do with music. This
includes creation and deletion of sounds and music adn Initialization/Shutdown.
This makes it easier to organize sounds and music and make sure things are done
according to RAII. It also allows us to reuse sounds without creating a new sound
every time it is played.*/

class Sound;
class Music;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	bool Initialize();
	/*Initialize returns true. This is to detect, if the SOundManager got initialized successfully.*/

	void Shutdown();
	/*Shutdown deletes every sound in m_xSounds, every sound chunk in m_xSoundChunks, every music in
	m_xMusics and every music chunk in m_xMusicChunks.*/

	Sound* CreateSound(const std::string p_FilePath);
	/*CreateSound takes the file path to a sound file and creates a sound chunk and a sound from it.
	It adds those two to m_xSoundChunks and m_xSounds. It also returns a ponter to the sound created.*/

	void DestroySound(Sound* p_xSound);
	/* DestroySound takes a pointer to a sound. It then looks for the sound in m_xSounds and deletes it.*/

	Music* CreateMusic(const std::string p_FilePath); 
	/*CreateMusic takes the file path to a music file and creates a music chunk and a music from it.
	It adds those two to m_xMusicChunks and m_xMusics. It also returns a pointer to the music created.*/

	void DestroyMusic(Music* p_xMusic);
	/* DestroyMusic takes a pointer to a music. It then looks for the music in m_xMusics and deletes it.*/

private:
	std::vector<Sound*> m_xSounds;
	std::map<std::string, Mix_Chunk*> m_xSoundChunks;
	std::vector<Music*> m_xMusics;
	std::map<std::string, Mix_Music*> m_xMusicChunks;
};

