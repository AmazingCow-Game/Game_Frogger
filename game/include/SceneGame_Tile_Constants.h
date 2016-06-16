#ifndef __Game_Frogger_include_SceneGame_Tile_Constants_h__
#define __Game_Frogger_include_SceneGame_Tile_Constants_h__

//Game_Frogger
#include "GameFrogger_Utils.h"


NS_GAME_FROGGER_BEGIN

constexpr int kTileSize     = 40;
constexpr int kTilesCount_X = 13;
constexpr int kTilesCount_Y = 14;

//Target Row
constexpr int kTargetRowTilesCount_X    = kTilesCount_X;
constexpr int kTargetRowTilesCount_Y    = 1;
constexpr int kTargetRowTiles_Initial_X = 0;
constexpr int kTargetRowTiles_Initial_Y = 2;

//Water
constexpr int kWaterTilesCount_X    = kTilesCount_X;
constexpr int kWaterTilesCount_Y    = 5;
constexpr int kWaterTiles_Initial_X = kTargetRowTiles_Initial_X;
constexpr int kWaterTiles_Initial_Y = kTargetRowTiles_Initial_Y + kTargetRowTilesCount_Y;

//Safe Row
constexpr int kSafeRowTilesCount_X    = kTilesCount_X;
constexpr int kSafeRowTilesCount_Y    = 1;
constexpr int kSafeRowTiles_Initial_X = kWaterTiles_Initial_X;
constexpr int kSafeRowTiles_Initial_Y = kWaterTiles_Initial_Y + kWaterTilesCount_Y;

//Highway
constexpr int kHighwayTilesCount_X    = kTilesCount_X;
constexpr int kHighwayTilesCount_Y    = 5;
constexpr int kHighwayTiles_Initial_X = kSafeRowTiles_Initial_X;
constexpr int kHighwayTiles_Initial_Y = kSafeRowTiles_Initial_Y + kSafeRowTilesCount_Y;

//Start Row
constexpr int kStartRowTilesCount_X    = kTilesCount_X;
constexpr int kStartRowTilesCount_Y    = 1;
constexpr int kStartRowTiles_Initial_X = kHighwayTiles_Initial_X;
constexpr int kStartRowTiles_Initial_Y = kHighwayTiles_Initial_Y + kHighwayTilesCount_Y;

NS_GAME_FROGGER_END
#endif // defined(__Game_Frogger_include_SceneGame_Tile_Constants_h__)
