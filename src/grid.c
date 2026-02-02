#include "grid.h"
#include <stdlib.h>
#include "raylib.h"
#include "colors.h"
#include "block.h"

#define CELL_SIZE 30

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

int isCellEmpty(Grid *g, int row, int col)
{
    return g->grid[row][col];
}

int isCellOutside(Grid *g, int row, int col)
{
    if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS) return 1;
    return 0;
}

void drawGrid(Grid *g)
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            DrawRectangle(CELL_SIZE * j, CELL_SIZE * i, CELL_SIZE, CELL_SIZE, brickColors[g->grid[i][j]]);
        }
    }
}

int setCellValue(Grid *g, int row, int col, BLOCK_TYPE val)
{
    if (g->grid[row][col] == 0) return 0;
    g->grid[row][col] = val;
    return 1;
}