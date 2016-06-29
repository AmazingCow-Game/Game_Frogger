//Header
#include "SceneGame.h"
//Game_Frooger
#include "GameConstants.h"
#include "Tile_Constants.h"
#include "SceneMenu.h"
#include "SceneGame_HelperFunctions.h"

//Usings
USING_NS_GAME_FROGGER


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kOneSecond = 1;

constexpr int kScore_Step    =   100;
constexpr int kScore_Time    =    50;
constexpr int kScore_Row     =  2500;
constexpr int kScore_Bonus   =  5000;
constexpr int kScore_Victory = 10000;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
SceneGame::SceneGame()
{
    //COWTODO: Put this in a better place.
    m_playerLives = 3;
    m_score       = 0;
    m_highScore   = 0;

    initBackground();
    initStateText ();
    initSounds    ();

    m_waterRect = Lore::Rectangle(
        Helper_TileToVec(kWaterTiles_Initial_X, kWaterTiles_Initial_Y),
        Helper_TileToVec(kWaterTilesCount_X,    kWaterTilesCount_Y)
    );

    reset(1);

    soundPlay_Intro();
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
        // changeState(SceneGame::State::Paused);
        reset(1);
        return;
    }

    m_soundToPlay = "";

    //Movement...
    if(m_player.isMoveAnimationDone())
    {
        auto moveDirection = Player::Direction::None;

        if(inputMgr->isKeyClick(SDL_SCANCODE_LEFT))
        {
            moveDirection = Player::Direction::Left;
        }
        else if(inputMgr->isKeyClick(SDL_SCANCODE_RIGHT))
        {
            moveDirection = Player::Direction::Right;
        }
        else if(inputMgr->isKeyClick(SDL_SCANCODE_UP))
        {
            moveDirection = Player::Direction::Up;
            updateScoreStep(false);
        }
        else if(inputMgr->isKeyClick(SDL_SCANCODE_DOWN))
        {
            moveDirection = Player::Direction::Down;
            updateScoreStep(true);
        }

        if(moveDirection != Player::Direction::None)
        {
            m_player.move(moveDirection);
            m_soundToPlay = kSoundName_Jump;
        }
    }

    //Timers
    m_countdownTimer.update(dt);

    //Enemies
    for(auto &enemy : m_enemiesVec)
        enemy->update(dt);

    m_player.setIsSafe(false);
    m_player.setLateralMovementSpeed(0);

    //Collisions
    checkCarsCollisions        ();
    checkTreesCollisions       ();
    checkTurtlesCollisions     ();
    checkWaterCollision        ();
    checkBonusEnemiesCollisions();

    //Player
    m_player.update(dt);

    if(!m_soundToPlay.empty())
        Lore::SoundManager::instance()->playEffect(m_soundToPlay);
}

void SceneGame::updatePaused(float /* dt */)
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
     //Player
    m_player.update(dt);

    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_SPACE) && m_player.isMoveAnimationDone())
    {
        resetNextLevel();
        return;
    }
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
//Reset
void SceneGame::reset(int level)
{
    m_enemiesVec.clear();
    m_levelInfo = LevelInfo_GetInfoForLevel(level);

    initCars        ();
    initTrees       ();
    initTurtles     ();
    initBonusEnemies();

    resetSameLevel();
}

void SceneGame::resetSameLevel()
{
    //COWTODO: Remove magic numbers.
    m_remainingTime = m_levelInfo.time;
    changeState(SceneGame::State::Playing);

    initPlayer();
    initTimers();
    initHud   ();
}

void SceneGame::resetNextLevel()
{
    reset(m_levelInfo.level + 1);
}


//Player
void SceneGame::killPlayer()
{
    --m_playerLives;

    m_player.kill();
    m_playerDieAnimationIsDone = false;

    if(m_playerLives > 0) changeState(SceneGame::State::Defeat);
    else                  changeState(SceneGame::State::GameOver);
}


//State
void SceneGame::changeState(State newState)
{
    m_state = newState;
    m_stateText.setString(Helper_StateToStr(m_state));
}

void SceneGame::checkVictory()
{
    for(auto &enemy : m_bonusEnemiesVec)
    {
        if(enemy->getType() != BonusEnemy::Type::Frog)
            return;
    }

    updateScoreTime   ();
    updateScoreVictory();

    changeState(SceneGame::State::Victory);
    m_soundToPlay = kSoundName_Victory;
}



//Score
void SceneGame::updateScoreStep(bool backwards)
{
    auto value = (backwards) ? -kScore_Step : kScore_Step;
    updateScore(value);
}

void SceneGame::updateScoreTime()
{
    updateScore(m_remainingTime * kScore_Time);
}

void SceneGame::updateScoreRow()
{
    updateScore(kScore_Row);
}

void SceneGame::updateScoreBonus()
{
    updateScore(kScore_Bonus);
}

void SceneGame::updateScoreVictory()
{
    updateScore(kScore_Victory);
}

