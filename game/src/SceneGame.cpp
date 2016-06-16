//Header
#include "SceneGame.h"
//Game_Frooger
#include "GameConstants.h"
#include "SceneGame_Tile_Constants.h"
#include "SceneGame_HelperFunctions.h"
#include "SceneMenu.h"

//Usings
USING_NS_GAME_FROGGER


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kOneSecond = 1;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
SceneGame::SceneGame()
{
    //COWTODO: Put this in a better place.
    m_levelTime   = 360;
    m_playerLives = 3;


    initBackground();
    initStateText ();

    m_waterRect = Lore::Rectangle(
        Helper_TileToVec(kWaterTiles_Initial_X, kWaterTiles_Initial_Y),
        Helper_TileToVec(kWaterTilesCount_X,    kWaterTilesCount_Y)
    );

    reset();
}


////////////////////////////////////////////////////////////////////////////////
// Update                                                                     //
////////////////////////////////////////////////////////////////////////////////
void SceneGame::update(float dt)
{
    switch(m_state)
    {
        case SceneGame::State::Playing  : updatePlaying (dt); break;
        case SceneGame::State::Paused   : updatePaused  (dt); break;
        case SceneGame::State::Victory  : updateVictory (dt); break;
        case SceneGame::State::Defeat   : updateDefeat  (dt); break;
        case SceneGame::State::GameOver : updateGameOver(dt); break;
    }
}

void SceneGame::updatePlaying(float dt)
{
    auto inputMgr = Lore::InputManager::instance();

    //Pause...
    if(inputMgr->isKeyClick(SDL_SCANCODE_SPACE))
    {
        changeState(SceneGame::State::Paused);
        return;
    }

    //Movement...
    auto moveDirection = Player::Direction::None;

    if(inputMgr->isKeyClick(SDL_SCANCODE_LEFT))
        moveDirection = Player::Direction::Left;
    if(inputMgr->isKeyClick(SDL_SCANCODE_RIGHT))
        moveDirection = Player::Direction::Right;
    if(inputMgr->isKeyClick(SDL_SCANCODE_UP))
        moveDirection = Player::Direction::Up;
    if(inputMgr->isKeyClick(SDL_SCANCODE_DOWN))
        moveDirection = Player::Direction::Down;

    if(moveDirection != Player::Direction::None)
        m_player.move(moveDirection);


    //Timers
    m_countdownTimer.update(dt);

    //Enemies
    for(auto &enemy : m_enemiesVec)
        enemy->update(dt);

    //Player
    m_player.update(dt);

    //Collisions
    checkCarsCollisions        ();
    checkTreesCollisions       ();
    checkTurtlesCollisions     ();
    checkWaterCollision        ();
    checkBonusEnemiesCollisions();
}

void SceneGame::updatePaused(float dt)
{
    auto inputMgr = Lore::InputManager::instance();

    //Pause...
    if(inputMgr->isKeyClick(SDL_SCANCODE_SPACE))
    {
        changeState(SceneGame::State::Playing);
        return;
    }
}

void SceneGame::updateVictory(float dt)
{

}

void SceneGame::updateDefeat(float dt)
{
    //Player
    m_player.update(dt);

    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_SPACE) && m_playerDieAnimationIsDone)
    {
        resetSameLevel();
        return;
    }
}

void SceneGame::updateGameOver(float dt)
{
    //Player
    m_player.update(dt);

    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_SPACE) && m_playerDieAnimationIsDone)
    {
        auto gameMgr = Lore::GameManager::instance();
        gameMgr->changeScene(Lore::make_unique<SceneMenu>());

        return;
    }
}


////////////////////////////////////////////////////////////////////////////////
// Draw                                                                       //
////////////////////////////////////////////////////////////////////////////////
void SceneGame::draw()
{
    switch(m_state)
    {
        case SceneGame::State::Playing  : drawPlaying (); break;
        case SceneGame::State::Paused   : drawPaused  (); break;
        case SceneGame::State::Victory  : drawVictory (); break;
        case SceneGame::State::Defeat   : drawDefeat  (); break;
        case SceneGame::State::GameOver : drawGameOver(); break;
    }
}

void SceneGame::drawPlaying()
{
    //Background / Hud
    m_background.draw();
    m_hud.draw();

    // //COWTODO: DEBUG DRAW
    // SDL_Rect rect = Lore::SDLHelpers::make_rect(m_waterRect);
    // SDL_SetRenderDrawColor(Lore::WindowManager::instance()->getRenderer(),
    //                         255, 0, 255, 255);
    // SDL_RenderFillRect(Lore::WindowManager::instance()->getRenderer(), &rect);

    //Enemies
    for(auto &enemy : m_enemiesVec)
        enemy->draw();

    //Player
    m_player.draw();
}

void SceneGame::drawPaused()
{
    drawPlaying();
    m_stateText.draw();
}

void SceneGame::drawVictory()
{
    drawPlaying();
    m_stateText.draw();
}

void SceneGame::drawDefeat()
{
    drawPlaying();
    m_stateText.draw();
}

