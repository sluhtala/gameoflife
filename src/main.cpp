#include "SDL2/SDL.h"
#include <iostream>
#include <stdlib.h>
#include "grid.h"
#include "gameoflife.h"

void	exit_program(t_data *data, const char *message)
{
	std::cout << message << std::endl;
	exit_program(data);
}

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

void	render_rect_color(t_data *data, Uint8 r, Uint8 g, Uint8 b)
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

void	refresh_game(t_data *data)
{
	SDL_RenderClear(data->renderer);
	data->grid->draw(data);
	if (data->playing == 1)
		render_rect_color(data, 0, 255, 0);
	if (data->playing == 0)
		render_rect_color(data, 255, 0, 0);
	SDL_RenderPresent(data->renderer);
}

void	toggle_play(t_data *data, Uint32 *timer)
{
	data->playing = (data->playing + 1) % 2;
   	refresh_game(data);
	if (data->playing == 1)
	   *timer = SDL_GetTicks();
	else
	   *timer = 0;
}

void window_loop(t_data *data)
{
	Uint32 timer;

	timer = 0;
	while (data->running == 1)
	{
	   	if (data->playing && timer > 0 && SDL_GetTicks() - timer >= data->game_speed)
		{
			if (data->playing == 1)
	   			data->grid->update();
			refresh_game(data);
		   	timer = SDL_GetTicks();
		}
		SDL_PollEvent(&data->event);
		if (data->event.type == SDL_QUIT)
		{
			data->running = 0;
			break;
		}
		if (data->event.type == SDL_WINDOWEVENT &&
			 data->event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			refresh_game(data);
		}
		input_manager(data, &timer);
	}
}

int main()
{
	t_data *data;

	data = initialization();
	std::cout << "Welcome to game of life!" << std::endl;
	refresh_game(data);
	window_loop(data);
	if (data->running == 0)
		exit_program(data);
	return (0);
}
