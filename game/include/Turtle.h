#ifndef __Game_Frogger_include_Turtle_h__
#define __Game_Frogger_include_Turtle_h__

//Game_Frogger
#include "GameFrogger_Utils.h"
#include "Enemy.h"

NS_GAME_FROGGER_BEGIN

class Turtle : public Enemy
{
    // CTOR / DTOR //
public:
    Turtle(int type);
    virtual ~Turtle();


    // Update / Draw //
public:
    virtual void update(float dt) override;


    // Public Methods //
public:
    virtual void setSpeed(const Lore::Vector2 &speed) override;

    bool isAboveWater() const;

    //Collision
    virtual bool checkCollision(const Lore::Rectangle &testRect,
                                float safeOffset);


    // Private Methods //
private:
    void updateFrame();
    void onUpdateFrameClockTick();


    // iVars //
private:
    CoreClock::Clock m_updateFrameClock;
    Lore::Vector2    m_spriteSize;
    int              m_currAnimationIndex;
};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_Turtle_h__ //
