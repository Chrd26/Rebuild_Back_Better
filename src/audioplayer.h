#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <stdarg. h>

// Read more on audio
// https://wiki.libsdl.org/SDL3_mixer/CategoryAPI
template<typename T>
class AudioPlayer
{
	static	T* 	audioFile;
	static int result;
	
public:
	static  AudioPlayer(std::string fileLocation);
	static	void PlayAudio(int loops, int fadeInTime);
	static 	void StopAudio(int timeToFadeOut);

private:
	static	~AudioPlayer();
};
