#include "SDL2/SDL.h"
#include <iostream>
#include <stdlib.h>
#include "grid.h"
#include "gameoflife.h"

void	exit_program(t_data *data)
{
	if (data->init == 0)
		SDL_Quit();
	if (data->window)
		SDL_DestroyWindow(data->window);
	if (data->renderer)
	   SDL_DestroyRenderer(data->renderer);
	delete(data->grid);
	delete(data);
	std::cout << "Good bye!" << std::endl;
	exit(0);
}

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
	   exit_program(data);
	else
	   std::cout << "SDL initialized" <<  std::endl;
	data->running = 1;
	data->playing = 0;
	if (!(data->window = SDL_CreateWindow(TITLE, 10, 10, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE)))
		exit_program(data);
	else
	   std::cout << "SDL window created" <<  std::endl;
	if (!(data->renderer = SDL_CreateRenderer(data->window, -1, 0)))
	   exit_program(data);
	else
	   std::cout << "SDL renderer created" <<  std::endl;
	data->grid = new Grid(GRID_WIDTH, GRID_HEIGHT, CELL_SICE);
	SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 1);

	return(data);
}

void	draw_rect_color(t_data *data, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Rect rect;

	SDL_SetRenderDrawColor(data->renderer, r, g, b, 1);
	rect.x = 0;
	rect.y = 0;
	rect.w = data->grid->width * data->grid->cell_size;
	rect.h = data->grid->height * data->grid->cell_size;
	SDL_RenderDrawLine(data->renderer, rect.x, rect.y, rect.w, 0);
	SDL_RenderDrawLine(data->renderer, rect.w, 0, rect.w, rect.h);
	SDL_RenderDrawLine(data->renderer, 0, rect.h, rect.w, rect.h);
	SDL_RenderDrawLine(data->renderer, 0, rect.y, rect.x, rect.h);
	SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 1);
}

Uint32	grid_update(Uint32 interval, void *param)
{
	t_data *data;
	SDL_Rect rect;
	int i;

	data = (t_data*)param;
	i = 0;
	if (data->playing == 1)
	   data->grid->update();
	SDL_RenderPresent(data->renderer);
	SDL_RenderClear(data->renderer);
	data->grid->draw(data);
	if (data->playing == 1)
		draw_rect_color(data, 0, 255, 0);
	else
		draw_rect_color(data, 255, 0, 0);
	SDL_RenderPresent(data->renderer);
	return(interval);
}

void	toggle_play(t_data *data, Uint32 *timer)
{
	data->grid->draw(data);
   	if (data->playing == 0)
	{
	   *timer = SDL_GetTicks();
		draw_rect_color(data, 0, 255, 0);
	}
	else
	{
	   *timer = 0;
		draw_rect_color(data, 255, 0, 0);
	}
   	SDL_RenderPresent(data->renderer);
	data->playing = (data->playing + 1) % 2;
}

void window_loop(t_data *data)
{
	int mouseclick;
	Uint32 timer;

	mouseclick = 0;
	timer = 0;
	while (data->running == 1)
	{
	   	if (data->playing && timer > 0 && SDL_GetTicks() - timer >= data->game_speed)
		{
			grid_update(0, (void*)data);
			timer = SDL_GetTicks();
		}
		SDL_PollEvent(&data->event);
		if (data->event.type == SDL_QUIT)
		{
			data->running = 0;
			break;
		}
		input_manager(data, &timer);
	}
}

int main()
{
	t_data *data;

	data = initialization();
	std::cout << "Welcome to game of life!" << std::endl;
	grid_update(0, data);
	window_loop(data);
	if (data->running == 0)
		exit_program(data);
	return (0);
}
