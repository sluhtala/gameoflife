#include "gameoflife.h"
#include "iostream"

static void clear_grid_cells(t_data *data)
{
	data->grid->clear_cells();
	refresh_game(data);
}

static void input_toggle_cell(t_data *data, int x, int y)
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
	refresh_game(data);
}

static void adjust_gamespeed(t_data *data, int speed)
{
	float fps;

	if (data->game_speed <= 100 )
	  speed /= 10;
	if (data->game_speed == 100 && speed >= 0)
	  speed *= 10;
	data->game_speed = data->game_speed + speed;
	if (data->game_speed < 10)
		data->game_speed = 10;
	if (data->game_speed > 5000)
		data->game_speed = 5000;
	fps = 1.0 / (data->game_speed / 1000.0);
	std::cout << "Fps: " << fps << std::endl;	
	//std::cout << "Game update time: " << data->game_speed << "ms" << std::endl;	
}

void	input_manager(t_data *data, Uint32 *timer)
{
	SDL_Event e;
	static int mouseclick = 0;
	static int keypress = 0;
	static Uint32 key_timer;
	static int pressdelay = 500;

	e = data->event;
	if (SDL_GetTicks() - key_timer > pressdelay)
	{
	   	pressdelay = 100;
		key_timer = SDL_GetTicks();
		keypress = 0;
	}
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			data->running = 0;
		if (e.key.keysym.sym == SDLK_c)
			clear_grid_cells(data);
		if (e.key.keysym.sym == SDLK_SPACE)   
			toggle_play(data, timer);
		if (keypress == 0 && e.key.keysym.sym == SDLK_LEFT)
		{
	   		adjust_gamespeed(data, 100);
	  		keypress = 1;
			key_timer = SDL_GetTicks();
		}	
		if (keypress == 0 && e.key.keysym.sym == SDLK_RIGHT)
		{
			adjust_gamespeed(data, -100);
	  		keypress = 1;
			key_timer = SDL_GetTicks();
		}
	}
	if (e.type == SDL_KEYUP)
	{
		if (e.key.keysym.sym == SDLK_LEFT)	
			keypress = 0;
		if (e.key.keysym.sym == SDLK_RIGHT)	
			keypress = 0;
		pressdelay = 500;
	}
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (mouseclick == 0 && e.button.button == SDL_BUTTON_LEFT)
		{
			mouseclick = 1;
			input_toggle_cell(data, data->event.button.x, data->event.button.y);
		}
	}
	if (e.type == SDL_MOUSEBUTTONUP)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		   mouseclick = 0;
	}
}
