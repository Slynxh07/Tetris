#include "grid.h"
#include <stdlib.h>
#include "raylib.h"
#include "colors.h"
#include <stdio.h>

#define CELL_SIZE 30

Grid *createGrid()
{
    Grid *g = malloc(sizeof(Grid));
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for(int j = 0; j < NUM_COLS; j++)
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

void drawTGrid(const Grid *g)
{
	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			int cellValue = g->grid[row][col];
			DrawRectangle(col * CELL_SIZE + 11, row * CELL_SIZE + 11, CELL_SIZE - 1, CELL_SIZE - 1, brickColors[cellValue]);
		}
	}
}

int isCellEmpty(const Grid *g, const int row, const int col)
{
    return g->grid[row][col] == 0;
}

int isCellOutside(const int row, const int col)
{
    if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS) return 1;
    return 0;
}

void drawGrid(const Grid *g)
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            DrawRectangle(CELL_SIZE * j, CELL_SIZE * i, CELL_SIZE, CELL_SIZE, brickColors[g->grid[i][j]]);
        }
    }
}

void setCellValue(Grid *g, const int row, const int col, const int val)
{
    g->grid[row][col] = val;
}
