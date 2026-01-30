#include "grid.h"
#include <stdlib.h>

Grid *createGrid()
{
    Grid *g = malloc(sizeof(Grid));
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for(int j = 0; j < NUM_COLS; i++)
        {
            g->grid[i][j] = 0;
        }
    }
    return g;
}

void destroyGrid(Grid *g)
{
    free(g);
}

int isCellEmpty(int row, int col)
{

}
int isCellOutside(int row, int col)
{

}