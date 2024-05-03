#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
// Read more on audio
// https://wiki.libsdl.org/SDL3_mixer/CategoryAPI
class AudioPlayer
{
	T* 	audioFile;
	static int result;
	
public:
	AudioPlayer(std::string fileLocation);
	~AudioPlayer();
	void PlayAudio(int loops, int fadeInTime);
	static void StopAudio(int timeToFadeOut);
	bool plays;
};
