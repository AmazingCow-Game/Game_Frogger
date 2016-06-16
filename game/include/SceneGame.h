#ifndef __Game_Frogger_include_SceneGame_h__
#define __Game_Frogger_include_SceneGame_h__

//std
#include <vector>
//Game_Frogger
#include "GameFrogger_Utils.h"
#include "BonusEnemy.h"
#include "Car.h"
#include "Tree.h"
#include "Hud.h"
#include "Player.h"


NS_GAME_FROGGER_BEGIN

class SceneGame : public Lore::Scene
{
    // Enums //
public:
    enum class State {
        Playing,
        Paused,
        Defeat,
        Victory,
        GameOver
    };


    // CTOR / DTOR //
public:
    SceneGame();


    // Update //
public:
    virtual void update(float dt) override;

private:
    void updatePlaying (float dt);
    void updatePaused  (float dt);
    void updateVictory (float dt);
    void updateDefeat  (float dt);
    void updateGameOver(float dt);


    // Draw //
public:
    virtual void draw() override;

private:
    void drawPlaying  ();
    void drawPaused   ();
    void drawVictory  ();
    void drawDefeat   ();
    void drawGameOver ();


    // Private Methods //
private:
    void reset();
    void resetSameLevel();
    void resetNextLevel();

    void killPlayer();

    void changeState(State newState);


    // Init //
private:
    void initBackground  ();
    void initHud         ();
    void initPlayer      ();
    void initTimers      ();
    void initCars        ();
    void initTrees       ();
    void initBonusEnemies();
    void initStateText   ();

    //COWTODO: Refactor....
    void createCarHelper(int lane, int groupCount, int startX, int direction);
    void createTreeHelper(int lane, int groupCount, int startX, int direction);


    // Collisions //
private:
    void checkCarsCollisions        ();
    void checkTreesCollisions       ();
    void checkTurtlesCollisions     ();
    void checkWaterCollision        ();
    void checkBonusEnemiesCollisions();


    // Timer Callbacks //
private:
    void onCountdownTimerTick();
    void onCountdownTimerDone();


    // Player Callbacks //
private:
    void onPlayerDie();


    // iVars //
private:
    //Game Objects
    Lore::Sprite m_background;
    Hud          m_hud;

    //Player
    Player m_player;
    bool   m_playerDieAnimationIsDone;

    //Enemies
    Lore::Rectangle                          m_waterRect;
    std::vector<std::shared_ptr<Car>>        m_carsVec;
    std::vector<std::shared_ptr<Tree>>       m_treesVec;
    std::vector<std::shared_ptr<BonusEnemy>> m_bonusEnemiesVec;
    std::vector<Enemy *>                     m_enemiesVec;

    //House Keeping
    State      m_state;
    int        m_playerLives;
    Lore::Text m_stateText;

    //Game Time
    CoreClock::Clock m_countdownTimer;
    int              m_remainingTime;
    int              m_levelTime;
};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_SceneGame_h__ //
