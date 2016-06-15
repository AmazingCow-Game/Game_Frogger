//Header
#include "Enemy.h"

//Usings
USING_NS_GAME_FROGGER;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Enemy::Enemy()
{
    //Empty...
}

Enemy::~Enemy()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Interaction Properties                                                     //
////////////////////////////////////////////////////////////////////////////////
bool Enemy::isTouchabled() const
{
    return true;
}

bool Enemy::isFatal() const
{
    return false;
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void Enemy::setMovementBounds(int minX, int maxX)
{
    auto width = getSprite().getBounds().getWidth();

    m_minX = minX - width;
    m_maxX = maxX;
}

int Enemy::getMovementMinX() const
{
    return m_minX;
}

int Enemy::getMovementMaxX() const
{
    return m_maxX;
}

//Bounding Box
Lore::Rectangle Enemy::getBoundingBox()
{
    return getSprite().getBounds();
}
