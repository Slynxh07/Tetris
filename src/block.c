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
        b->cells[0] = (Posistion){ 0, 0 };
        b->cells[1] = (Posistion){ 0, 0 };
        b->cells[2] = (Posistion){ 0, 0 };
        b->cells[3] = (Posistion){ 0, 0 };
        break;
    case BLUE_RICKY:
        b->cells[0] = (Posistion){ 0, 0 };
        b->cells[1] = (Posistion){ 0, 0 };
        b->cells[2] = (Posistion){ 0, 0 };
        b->cells[3] = (Posistion){ 0, 0 };
        break;
    case CLEVELAND_Z:
        b->cells[0] = (Posistion){ 0, 0 };
        b->cells[1] = (Posistion){ 0, 0 };
        b->cells[2] = (Posistion){ 0, 0 };
        b->cells[3] = (Posistion){ 0, 0 };
        break;
    case RHODE_ISLAND_Z:
        b->cells[0] = (Posistion){ 0, 0 };
        b->cells[1] = (Posistion){ 0, 0 };
        b->cells[2] = (Posistion){ 0, 0 };
        b->cells[3] = (Posistion){ 0, 0 };
        break;
    case HERO:
        b->cells[0] = (Posistion){ 0, 0 };
        b->cells[1] = (Posistion){ 0, 0 };
        b->cells[2] = (Posistion){ 0, 0 };
        b->cells[3] = (Posistion){ 0, 0 };
        break;
    case TEEWEE:
        b->cells[0] = (Posistion){ 0, 0 };
        b->cells[1] = (Posistion){ 0, 0 };
        b->cells[2] = (Posistion){ 0, 0 };
        b->cells[3] = (Posistion){ 0, 0 };
        break;
    case SMASHBOY:
        b->cells[0] = (Posistion){ 0, 0 };
        b->cells[1] = (Posistion){ 0, 0 };
        b->cells[2] = (Posistion){ 0, 0 };
        b->cells[3] = (Posistion){ 0, 0 };
        break;
    default:
        printf("Error creating block...");
        exit(-1);
        break;
    }
    return b;
}

BLOCK_TYPE getBlockType(Block *b)
{
    return b->blockType;
}

void destroyBlock(Block *b)
{
    free(b);
}

void rotate(Block *b)
{

}

void move(Block *b, Direction dir)
{

}  

void checkValidMove(Block *b, Direction dir)
{

}