#include "audioplayer.h"

// Music
template<>
AudioPlayer<Mix_Music>::AudioPlayer(std::string fileLocation)
{
	audioFile = Mix_LoadMUS(fileLocation.c_str());
	
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
	if (Mix_PlayingMusic() == 0)
	{
		result = Mix_FadeInMusic(audioFile, loops, fadeInTime);
	}
}

template<>
void AudioPlayer<Mix_Music>::StopAudio(int timeToFadeOut)
{
	Mix_FadeOutMusic(timeToFadeOut);
}

// Sound Effect
template<>
AudioPlayer<Mix_Chunk>::AudioPlayer(std::string fileLocation)
{
	audioFile = Mix_LoadWAV(fileLocation.c_str());
	
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





