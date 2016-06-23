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


//Collision
bool Enemy::checkCollision(const Lore::Rectangle &testRect, float safeOffset)
{
    Lore::Rectangle outRect;
    bool collided = (getBoundingBox().intersectionRect(testRect, outRect))
                     && (outRect.getWidth() > safeOffset);

    //Just to add a breakpoint...
    COREGAME_ONLY_IN_DEBUG({
        if(collided)
        {
             FROGGER_DLOG(
                "Enemy collided offset %2.f - safe offset %.2f",
                outRect.getWidth(), safeOffset
            );
        }
    });

    return collided;
}

