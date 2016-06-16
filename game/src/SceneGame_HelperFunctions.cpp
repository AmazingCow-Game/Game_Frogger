//Header
#include "SceneGame_HelperFunctions.h"
//Game_Kaboom
#include "SceneGame_Tile_Constants.h"



////////////////////////////////////////////////////////////////////////////////
// Helper Functions                                                           //
////////////////////////////////////////////////////////////////////////////////
NS_GAME_FROGGER_BEGIN

Lore::Vector2 Helper_TileToVec(int x, int y)
{
    return Lore::Vector2(x * kTileSize, y * kTileSize);
}

bool Helper_FrogIsOnStartRow(const Player &player)
{
    int row = player.getPosition().y / kTileSize;
    bool inRow = row >=  (kStartRowTiles_Initial_Y) &&
                 row < (kStartRowTiles_Initial_Y + kStartRowTilesCount_Y);

    if(inRow)
        FROGGER_DLOG("FROG is on START Row: %d", row);

    return inRow;
}

bool Helper_FrogIsOnHighwayRow(const Player &player)
{
    int row = player.getPosition().y / kTileSize;
    bool inRow = row >=  (kHighwayTiles_Initial_Y) &&
                 row < (kHighwayTiles_Initial_Y + kHighwayTilesCount_Y);

    if(inRow)
        FROGGER_DLOG("FROG is on HIGHWAY Row: %d", row);

    return inRow;
}

bool Helper_FrogIsOnWaterRow(const Player &player)
{
    int row = player.getPosition().y / kTileSize;
    bool inRow = row >=  (kWaterTiles_Initial_Y) &&
                 row < (kWaterTiles_Initial_Y + kWaterTilesCount_Y);

    if(inRow)
        FROGGER_DLOG("FROG is on WATER Row: %d", row);

    return inRow;
}

bool Helper_FrogIsOnTargetRow(const Player &player)
{
    int row = player.getPosition().y / kTileSize;
    bool inRow = row >=  (kTargetRowTiles_Initial_Y) &&
                 row < (kTargetRowTiles_Initial_Y + kTargetRowTilesCount_Y);

    if(inRow)
        FROGGER_DLOG("FROG is on TARGET Row: %d", row);

    return inRow;
}

std::string Helper_StateToStr(SceneGame::State state)
{
    switch(state)
    {
        case SceneGame::State::Playing  : return "Playing";
        case SceneGame::State::Paused   : return "Paused";
        case SceneGame::State::Defeat   : return "Defeat";
        case SceneGame::State::Victory  : return "Victory";
        case SceneGame::State::GameOver : return "Game Over";
    }

    return ""; //Make compiler happy.
}

NS_GAME_FROGGER_END
