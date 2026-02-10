#ifndef SOUNDS_H
#define SOUNDS_H

#include "raylib.h"

extern Sound movePieceS;
extern Sound pieceLandedS;
extern Sound rotatePieceS;
extern Sound pieceMoveAfterClearS;
extern Sound lineClearS;
extern Sound tetrisS;
extern Sound levelUpS;
extern Sound gameOverS;

void loadSounds();
void unloadSounds();

#endif