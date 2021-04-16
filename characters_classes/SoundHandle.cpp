#ifndef SOUNDHANDLE_CPP
#define SOUNDHANDLE_CPP

#include <windows.h>
#include <string>

// Decided to use a structure as opposed to a class due to my lack of structure usage, readability and because they can both be used to achieve the same goal in this situation
struct musicControl
{
	bool musicRunning = false;
	
	bool toggleMusic()
	{
		if(musicRunning)
		{
			// 
			PlaySound(NULL, NULL, SND_NODEFAULT);
			musicRunning = false;
		}
		else
		{
			PlaySound(TEXT("IngameMusic.wav"), NULL, SND_LOOP | SND_ASYNC | SND_NODEFAULT);
			musicRunning = true;
		}
		return musicRunning;
	}
	
	void restartMusic()
	{
		musicRunning = false;
		toggleMusic();
	}
};

void playSoundEffect(const char* fileName)
{
	PlaySound(TEXT(fileName), NULL, SND_NODEFAULT | SND_FILENAME);
}

musicControl musicHandler;
#endif

