#include "grid.h"
#include "gameoflife.h"

Grid::Grid(int w, int h, int size)
{
	width = w;
	height = h;
	cell_size = size;
	cells = new Cell[h * w];
}
#include <iostream>


void Grid::draw(t_data *data)
{
	SDL_Rect rect;
	int i;
	i = 0;
	while (i < width * height)
	{
		SDL_SetRenderDrawColor(data->renderer, 255, 255, 255, 1);
		rect.x = cell_size * (i % width);
		rect.y = i / width * cell_size;
		rect.w = cell_size;
		rect.h = cell_size;
		if (cells[i].status == 0)
		   SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 1);
		SDL_RenderFillRect(data->renderer, &rect);
		SDL_SetRenderDrawColor(data->renderer, 255, 255, 255, 1);
		SDL_RenderDrawRect(data->renderer, &rect);
		i++;
	}
}

void Grid::clear_cells()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cells[y * width + x].status = 0;
		}
	}
}

int	calculate_health(Grid *grid, Cell *cells, int id)
{
	int health;
	int x;
	int y;

	x = id % grid->width;
	y = id / grid->width;
	health = 0;
	if (x - 1 >= 0 && y - 1 >= 0)
		health += cells[id - grid->width - 1].status;
	if (y - 1 >= 0)
		health += cells[id - grid->width].status;
	if (x + 1 < grid->width && y - 1 >= 0)
		health += cells[id - grid->width + 1].status;
	if (x != 0)
		health += cells[id - 1].status;
	if (x != grid->width - 1)
		health += cells[id + 1].status;
	if (x != 0 && y != grid->height - 1)
		health += cells[id + grid->width - 1].status;
	if (y + 1 < grid->height)
		health += cells[id + grid->width].status;
	if (x != grid->width - 1 && y != grid->height - 1)
		health += cells[id + grid->width + 1].status;
	return (health);
}

void Grid::update()
{
   int id;
 
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			id = y * width + x;
			cells[id].health = calculate_health(this, cells, y * width + x);
		}
	}
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			  id = y * width + x;
		   if (y == 1 && x == 1)
		   		std::cout << cells[id].health << std::endl;
			if (cells[id].status == 1)
			{
				if (cells[id].health < 2 || cells[id].health > 3)
				   cells[id].status = 0;
			}
			else
			{
				if (cells[id].health == 3)
					cells[id].status = 1;	   
			}
			cells[id].health = 0;
		}
	}

}

Cell::Cell()
{
	status = 0;
	health = 0;
}

void Cell::toggle()
{
	status = (status + 1) % 2;
}
