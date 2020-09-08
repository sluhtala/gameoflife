#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#define TITLE "Game of Life"
#define WIDTH 600
#define HEIGHT 400
#define GRID_UPDATE_DELAY 1000
#include "grid.h"
#include "SDL2/SDL.h"
//running allows application to be open
//playing is 1 if grid is updating

typedef struct	s_data
{
	int init;
	int running;
	int playing;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	Grid *grid;
}				t_data;


#endif
