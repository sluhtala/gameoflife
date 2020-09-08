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
	data->init = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	data->window = NULL;
	data->grid = NULL;
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
	data->grid = new Grid(20, 10, 30);
	std::cout << data->grid->width << std::endl;
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
	std::cout << "update" << std::endl;
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


void	toggle_play(t_data *data, int *timer)
{
	data->grid->draw(data);
   	if (data->playing == 0)
	{
	   *timer = SDL_GetTicks();
		//*timer = SDL_AddTimer(GRID_UPDATE_DELAY, grid_update, (void*)data);
		draw_rect_color(data, 0, 255, 0);
	}
	else
	{
	   *timer = 0;
		//SDL_RemoveTimer(*timer);
		draw_rect_color(data, 255, 0, 0);
	}
   	SDL_RenderPresent(data->renderer);
	data->playing = (data->playing + 1) % 2;
	std::cout << data->playing << std::endl;
}

void input_handler(t_data *data, int x, int y)
{
	int cell_size;
	int cellid;
	
	if (x < 0 || y < 0)
		return ;
	cell_size = data->grid->cell_size;
	if (x > data->grid->width * cell_size)
	   return ;
	if (y > data->grid->height * cell_size)
	   return ;
	cellid = y / cell_size * data->grid->width + x / cell_size; 
	data->grid->cells[cellid].toggle();
	SDL_RenderClear(data->renderer);
	data->grid->draw(data);
	if (data->playing)
		draw_rect_color(data, 0, 255, 0);
	else
		draw_rect_color(data, 255, 0, 0);
	SDL_RenderPresent(data->renderer);
}

void window_loop(t_data *data)
{
	int mouseclick;
	int timer;

	mouseclick = 0;
	timer = 0;
	while (data->running == 1)
	{
	   	if (data->playing && timer > 0 && SDL_GetTicks() - timer >= GRID_UPDATE_DELAY)
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
		if (data->event.type == SDL_KEYDOWN && data->event.key.keysym.sym == SDLK_ESCAPE)
			 data->running = 0;
		if (data->event.type == SDL_KEYDOWN && data->event.key.keysym.sym == SDLK_SPACE)
		{
		   toggle_play(data, &timer);
		}
		if (mouseclick == 0 && data->event.type == SDL_MOUSEBUTTONDOWN)
		{
			mouseclick = 1;
			input_handler(data, data->event.button.x, data->event.button.y);
		}
		if (data->event.type == SDL_MOUSEBUTTONUP)
		{
			mouseclick = 0;
		}
		if (data->event.type == SDL_KEYDOWN && data->event.key.keysym.sym == SDLK_c)
		{
			data->grid->clear_cells();
			SDL_RenderClear(data->renderer);
			data->grid->draw(data);
			if (data->playing == 1)
				draw_rect_color(data, 0, 255, 0);
			else
				draw_rect_color(data, 255, 0, 0);
			SDL_RenderPresent(data->renderer);
		}
	}
}

int main()
{
	t_data *data;

	data = initialization();
	std::cout << "Welcome to game of life!" << std::endl;
   	data->grid->cells[10].status = 1;
   	data->grid->cells[11].status = 1;
   	data->grid->cells[12].status = 1;
	grid_update(0, data);
	window_loop(data);
	if (data->running == 0)
		exit_program(data);
	return (0);
}
