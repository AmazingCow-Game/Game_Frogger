#ifndef __Game_Frogger_include_Player_h__
#define __Game_Frogger_include_Player_h__

//std
#include <functional>
//Game_Frogger
#include "GameFrogger_Utils.h"
#include "GameObject.h"

NS_GAME_FROGGER_BEGIN

class Player : public GameObject
{
    // Enums / Typedefs / Constants //
public:
    enum class Direction {
        Up    = 0,
        Right = 2,
        Down  = 4,
        Left  = 6,
        None  = -1
    };

    typedef std::function<void ()> DieCallback;


    // CTOR / DTOR //
public:
    Player();
    virtual ~Player();


    // Update / Draw //
public:
    virtual void update(float dt) override;


    // Actions //
public:
    virtual void move(Direction dir);
    virtual void kill();
    void reset();


    // Others //
public:
    void setInitialPosition(const Lore::Vector2 &pos);
    void setMovementBounds(const Lore::Vector2 &min,
                           const Lore::Vector2 &max);

    void setDieAnimationCallback(const DieCallback &callback);

    virtual Lore::Rectangle getBoundingBox() override;

    void setLateralMovementSpeed(float speed);


    bool isSafe() const;
    void setIsSafe(bool safe);

    bool isMoveAnimationDone() const;


    // Private Methods //
private:
    //Inits
    void initSprite();
    void initFrames();
    void initTimers();

    void setFrameRect(int index);
    bool canMove(const Lore::Vector2 &targetPos) const;

    //Timer Callbacks
    void onMoveAnimationTimerTick ();
    void onDyingAnimationTimerTick();
    void onDyingAnimationTimerDone();


    // iVars //
private:
    //Frames / Animation
    std::vector<Lore::Rectangle> m_aliveFramesRect;
    std::vector<Lore::Rectangle> m_dyingFramesRect;

    CoreClock::Clock m_moveAnimationTimer;
    CoreClock::Clock m_dyingAnimationTimer;

    bool m_isMoveAnimationDone;

    //Movement
    Lore::Vector2 m_initialPosition;
    Lore::Vector2 m_minBounds;
    Lore::Vector2 m_maxBounds;
    Direction     m_currentDirection;
    Lore::Vector2 m_lateralSpeed;

    //Safe
    bool m_isSafe;

    //Callbacks
    DieCallback m_dieAnimationCallback;
};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_Player_h__ //
