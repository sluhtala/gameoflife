#include "gameoflife.h"
#include <iostream>

t_data	*initialization()
{
	t_data *data;

	data = new t_data;	
	data->init = -1;
	data->init = SDL_Init(SDL_INIT_VIDEO);
	data->window = NULL;
	data->grid = NULL;
	data->game_speed = GAME_SPEED;
	if (data->init != 0)
	   exit_program(data, "Error initializing SDL.");
	else
	   std::cout << "SDL initialized" <<  std::endl;
	data->running = 1;
	data->playing = 0;
	if (!(data->window = SDL_CreateWindow(TITLE, 10, 10, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE)))
		exit_program(data, "Error creating window.");
	else
	   std::cout << "SDL window created" <<  std::endl;
	if (!(data->renderer = SDL_CreateRenderer(data->window, -1, 0)))
	   exit_program(data, "Error creating renderer.");
	else
	   std::cout << "SDL renderer created" <<  std::endl;
	data->grid = new Grid(GRID_WIDTH, GRID_HEIGHT, CELL_SICE);
	SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 1);
	return(data);
}
