#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <iostream>
#include <future>

// Read more on audio
// https://wiki.libsdl.org/SDL3_mixer/CategoryAPI
template<typename T>
class AudioPlayer
{
	T* 	audioFile;
	int result;
	
public:
	AudioPlayer(std::string fileLocation);
	~AudioPlayer();
	void PlayAudio(int loops, int fadeInTime);
	void StopAudio(int timeToFadeOut);
	bool plays;
};
