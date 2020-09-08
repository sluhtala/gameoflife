#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#define TITLE "Game of Life"
#define WIDTH 800
#define HEIGHT 600
#define GRID_WIDTH 20
#define GRID_HEIGHT 15
#define CELL_SICE 30
#define GAME_SPEED 600
#include "grid.h"
#include "SDL2/SDL.h"
//running allows application to be open
//playing is 1 if grid is updating

typedef struct	s_data
{
	int init;
	int running;
	int playing;
	int game_speed;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	Grid *grid;
}				t_data;

void	input_manager(t_data *data, Uint32 *timer);
void	draw_rect_color(t_data *data, Uint8 r, Uint8 g, Uint8 b);
void	toggle_play(t_data *data, Uint32 *timer);

#endif
