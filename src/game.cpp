/*Code and engine made by Titan Game Studios 2016/2020 coded by Luiz Nai.*/
#include "game.h"

SDL_Rect baseclass::coord; //we have to actually reserve memory for the static SDL_Rect from the baseclass
int save_clock;
 
game::game()    //constructor
{					
	screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,24,SDL_FULLSCREEN);

	// button initialization
	SDL_ShowCursor(SDL_DISABLE);		
	SDL_Delay(200);

	// button initialization
	WPAD_Init();

	// Initialise the audio subsystem
	ASND_Init();
	MP3Player_Init();

	m_screen = load_image("sd:/apps/vgdb/rd/images/menu/menu.bmp");
	jaguar = load_image("sd:/apps/vgdb/rd/images/menu/jaguar.bmp");
	v_letter = load_image("sd:/apps/vgdb/rd/images/menu/imagev.bmp");
	g_letter = load_image("sd:/apps/vgdb/rd/images/menu/imageg.bmp");
	d_letter = load_image("sd:/apps/vgdb/rd/images/menu/imaged.bmp");
	b_letter = load_image("sd:/apps/vgdb/rd/images/menu/imageb.bmp");
	vgdb_logo = load_image("sd:/apps/vgdb/rd/images/menu/vgdblogo.bmp");
	showjaguar = false;
		
	baseclass::coord.x = 0;
	baseclass::coord.y = 0;
	camera.x=0;
	camera.y=0;
	counter = 0;
	total_counter = 20;
	half_total = total_counter/2;

	v_rect.x = -2;
	v_rect.y = -20;
	v_rect.w = -74;
	v_rect.h = -92;

	g_rect.x = -82;
	g_rect.y = -40;
	g_rect.w = -74;
	g_rect.h = -92;

	d_rect.x =-163;
	d_rect.y = -20;
	d_rect.w = -74;
	d_rect.h = -92;

	b_rect.x =-242;
	b_rect.y = -40;
	b_rect.w = -74;
	b_rect.h = -92;

	logo_rect.x = -4;
	logo_rect.y = -200;
	logo_rect.w = -307;
	logo_rect.h = -20;

	///////////////
	baseclass::coord.w=SCREEN_WIDTH;
	///////////////
	camera.w=SCREEN_WIDTH;
	baseclass::coord.h=SCREEN_HEIGHT;
	camera.h=SCREEN_HEIGHT;
}

///// Destroy all the variables in the memory for the game.
game::~game()
{
	SDL_FreeSurface(m_screen);
	SDL_FreeSurface(jaguar);	
	SDL_FreeSurface(v_letter);	
	SDL_FreeSurface(g_letter);	
	SDL_FreeSurface(d_letter);	
	SDL_FreeSurface(b_letter);	
	SDL_FreeSurface(vgdb_logo);	
	SDL_Quit();
}

///////Function to load the images
SDL_Surface* game::load_image(const char* filename)     //it will load an image
{
      	SDL_Surface* tmp=SDL_LoadBMP(filename); //load the BMP to a tmp variable
        SDL_Surface* tmp2=SDL_DisplayFormat(tmp);       //change it to the format of the screen
        SDL_FreeSurface(tmp);   //free the tmp, we don't need it anymore
        return tmp2;    //return
}

void game::animation() {
	counter++;

	if(counter <= half_total)
	{
		v_rect.y++;
		g_rect.y--; 
		d_rect.y++; 
		b_rect.y--; 
	}
	else
	{
		v_rect.y--;
		g_rect.y++; 
		d_rect.y--; 
		b_rect.y++; 		
	}

	if(counter==total_counter) {
		counter=0;
	}
}

///// Function to start the game
void game::start()
{	
	// to stop the while loop
	bool done = false;
	// this is the endless while loop until someone presses the home button on the wiimote

	MP3Player_PlayBuffer(sample_mp3, sample_mp3_size, NULL);

	while (!done)
    {
		// scans if a button was pressed
        WPAD_ScanPads();
		u32 held = WPAD_ButtonsHeld(0);
		
		// if the homebutton is pressed it will set done = true and it will fill the screen
		// with a black background
		if(held & WPAD_BUTTON_HOME){
			done=true;
			SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
		}

		if(held & WPAD_BUTTON_A){
			showjaguar=true;
		}
		else {
			showjaguar=false;	
		}

		SDL_FillRect(screen,NULL, 0x000000); 
		SDL_BlitSurface(m_screen,&camera,screen,NULL);
		SDL_BlitSurface(v_letter,&v_rect,screen,NULL);
		SDL_BlitSurface(g_letter,&g_rect,screen,NULL);
		SDL_BlitSurface(d_letter,&d_rect,screen,NULL);
		SDL_BlitSurface(b_letter,&b_rect,screen,NULL);
		SDL_BlitSurface(vgdb_logo,&logo_rect,screen,NULL);


		if(showjaguar) {
			SDL_BlitSurface(jaguar,&camera,screen,NULL);
		}
		else {
			animation();
		}

		SDL_Delay(50);
		
		// SDL_Flip refreshes the screen so it will show the updated screen
		SDL_Flip(screen);
    }
}