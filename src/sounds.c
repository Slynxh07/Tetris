#include "sounds.h"

Sound movePieceS;
Sound pieceLandedS;
Sound rotatePieceS;
Sound pieceMoveAfterClearS;
Sound lineClearS;
Sound tetrisS;
Sound levelUpS;
Sound gameOverS;

void loadSounds()
{
    movePieceS = LoadSound("Assets/Sound/move_piece.wav");
    pieceLandedS = LoadSound("Assets/Sound/piece_landed.wav");
    rotatePieceS = LoadSound("Assets/Sound/rotate_piece.wav");
    pieceMoveAfterClearS = LoadSound("Assets/Sound/piece_falling_after_line_clear.wav");
    lineClearS = LoadSound("Assets/Sound/line_clear.wav");
    tetrisS = LoadSound("Assets/Sound/tetris_4_lines.wav");
    levelUpS = LoadSound("Assets/Sound/level_up_jingle.wav");
    gameOverS = LoadSound("Assets/Sound/game_over.wav");
}

void unloadSounds()
{
    UnloadSound(movePieceS);
    UnloadSound(pieceLandedS);
    UnloadSound(rotatePieceS);
    UnloadSound(pieceMoveAfterClearS);
    UnloadSound(lineClearS);
    UnloadSound(tetrisS);
    UnloadSound(levelUpS);
    UnloadSound(gameOverS);
}