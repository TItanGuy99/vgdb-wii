/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
// normal includes
#include <stdlib.h>
#include <time.h>
#include <gccore.h>
#include <wiiuse/wpad.h> 
#include <asndlib.h>
#include <mp3player.h>

// SDL includes
#include <SDL/sdl.h>
#include <SDL/sdl_image.h>
#include <SDL/SDL_mixer.h>


#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include "base.h"
// include generated header
#include "sample_mp3.h"
#ifndef GAME_H
#define GAME_H

class game:public baseclass{
	SDL_Joystick *joystick;
	int counter, total_counter, half_total, buttonCount;
	bool showjaguar;
	SDL_Surface *screen, *jaguar, *m_screen, *v_letter, *g_letter, *d_letter, *b_letter, *vgdb_logo;
	SDL_Rect camera, v_rect, g_rect, d_rect, b_rect, logo_rect;
	SDL_Surface* load_image(const char* filename); 
	void animation();
	bool running;
	static const int SCREEN_WIDTH=320;
	static const int SCREEN_HEIGHT=240;
        public:
        game();
        ~game();
        void start();
};

#endif
