//Header
#include "SceneGame_HelperFunctions.h"
//Game_Kaboom
#include "SceneGame_Tile_Constants.h"

NS_GAME_FROGGER_BEGIN

////////////////////////////////////////////////////////////////////////////////
// Tiles                                                                      //
////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////
// State                                                                      //
////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////
// Enemies Creation                                                           //
////////////////////////////////////////////////////////////////////////////////
void Helper_createCar(
    const LevelInfo                   &levelInfo,
    std::vector<std::shared_ptr<Car>> &carsVec,
    std::vector<Enemy *>              &enemiesVec)
{
    auto gm = Lore::GameManager::instance();
    for(int i = 0; i < levelInfo.carsInfo.size(); ++i)
    {
        const auto& carInfo = levelInfo.carsInfo[i];
        //Decide Speed
        auto finalSpeed = gm->getRandomNumber(carInfo.minSpeed,
                                              carInfo.maxSpeed);

        //Build the cars with the pattern.
        for(int j = 0; j < carInfo.pattern.size(); ++j)
        {
            //Empty slot...
            if(carInfo.pattern[j] == 0)
                continue;

            auto car = std::make_shared<Car>();

            car->setSpeed(Lore::Vector2(finalSpeed, 0));
            car->setPosition(
                Helper_TileToVec(kHighwayTiles_Initial_X + j,
                                 kHighwayTiles_Initial_Y + i)
            );

            car->setMovementBounds(kHighwayTiles_Initial_X * kTileSize,
                                   kHighwayTilesCount_X    * kTileSize);

            carsVec.push_back   (car);
            enemiesVec.push_back(car.get());
        }
    }
}

void Helper_createTree(
    const LevelInfo                    &levelInfo,
    std::vector<std::shared_ptr<Tree>> &treesVec,
    std::vector<Enemy *>               &enemiesVec)
{
    auto gm = Lore::GameManager::instance();
    for(int i = 0; i < levelInfo.treesInfo.size(); ++i)
    {
        const auto& treeInfo = levelInfo.treesInfo[i];

        //Decide Speed
        auto finalSpeed = gm->getRandomNumber(treeInfo.minSpeed,
                                              treeInfo.maxSpeed);

        //Build the trees with the pattern.
        for(int j = 0; j < treeInfo.pattern.size(); ++j)
        {
            //Empty slot...
            if(treeInfo.pattern[j] == 0)
                continue;

            auto tree = std::make_shared<Tree>(treeInfo.pattern[j]);

            tree->setSpeed(Lore::Vector2(finalSpeed, 0));
            tree->setPosition(
                Helper_TileToVec(kWaterTiles_Initial_X + j,
                                 kWaterTiles_Initial_Y + i)
            );

            tree->setMovementBounds(kWaterTiles_Initial_X * kTileSize,
                                    kWaterTilesCount_X    * kTileSize);

            treesVec.push_back  (tree);
            enemiesVec.push_back(tree.get());
        }
    }
}

void Helper_createTurtle(
    const LevelInfo                      &levelInfo,
    std::vector<std::shared_ptr<Turtle>> &turtlesVec,
    std::vector<Enemy *>                 &enemiesVec)
{
    auto gm = Lore::GameManager::instance();
    for(int i = 0; i < levelInfo.turtlesInfo.size(); ++i)
    {
        const auto& turtleInfo = levelInfo.turtlesInfo[i];

        //Decide Speed
        auto finalSpeed = gm->getRandomNumber(turtleInfo.minSpeed,
                                              turtleInfo.maxSpeed);

        //Build the turtles with the pattern.
        for(int j = 0; j < turtleInfo.pattern.size(); ++j)
        {
            //Empty slot...
            if(turtleInfo.pattern[j] == 0)
                continue;

            auto turtle = std::make_shared<Turtle>(turtleInfo.pattern[j]);

            turtle->setSpeed(Lore::Vector2(finalSpeed, 0));
            turtle->setPosition(
                Helper_TileToVec(kWaterTiles_Initial_X + j,
                                 kWaterTiles_Initial_Y + i)
            );

            turtle->setMovementBounds(kWaterTiles_Initial_X * kTileSize,
                                      kWaterTilesCount_X     * kTileSize);

            turtlesVec.push_back(turtle);
            enemiesVec.push_back(turtle.get());
        }
    }
}


NS_GAME_FROGGER_END
