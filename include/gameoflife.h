#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#define TITLE "Game of Life"
#define WIDTH 810
#define HEIGHT 600
#define GRID_WIDTH 50
#define GRID_HEIGHT 37
#define CELL_SICE 16
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
void	render_rect_color(t_data *data, Uint8 r, Uint8 g, Uint8 b);
void	toggle_play(t_data *data, Uint32 *timer);
t_data	*initialization();
void	exit_program(t_data *data, const char *message);
void	exit_program(t_data *data);
void	refresh_game(t_data *data);

#endif
