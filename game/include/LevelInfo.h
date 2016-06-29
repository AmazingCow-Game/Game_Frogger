#ifndef __Game_Frogger_include_LevelInfo_h__
#define __Game_Frogger_include_LevelInfo_h__

//std
#include <vector>
//Game_Frogger
#include "GameFrogger_Utils.h"
#include "Tile_Constants.h"

NS_GAME_FROGGER_BEGIN

////////////////////////////////////////////////////////////////////////////////
// Types                                                                      //
////////////////////////////////////////////////////////////////////////////////
struct EnemyInfo
{
    int row;
    int direction;
    int minSpeed;
    int maxSpeed;

    std::array<int, kTilesCount_X> pattern;
};

struct LevelInfo
{
    int      level;
    int      time;

    std::vector<EnemyInfo> carsInfo;
    std::vector<EnemyInfo> treesInfo;
    std::vector<EnemyInfo> turtlesInfo;
};


////////////////////////////////////////////////////////////////////////////////
// Functions                                                                  //
////////////////////////////////////////////////////////////////////////////////
LevelInfo LevelInfo_GetInfoForLevel(int level);


NS_GAME_FROGGER_END
#endif // defined(__Game_Frogger_include_LevelInfo_h__) //
