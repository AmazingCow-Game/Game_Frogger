#ifndef __Game_Frogger_include_SceneGame_HelperFunctions_h__
#define __Game_Frogger_include_SceneGame_HelperFunctions_h__

//Game_Frogger
#include "GameFrogger_Utils.h"
#include "Player.h"
#include "SceneGame.h"
#include "LevelInfo.h"
#include "Tile_Constants.h"

NS_GAME_FROGGER_BEGIN

////////////////////////////////////////////////////////////////////////////////
// Tiles                                                                      //
////////////////////////////////////////////////////////////////////////////////
Lore::Vector2 Helper_TileToVec(int x, int y);

bool Helper_FrogIsOnStartRow  (const Player &player);
bool Helper_FrogIsOnHighwayRow(const Player &player);
bool Helper_FrogIsOnWaterRow  (const Player &player);
bool Helper_FrogIsOnTargetRow (const Player &player);

////////////////////////////////////////////////////////////////////////////////
// State                                                                      //
////////////////////////////////////////////////////////////////////////////////
std::string Helper_StateToStr(SceneGame::State state);


////////////////////////////////////////////////////////////////////////////////
// Enemies Creation                                                           //
////////////////////////////////////////////////////////////////////////////////
void Helper_createCar(
    const LevelInfo                   &levelInfo,
    std::vector<std::shared_ptr<Car>> &carsVec,
    std::vector<Enemy *>              &enemiesVec
);

void Helper_createTree(
    const LevelInfo                    &levelInfo,
    std::vector<std::shared_ptr<Tree>> &treesVec,
    std::vector<Enemy *>               &enemiesVec
);

void Helper_createTurtle(
    const LevelInfo                      &levelInfo,
    std::vector<std::shared_ptr<Turtle>> &turtlesVec,
    std::vector<Enemy *>                 &enemiesVec
);

NS_GAME_FROGGER_END
#endif // defined(__Game_Frogger_include_SceneGame_HelperFunctions_h__)
