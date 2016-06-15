#ifndef __Game_Frogger_include_BonusEnemy_h__
#define __Game_Frogger_include_BonusEnemy_h__

//Game_Frogger
#include "GameFrogger_Utils.h"
#include "Enemy.h"

NS_GAME_FROGGER_BEGIN

class BonusEnemy : public Enemy
{
    // Enum //
public:
    enum class Type
    {
        Fly,
        Alligator,
        Frog,
        None
    };


    // CTOR / DTOR //
public:
    BonusEnemy();
    virtual ~BonusEnemy();


    // Update / Draw //
public:
    virtual void update(float dt) override;


    // Public Methods //
public:
    virtual bool isTouchabled() const override;
    virtual bool isFatal     () const override;

    void turnToFrog();
    Type getType() const;


    // Private Methods //
private:
    void setType(Type type);

    //Timers
    void resetAppearTimer();
    void resetStayTimer();

    //Callbacks
    void onAppearTimerTick();
    void onStayTimerTick();


    // iVars //
private:
    Type m_currentType;

    CoreClock::Clock m_appearTimer;
    CoreClock::Clock m_stayTimer;

    Lore::Vector2 m_spriteSize;
};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_BonusEnemy_h__ //
