#include "audioplayer.h"

// Music
T *AudioPlayer<Mix_Music>::audioFile = nullptr;
AudioPlayer<Mix_Music>::result = 0;

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
	audioFile = nullptr;
}

void AudioPlayer<Mix_Music>::PlayAudio(T *audioFile, Types... types)
{
	constexpr std::size_t getSize = sizeof...(types);
	va_list args;
	va_start(args, types);
	
	switch(getSize)
	{
		case 1:
			result =  Mix_PlayMusic(audioFile, va_arg(args, 0));	
			
			if (result != 0)
			{
				exit(-1);
			}
			
			break;
		case 2:
			result = Mix_FadeInMusic(audioFile, va_arg(args, 0), 
													 va_arg(args, 1));
			
			if (result !=- 0)
			{
				exit(-1);
			}
			break;
		
		default:
			break;
	}
}

void AudioPlayer<Mix_Music>::StopAudio(int timeToFadeOut)
{
	Mix_FadeOutMusic(timeToFadeOut);
}

// Sound Effect
T *AudioPlayer<Mix_Chunk>::audioFile = nullptr;
AudioPlayer<Mix_Chunk>::channel = 0;

AudioPlayer<Mix_Chunk>::AudioPlayer(std::string fileLocation)
{
	audioFile = Mix_LoadWAV(fileLocation.c_str());
	
	if (audioFile = nullptr)
	{
		std::cout << "Failed to find audiofile"
		exit(-1);
	}
}

AudioPlayer<Mix_Chunk::~AudioPlayer()
{
	Mix_FreeChunk(audioFile);
	audioFile = nullptr;
}

void AudioPlayer<Mix_Chunk>::PlayAudio(T *audioFile, Types... types)
{
	constexpr std::size_t getSize = sizeof...(types);
	va_list args;
	va_start(args, types);
	
	switch(getSize)
	{
		case 1:
			result =  Mix_PlayChannel(-1,	audioFile,	va_arg(args, 0));	
			
			if (result	==	-1)
			{
				exit(-1);
			}
			
			break;
		case 2:
			result = Mix_FadeInChannel(-1,	audioFile, 	va_arg(args, 0), 
														va_arg(args, 1));
			
			if (result == -1)
			{
				exit(-1);
			}
			break;
		
		default:
			break;
	}
}

void AudioPlayer<Mix_Music>::StopAudio(int timeToFadeOut)
{
	Mix_FadeOutChannel(result, timeToFadeOut);
}





