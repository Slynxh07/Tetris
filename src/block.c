#include "block.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    Posistion cells[4];
    BLOCK_TYPE blockType;
    int rowOffset;
    int colOffset;
    int rotateState;
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
    b->colOffset = 0;
    b->rowOffset = 0;
    b->rotateState = 0;
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
    b->rotateState++;
    if (b->rotateState >= 4) b->rotateState = 0;
}

void move(Block *b, Direction dir)
{
    switch (dir)
    {
        case DOWN:
            b->rowOffset++;
            break;
        case LEFT:
            b->colOffset--;
            break;
        case RIGHT:
            b->colOffset++;
            break;
        default:
            printf("Invlaid input, don't know how you got here...");
            exit(-1);
            break;
    }
}  

int checkValidMove(Block *b, Direction dir, Grid *g)
{
    switch (dir)
    {
        case DOWN:
            if (!isCellEmpty(g, b->rowOffset + 1, b->colOffset)) return 0;
            break;
        case LEFT:
            if (!isCellEmpty(g, b->rowOffset, b->colOffset - 1)) return 0;
            break;
        case RIGHT:
            if (!isCellEmpty(g, b->rowOffset, b->colOffset + 1)) return 0;
            break;
    }
    return 1;
}

void lockBlock(Block *b, Grid *g)
{
    if (setCellValue(g, b->rowOffset, b->colOffset, b->blockType))
    {
        return;
    }
}