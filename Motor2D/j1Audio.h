#ifndef __j1AUDIO_H__
#define __j1AUDIO_H__

#include "j1Module.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define DEFAULT_MUSIC_VOLUME 25
#define DEFAULT_FX_VOLUME 128

struct _Mix_Music;
struct Mix_Chunk;

class j1Audio : public j1Module
{
public:

	j1Audio();

	// Destructor
	virtual ~j1Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	int getMusicVolume() const;
	int getFxVolume() const;
	void setMusicVolume(float volume);
	void setFxVolume(float volume);

private:

	_Mix_Music*			music = NULL;
	p2List<Mix_Chunk*>	fx;

	int fx_volume = DEFAULT_FX_VOLUME;
	int music_volume = DEFAULT_MUSIC_VOLUME;
};

#endif // __j1AUDIO_H__