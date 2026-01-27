#include "block.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    Posistion cells[4];
    BLOCK_TYPE blockType;
} Block;

Block *createBlock(BLOCK_TYPE blockType)
{
    Block *b = malloc(sizeof(Block));
    b->blockType = blockType;
    switch (blockType)
    {
    case ORANGE_RICKY:
        break;
    case BLUE_RICKY:
        break;
    case CLEVELAND_Z:
        break;
    case RHODE_ISLAND_Z:
        break;
    case HERO:
        break;
    case TEEWEE:
        break;
    case SMASHBOY:
        break;
    default:
        printf("Error creating block...");
        exit(-1);
        break;
    }
    return b;
}

void destroyBlock(Block *b)
{
    free(b);
}