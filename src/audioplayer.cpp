#include "audioplayer.h"

// Music
template<>
int AudioPlayer<Mix_Music>::result = 0;

template<>
AudioPlayer<Mix_Music>::AudioPlayer(std::string fileLocation)
{
	auto getFile = std::async(std::launch::async, Mix_LoadMUS, fileLocation.c_str());
	getFile.wait();
	audioFile = getFile.get();
	
	if (audioFile == nullptr)
	{
		std::cout << "Failed to find audiofile ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
}

template<>
AudioPlayer<Mix_Music>::~AudioPlayer()
{
	Mix_FreeMusic(audioFile);
	audioFile = nullptr;
}

template<>
void AudioPlayer<Mix_Music>::PlayAudio(int loops, int fadeInTime)
{
	result = Mix_FadeInMusic(audioFile, loops, fadeInTime);
	plays = true;
}

template<>
void AudioPlayer<Mix_Music>::StopAudio(int timeToFadeOut)
{
	Mix_FadeOutMusic(timeToFadeOut);
}

// Sound Effect
template<>
int AudioPlayer<Mix_Chunk>::result = 0;

template<>
AudioPlayer<Mix_Chunk>::AudioPlayer(std::string fileLocation)
{
	auto getFile = std::async(std::launch::async, Mix_LoadWAV, fileLocation.c_str());
	getFile.wait();
	audioFile = getFile.get();
	
	if (audioFile == nullptr)
	{
		std::cout << "Failed to find audiofile" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
}

template<>
AudioPlayer<Mix_Chunk>::~AudioPlayer()
{
	Mix_FreeChunk(audioFile);
	audioFile = nullptr;
}

template<>
void AudioPlayer<Mix_Chunk>::PlayAudio(int loops, int fadeInTime)
{
	if (Mix_Playing(result) == 0) 
	{
		result = Mix_FadeInChannel(-1,	audioFile, loops, fadeInTime);
	}
}

template<>
void AudioPlayer<Mix_Chunk>::StopAudio(int timeToFadeOut)
{
	Mix_FadeOutChannel(result, timeToFadeOut);
}





