#ifndef __Game_Frogger_include_Car_h__
#define __Game_Frogger_include_Car_h__

//Game_Frogger
#include "GameFrogger_Utils.h"
#include "Enemy.h"

NS_GAME_FROGGER_BEGIN

class Car : public Enemy
{
    // CTOR / DTOR //
public:
    Car();
    virtual ~Car();

    // Public Methods //
public:
    void setSpeed(const Lore::Vector2 &speed);
};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_Car_h__ //
