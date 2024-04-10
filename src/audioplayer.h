#include <SDL3_mixer/SDL_mixer.h>
#include <string>

// Read more on audio
// https://wiki.libsdl.org/SDL3_mixer/CategoryAPI
template<typename T, typename... Types>
class AudioPlayer
{
	T* audio_file;
	
public:
	AudioPlayer(std::string fileLocation);
	void Play_Audio(Types... types);

private:
	~AudioPlayer();
};
