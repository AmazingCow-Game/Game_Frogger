#ifndef __Game_Frogger_include_Enemy_h__
#define __Game_Frogger_include_Enemy_h__

//Game_Frogger
#include "GameFrogger_Utils.h"
#include "GameObject.h"

NS_GAME_FROGGER_BEGIN

class Enemy : public GameObject
{
    // CTOR / DTOR //
public:
    Enemy();
    virtual ~Enemy();


    // Public Methods //
public:
    void setMovementBounds(int minX, int maxX);
    int getMovementMinX() const;
    int getMovementMaxX() const;

    //Bounding Box
    virtual Lore::Rectangle getBoundingBox() override;


    // iVars //
private:
    int m_minX;
    int m_maxX;
};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_Enemy_h__ //
