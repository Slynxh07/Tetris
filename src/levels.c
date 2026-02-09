#define FRAME_TIME (1.0f / 60.0f)

const float Level1 = FRAME_TIME * 60;
const float Level2 = FRAME_TIME * 50;
const float Level3 = FRAME_TIME * 40;
const float Level4 = FRAME_TIME * 30;
const float Level5 = FRAME_TIME * 20;
const float Level6 = FRAME_TIME * 10;
const float Level7 = FRAME_TIME * 5;
const float Level8 = FRAME_TIME * 4;
const float Level9 = FRAME_TIME * 3;
const float Level10 = FRAME_TIME * 2;
const float Level11 = FRAME_TIME * 1;
const float Level12 = FRAME_TIME * (1.0f / 2.0f);
const float Level13 = FRAME_TIME * (1.0f / 3.0f);
const float Level14 = FRAME_TIME * (1.0f / 4.0f);
const float Level15 = FRAME_TIME * (1.0f / 5.0f);
const float Level16 = FRAME_TIME * (1.0f / 20.0f);
const float Level17 = FRAME_TIME * (1.0f / 20.0f);
const float Level18 = FRAME_TIME * (1.0f / 20.0f);
const float Level19 = FRAME_TIME * (1.0f / 20.0f);
const float Level20 = FRAME_TIME * (1.0f / 20.0f);

int calcCurrentLevel(int totalLinesCleared)
{
    int levCalc = totalLinesCleared + 10;
    int level = levCalc / 10;
    if (level >= 20) return 20;
    return level;
}

double getIntervel(int level)
{
    switch (level)
    {
        case 1:
            return Level1;
        case 2:
            return Level2;
        case 3:
            return Level3;
        case 4:
            return Level4;
        case 5:
            return Level5;
        case 6:
            return Level6;
        case 7:
            return Level7;
        case 8:
            return Level8;
        case 9:
            return Level9;
        case 10:
            return Level10;
        case 11:
            return Level11;
        case 12:
            return Level12;
        case 13:
            return Level13;
        case 14:
            return Level14;
        case 15:
            return Level15;
        case 16:
            return Level16;
        case 17:
            return Level17;
        case 18:
            return Level18;
        case 19:
            return Level19;
        case 20:
            return Level20;
        default:
            return Level1;
    }
}