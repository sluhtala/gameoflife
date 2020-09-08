#ifndef GRID_H
#define GRID_H

typedef struct s_data t_data;
class Cell
{
	public:
		int status;
		Cell();
		void toggle();
		int health;
};

class Grid
{
	public:
		int width;
		int height;
		Grid(int w, int h, int size);
		void update();
		void draw(t_data *data);
		void clear_cells();
		int cell_size;
		Cell *cells;		
};


#endif
