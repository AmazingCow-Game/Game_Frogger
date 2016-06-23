//Header
#include "Enemy.h"

//Usings
USING_NS_GAME_FROGGER;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Enemy::Enemy() :
    m_minX(0),
    m_maxX(0),
    m_realPosition    (Lore::Vector2::Zero()),
    m_wrappingPosition(Lore::Vector2::Zero()),
    m_isWrapping(false)
{
    //Empty...
}

Enemy::~Enemy()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void Enemy::update(float dt)
{
    auto speed = getSpeed();
    auto width = getSprite().getBounds().getWidth();

    auto newPos =  m_realPosition + (speed * dt);

    auto moveMin = getMovementMinX();
    auto moveMax = getMovementMaxX();

    //Assume the we're not wrapping.
    setWrapping(false);

    //Moving to left...
    if(newPos.x < moveMin && speed.x < 0)
    {
        setWrapping(true);
        m_wrappingPosition = Lore::Vector2(
                                 moveMax - (-newPos.x),
                                 m_realPosition.y
                             );

        //Already moved too far - It should
        //be positioned into the "wrapping" position now.
        if(m_wrappingPosition.x + width < moveMax)
        {
            newPos = m_wrappingPosition;
            setWrapping(false);
        }
    }

    //Moving to right...
    else if(newPos.x + width > moveMax && speed.x > 0)
    {
        setWrapping(true);
        m_wrappingPosition = Lore::Vector2(
                                 newPos.x - moveMax,
                                 m_realPosition.y
                             );

        //Already moved too far - It should
        //be positioned into the "wrapping" position now.
        if(m_wrappingPosition.x > moveMin)
        {
            newPos = m_wrappingPosition;
            setWrapping(false);
        }
    }

    m_realPosition = newPos;
}

void Enemy::draw()
{
    //Draw the normal sprite.
    auto sprite = getSprite();
    sprite.setPosition(getRealPosition());
    sprite.setColor(Lore::Color::White());
    sprite.draw();

    if(!isWrapping())
        return;

    //Draw the wrapping sprite.
    sprite.setPosition(getWrappingPosition());
    sprite.setColor(Lore::Color(255, 0, 255));
    sprite.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
// Movement Bounds
void Enemy::setMovementBounds(int minX, int maxX)
{
    m_minX = minX;
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


//Position
void Enemy::setPosition(const Lore::Vector2 &pos)
{
    m_realPosition = pos;
}

const Lore::Vector2& Enemy::getPosition() const
{
    return m_realPosition;
}


//Bounding Box
Lore::Rectangle Enemy::getRealBoundingBox()
{
    return Lore::Rectangle(getRealPosition(),
                           getSprite().getBounds().getSize());
}

Lore::Rectangle Enemy::getWrappingBoundingBox()
{
    if(!isWrapping())
        return Lore::Rectangle::Empty();

    return Lore::Rectangle(getWrappingPosition(),
                           getSprite().getBounds().getSize());
}



//Collision
bool Enemy::checkCollision(const Lore::Rectangle &testRect,
                           float safeOffset)
{

    Lore::Rectangle outRect; //To check against the safe offset.

    //Check for normal collision.
    auto normalRect     = getRealBoundingBox();
    bool collidedNormal = (normalRect.intersectionRect(testRect, outRect))
                           && (outRect.getWidth() > safeOffset);


    //Check wrapping collision.
    if(isWrapping())
    {
        auto wrappingRect     = getWrappingBoundingBox();
        bool collidedWrapping = (wrappingRect.intersectionRect(testRect, outRect))
                                 && (outRect.getWidth() > safeOffset);

        return (collidedNormal || collidedWrapping);
    }

    return collidedNormal;
}


////////////////////////////////////////////////////////////////////////////////
// Protected Methods                                                          //
////////////////////////////////////////////////////////////////////////////////
void Enemy::setWrapping(bool wrapping)
{
    m_isWrapping = wrapping;
}

bool Enemy::isWrapping() const
{
    return m_isWrapping;
}


const Lore::Vector2 Enemy::getRealPosition() const
{
    return m_realPosition;
}

void Enemy::setRealPosition(const Lore::Vector2 &position)
{
    m_realPosition = position;
}


const Lore::Vector2 Enemy::getWrappingPosition() const
{
    return m_wrappingPosition;
}

void Enemy::setWrappingPosition(const Lore::Vector2 &position)
{
    m_wrappingPosition = position;
}
