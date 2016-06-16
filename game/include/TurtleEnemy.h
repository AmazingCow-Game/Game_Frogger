#ifndef __Game_Frogger_include_TurtleEnemy_h__
#define __Game_Frogger_include_TurtleEnemy_h__

//Game_Frogger
#include "GameFrogger_Utils.h"
#include "Enemy.h"

NS_GAME_FROGGER_BEGIN

class TurtleEnemy : public Enemy
{
    // CTOR / DTOR //
public:
    TurtleEnemy();
    virtual ~TurtleEnemy();


    // Interaction Properties //
public:
    virtual bool isTouchabled() const override;
    virtual bool isFatal     () const override;
};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_TurtleEnemy_h__ //
