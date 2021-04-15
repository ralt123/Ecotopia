#include <windows.h>

// Decided to use a structure as opposed to a class due to my lack of structure usage, readability and because they can both be used to achieve the same goal in this situation
struct musicControl
{
	bool musicRunning = false;
	
	bool toggleMusic()
	{
		if(musicRunning)
		{
			PlaySound(NULL, NULL, NULL);
			musicRunning = false;
		}
		else
		{
			PlaySound(TEXT("IngameMusic.wav"), NULL, SND_LOOP | SND_ASYNC);
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

musicControl musicHandler;

