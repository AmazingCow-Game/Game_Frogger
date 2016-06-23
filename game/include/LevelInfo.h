#ifndef __Game_Frogger_include_LevelInfo_h__
#define __Game_Frogger_include_LevelInfo_h__

//Game_Frogger
#include "GameFrogger_Utils.h"

NS_GAME_FROGGER_BEGIN

struct EnemyInfo
{
    int minSpeed;
    int maxSpeed;
    std::array<int, 13> pattern;
};

struct LevelInfo
{
    int      level;
    int      time;

    std::array<EnemyInfo, 5> carsInfo;
    std::array<EnemyInfo, 5> treesInfo;
    std::array<EnemyInfo, 5> turtlesInfo;
};

LevelInfo LevelInfo_GetInfoForLevel(int level);

NS_GAME_FROGGER_END

#endif // defined(__Game_Frogger_include_LevelInfo_h__) //