void SceneGame::updateScore(int delta)
{
    m_score += delta;
    if(m_score > m_highScore)
    {
        m_highScore = m_score;
        //COWTODO: Save...

        m_hud.updateHighScore(m_highScore);
    }

    m_hud.updateScore(m_score);
}


////////////////////////////////////////////////////////////////////////////////
// Init                                                                       //
////////////////////////////////////////////////////////////////////////////////
void SceneGame::initBackground()
{
    m_background.loadTexture("Images/background.png");
}

void SceneGame::initHud()
{
    m_hud.updateScore        (m_score        );
    m_hud.updateHighScore    (m_highScore    );
    m_hud.updateLives        (m_playerLives  );
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
    m_countdownTimer.setRepeatCount (m_levelInfo.time);
    m_countdownTimer.setTickCallback(tickCallback);
    m_countdownTimer.setDoneCallback(doneCallback);

    m_countdownTimer.start();
}

void SceneGame::initCars()
{
    m_carsVec.clear();
    Helper_createCar(m_levelInfo, m_carsVec, m_enemiesVec);
}

void SceneGame::initTrees()
{
    m_treesVec.clear();
    Helper_createTree(m_levelInfo, m_treesVec, m_enemiesVec);
}

void SceneGame::initTurtles()
{
    m_turtlesVec.clear();
    Helper_createTurtle(m_levelInfo, m_turtlesVec, m_enemiesVec);
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

void SceneGame::initSounds()
{
    auto soundMgr = Lore::SoundManager::instance();
    soundMgr->loadEffect(kSoundName_MusicIntro  );
    soundMgr->loadEffect(kSoundName_Jump        );
    soundMgr->loadEffect(kSoundName_Victory     );
    soundMgr->loadEffect(kSoundName_ReachTarget );
    soundMgr->loadEffect(kSoundName_DefeatWater );
    soundMgr->loadEffect(kSoundName_DefeatNormal);
    soundMgr->loadEffect(kSoundName_TimeUp      );
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
        if(!car->checkCollision(playerRect, 15))
            continue;

        killPlayer();
        m_soundToPlay = kSoundName_DefeatNormal;

        return; //One collision per time
    }//for(auto &car : m_carsVec)
}

void SceneGame::checkTreesCollisions()
{
    if(!Helper_FrogIsOnWaterRow(m_player))
        return;

    auto playerRect = m_player.getBoundingBox();

    for(auto &tree : m_treesVec)
    {
        if(!tree->checkCollision(playerRect, 15))
            continue;

        //Player is colliding - Make it move with the tree
        //and set that is is safe :D
        m_player.setLateralMovementSpeed(tree->getSpeed().x);
        m_player.setIsSafe(true);

        return;
    }//for(auto &tree : m_treesVec)...
}

void SceneGame::checkTurtlesCollisions()
{
    if(!Helper_FrogIsOnWaterRow(m_player))
        return;

    auto playerRect = m_player.getBoundingBox();

    for(auto &turtle : m_turtlesVec)
    {
        if(!turtle->checkCollision(playerRect, 15))
            continue;

        //Player is colliding - Make it move with the turtle
        //and set that is is safe :D
        m_player.setLateralMovementSpeed(turtle->getSpeed().x);
        m_player.setIsSafe(true);

        return;
    }//for(auto &turtle : m_turtleVec)...
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
    m_soundToPlay = kSoundName_DefeatWater;
}

void SceneGame::checkBonusEnemiesCollisions()
{
    if(!Helper_FrogIsOnTargetRow(m_player))
        return;

    auto playerRect = m_player.getBoundingBox();

    for(auto &enemy : m_bonusEnemiesVec)
    {
        //COWTODO: Remove magic numbers...
        if(enemy->checkCollision(playerRect, 15))
        {
            //Collided with a Gator - Should die...
            if(enemy->getType() == BonusEnemy::Type::Alligator)
                break;

            if(enemy->getType() == BonusEnemy::Type::Fly)
                updateScoreBonus();
            else
                updateScoreRow();

            m_player.reset();
            enemy->turnToFrog();

            m_soundToPlay = kSoundName_ReachTarget;
            checkVictory();

            return; //One collision per time.
        }
    }//for(auto &enemy : m_bonusEnemiesVec) ...


    m_soundToPlay = kSoundName_DefeatNormal;
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

    //COWTODO: Remove magic number.
    if(m_remainingTime == 20)
        soundPlay_TimeUp();
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


////////////////////////////////////////////////////////////////////////////////
// Sound Output                                                               //
////////////////////////////////////////////////////////////////////////////////
void SceneGame::soundPlay_Intro()
{
    auto soundMgr = Lore::SoundManager::instance();
    soundMgr->playEffect(kSoundName_MusicIntro);
}

void SceneGame::soundPlay_TimeUp()
{
    auto soundMgr = Lore::SoundManager::instance();
    soundMgr->playEffect(kSoundName_TimeUp);
}

