#ifndef __Game_Frogger_include_SceneGame_HelperFunctions_h__
#define __Game_Frogger_include_SceneGame_HelperFunctions_h__

//Game_Frogger
#include "GameFrogger_Utils.h"
#include "Player.h"
#include "SceneGame.h"

NS_GAME_FROGGER_BEGIN

Lore::Vector2 Helper_TileToVec(int x, int y);

bool Helper_FrogIsOnStartRow  (const Player &player);
bool Helper_FrogIsOnHighwayRow(const Player &player);
bool Helper_FrogIsOnWaterRow  (const Player &player);
bool Helper_FrogIsOnTargetRow (const Player &player);

std::string Helper_StateToStr(SceneGame::State state);


NS_GAME_FROGGER_END
#endif // defined(__Game_Frogger_include_SceneGame_HelperFunctions_h__)
