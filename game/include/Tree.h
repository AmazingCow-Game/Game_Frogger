#ifndef __Game_Frogger_include_Tree_h__
#define __Game_Frogger_include_Tree_h__

//Game_Frogger
#include "GameFrogger_Utils.h"
#include "Enemy.h"

NS_GAME_FROGGER_BEGIN

class Tree : public Enemy
{
    // CTOR / DTOR //
public:
    Tree(int type);
    virtual ~Tree();


    // Update / Draw //
public:
    virtual void update(float dt) override;


    // Public Methods //
public:
    virtual void setSpeed(const Lore::Vector2 &speed) override;

};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_Tree_h__ //
