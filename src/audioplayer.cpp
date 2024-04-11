#include "audioplayer.h"

// Music
template<>
typedef *AudioPlayer<Mix_Music>::audioFile = nullptr;

AudioPlayer<Mix_Music>::AudioPlayer(std::string fileLocation)
{
	audioFile = Mix_LoadMUS(fileLocation.c_str());
	
	if (audioFile = nullptr)
	{
		std::cout << "Failed to find audiofile"
		exit(-1);
	}
}

AudioPlayer<Mix_Music::~AudioPlayer()
{
	Mix_FreeMusic(audioFile);
}

void AudioPlayer<Mix_Music>::PlayAudio(T *audioFile, Types... types)
{
	constexpr std::size_t getSize = sizeof...(types);
	va_list args;
	va_start(args, types);
	
	switch(getSize)
	{
		case 1:
			int getStat =  Mix_PlayMusic(audioFile, va_arg(args, 0));	
			
			if (getSat != 0)
			{
				exit(-1);
			}
			
			break;
		case 2:
			int getStat = Mix_FadeInMusic(audioFile, va_arg(args, 0), 
													 va_arg(args, 1));
			
			if (getStat !=- 0)
			{
				exit(-1);
			}
		
		default:
			break;
	}
}

void AudioPlayer<Mix_Music>::StopAudio(int timeToFadeOut)
{
	Mix_FadeOutMusic(timeToFadeOut);
}