void SceneGame::drawGameOver()
{
    drawPlaying();
    m_stateText.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void SceneGame::reset()
{
    m_enemiesVec.clear();

    initCars        ();
    initTrees       ();
    initBonusEnemies();

    resetSameLevel();
}

void SceneGame::resetSameLevel()
{
    m_remainingTime = m_levelTime;
    changeState(SceneGame::State::Playing);

    initPlayer();
    initTimers();
    initHud   ();
}

void SceneGame::resetNextLevel()
{
    reset();
}


void SceneGame::killPlayer()
{
    --m_playerLives;

    m_player.kill();
    m_playerDieAnimationIsDone = false;

    if(m_playerLives > 0) changeState(SceneGame::State::Defeat);
    else                  changeState(SceneGame::State::GameOver);
}

void SceneGame::changeState(State newState)
{
    m_state = newState;
    m_stateText.setString(Helper_StateToStr(m_state));
}

////////////////////////////////////////////////////////////////////////////////
// Init                                                                       //
////////////////////////////////////////////////////////////////////////////////
void SceneGame::initBackground()
{
    m_background.loadTexture("background.png");
}

void SceneGame::initHud()
{
    //m_hud.updateScore        (m_score      );
    //m_hud.updateHighScore    (m_highScore  );
    m_hud.updateLives        (m_playerLives);
    m_hud.updateRemainingTime(m_remainingTime);
}

void SceneGame::initPlayer()
{
    m_player.setInitialPosition(
        Helper_TileToVec(kStartRowTilesCount_X / 2,
                         kStartRowTiles_Initial_Y)
    );

    m_player.setMovementBounds(
        //Min
        Helper_TileToVec(kTargetRowTiles_Initial_X,
                         kTargetRowTiles_Initial_Y),
        //Max
        Helper_TileToVec(kStartRowTilesCount_X,
                         kStartRowTiles_Initial_Y + kStartRowTilesCount_Y)
    );

    m_player.setDieAnimationCallback(
        COREGAME_CALLBACK_0(SceneGame::onPlayerDie, this)
    );


    m_player.reset();
}

void SceneGame::initTimers()
{
    auto tickCallback = COREGAME_CALLBACK_0(SceneGame::onCountdownTimerTick, this);
    auto doneCallback = COREGAME_CALLBACK_0(SceneGame::onCountdownTimerDone, this);

    m_countdownTimer.setInterval    (kOneSecond);
    m_countdownTimer.setRepeatCount (m_levelTime);
    m_countdownTimer.setTickCallback(tickCallback);
    m_countdownTimer.setDoneCallback(doneCallback);

    m_countdownTimer.start();
}

void SceneGame::initCars()
{
    m_carsVec.clear();

    //Lane 1
    createCarHelper(0, 4, 5,  -1);

    //Lane 2
    createCarHelper(1, 2, 0,  1);
    createCarHelper(1, 2, 10, 1);

    //Lane 3
    createCarHelper(2, 1, 5,  -1);

    //Lane 4
    createCarHelper(3, 4, 5,  1);

    //Lane 5
    createCarHelper(4, 3, 0,  -1);
    createCarHelper(4, 3, 10, -1);
}

void SceneGame::initTrees()
{
    m_treesVec.clear();

    createTreeHelper(0, 1, 2, -1);
    createTreeHelper(1, 1, 2, -1);
    createTreeHelper(2, 1, 2, -1);
    createTreeHelper(3, 1, 2, 1);
    createTreeHelper(4, 1, 2, -1);
}

void SceneGame::initBonusEnemies()
{
    m_bonusEnemiesVec.clear();

    for(int i = 0; i < kTilesCount_X ; i += 2)
    {
        auto enemy = std::make_shared<BonusEnemy>();
        enemy->setPosition(
              Helper_TileToVec(kTargetRowTiles_Initial_X + i,
                               kTargetRowTiles_Initial_Y)
        );

        m_bonusEnemiesVec.push_back(enemy);
        m_enemiesVec.push_back(enemy.get());
    }
}

void SceneGame::initStateText()
{
    m_stateText.loadFont(kFontName, kFontSize_StateText);
    m_stateText.setOrigin(Lore::ITransformable::OriginHelpers::Center());
    m_stateText.setPosition(
        Lore::WindowManager::instance()->getWindowRect().getCenter()
    );
}


void SceneGame::createCarHelper(int lane, int groupCount, int startX, int direction)
{
    for(int i = 0; i < groupCount; ++i)
    {
        auto car = std::make_shared<Car>();

        //COWTODO: Remove magic numbers...
        car->setSpeed(Lore::Vector2(40 * direction, 0));
        car->setPosition(
            Helper_TileToVec(kHighwayTiles_Initial_X + i + startX,
                             kHighwayTiles_Initial_Y + lane)
        );

        car->setMovementBounds(kHighwayTiles_Initial_X * kTileSize,
                              kHighwayTilesCount_X * kTileSize);

        m_carsVec.push_back(car);
        m_enemiesVec.push_back(car.get());
    }
}

void SceneGame::createTreeHelper(int lane, int groupCount, int startX, int direction)
{
    for(int i = 0; i < groupCount; ++i)
    {
        auto tree = std::make_shared<Tree>();

        //COWTODO: Remove magic numbers...
        tree->setSpeed(Lore::Vector2(40 * direction, 0));
        tree->setPosition(
            Helper_TileToVec(kWaterTiles_Initial_X + i + startX,
                             kWaterTiles_Initial_Y + lane)
        );

        tree->setMovementBounds(kWaterTiles_Initial_X * kTileSize,
                               kWaterTilesCount_X    * kTileSize);

        m_treesVec.push_back(tree);
        m_enemiesVec.push_back(tree.get());
    }
}

////////////////////////////////////////////////////////////////////////////////
// Collisions                                                                 //
////////////////////////////////////////////////////////////////////////////////
void SceneGame::checkCarsCollisions()
{
    if(!Helper_FrogIsOnHighwayRow(m_player))
        return;

    auto playerRect = m_player.getBoundingBox();
    for(auto &car : m_carsVec)
    {
        Lore::Rectangle outRect;
        if(car->getBoundingBox().intersectionRect(playerRect, outRect))
        {
            FROGGER_DLOG("Car INTERSECTION: %.2f %.2f %.2f %.2f",
                         outRect.getX(), outRect.getY(),
                         outRect.getWidth(), outRect.getHeight()
            );

            //COWTODO: Adjust the safe offset.
            if(outRect.getWidth() > 15)
            {
                killPlayer();
                return; //One collision per time
            }

            return; //One collision per time.
        }
    }//for(auto &car : m_carsVec)
}

void SceneGame::checkTreesCollisions()
{
    if(!Helper_FrogIsOnWaterRow(m_player))
    {
        m_player.setLateralMovementSpeed(0);
        return;
    }


    //Assumes that player isn't colliding with any of the trees.
    m_player.setIsSafe(false);
    m_player.setLateralMovementSpeed(0);

    auto playerRect = m_player.getBoundingBox();

    for(auto &tree : m_treesVec)
    {
        Lore::Rectangle outRect;
        if(tree->getBoundingBox().intersectionRect(playerRect, outRect))
        {
            FROGGER_DLOG("TREE INTERSECTION: %.2f %.2f %.2f %.2f",
                         outRect.getX(), outRect.getY(),
                         outRect.getWidth(), outRect.getHeight()
            );

            //COWTODO: Adjust the safe offset.
            if(outRect.getWidth() < 15)
                return;

            //Player is colliding - Make it move with the tree
            //and set that is is safe :D
            m_player.setLateralMovementSpeed(tree->getSpeed().x);
            m_player.setIsSafe(true);

            return;
        }
    }//for(auto &tree : m_treesVec)...
}

void SceneGame::checkTurtlesCollisions()
{
    //COWTODO: Implement...
}

void SceneGame::checkWaterCollision()
{
    if(Helper_FrogIsOnWaterRow(m_player) == false                 ||
       m_waterRect.intersects(m_player.getBoundingBox()) == false ||
       m_player.isSafe())
    {
        return;
    }

    killPlayer();
}

void SceneGame::checkBonusEnemiesCollisions()
{
    if(!Helper_FrogIsOnTargetRow(m_player))
        return;


    auto playerRect = m_player.getBoundingBox();

    for(auto &enemy : m_bonusEnemiesVec)
    {
        Lore::Rectangle outRect;

        //There is no intersection with this enemy...
        if(!enemy->getBoundingBox().intersectionRect(playerRect, outRect))
            continue;

        FROGGER_DLOG("BONUS ENEMY INTERSECTION: %.2f %.2f %.2f %.2f",
                     outRect.getX(), outRect.getY(),
                     outRect.getWidth(), outRect.getHeight()
        );

        //COWTODO: Adjust the safe offset.
        //There is an intersection, but check if the
        //most part of player is inside of the enemy...
        if(outRect.getWidth() >= 15)
        {
            m_player.reset();
            enemy->turnToFrog();
            return; //One collision per time.
        }
        //Nops, player is mostly outside...
        else
        {
            killPlayer();
            return; //One collision per time.
        }
    }//for(auto &enemy : m_bonusEnemiesVec) ...


    killPlayer();
}


////////////////////////////////////////////////////////////////////////////////
// Timer Callbacks                                                            //
////////////////////////////////////////////////////////////////////////////////
void SceneGame::onCountdownTimerTick()
{
    m_hud.updateRemainingTime(--m_remainingTime);

    FROGGER_DLOG("SceneGame::onCountdownTimerTick - RemainingTime %d",
                 m_remainingTime);
}

void SceneGame::onCountdownTimerDone()
{
    FROGGER_DLOG("SceneGame::onCountdownTimerDone");
    killPlayer();
}


////////////////////////////////////////////////////////////////////////////////
// Player Callbacks                                                           //
////////////////////////////////////////////////////////////////////////////////
void SceneGame::onPlayerDie()
{
    m_playerDieAnimationIsDone = true;
}
