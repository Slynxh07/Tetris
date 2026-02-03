#ifndef GRID_H
#define GRID_H

#define NUM_ROWS 20
#define NUM_COLS 10

typedef struct Grid
{
    int grid[NUM_ROWS][NUM_COLS];
} Grid;

Grid *createGrid();
void destroyGrid(Grid *g);
int isCellEmpty(Grid *g, int row, int col);
int isCellOutside(Grid *g, int row, int col);
int setCellValue(Grid *g, int row, int col, BLOCK_TYPE val);

#endif