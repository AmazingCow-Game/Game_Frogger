//Header
#include "Car.h"

//Usings
USING_NS_GAME_FROGGER

////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kCarsFramesCount = 4;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Car::Car()
{
    //Init the Sprite.
    auto &sprite = getSprite();
    sprite.loadTexture("car_sprites.png");

    auto spriteRect = sprite.getBounds();
    m_frameSize.x   = spriteRect.getWidth() / kCarsFramesCount;
    m_frameSize.y   = spriteRect.getHeight();

    randomizeFrame();
}

Car::~Car()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                             //
////////////////////////////////////////////////////////////////////////////////
void Car::update(float dt)
{
    auto newPos = getPosition() + (getSpeed() * dt);

    //Moving to left...
    if(newPos.x < getMovementMinX() && getSpeed().x < 0)
    {
        newPos.x = getMovementMaxX();
        randomizeFrame();
    }

    //Moving to right...
    if(newPos.x > getMovementMaxX() && getSpeed().x > 0)
    {
        newPos.x = getMovementMinX();
        randomizeFrame();
    }

    setPosition(newPos);
}


////////////////////////////////////////////////////////////////////////////////
// Interaction Properties                                                     //
////////////////////////////////////////////////////////////////////////////////
bool Car::isTouchabled() const
{
    return true;
}

bool Car::isFatal() const
{
    return true;
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void Car::setSpeed(const Lore::Vector2 &speed)
{
    Enemy::setSpeed(speed);
    getSprite().setFlipX(speed.x > 0);
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void Car::randomizeFrame()
{
    int index = Lore::GameManager::instance()->getRandomNumber(0, kCarsFramesCount -1);
    getSprite().setSourceRectangle(
        Lore::Rectangle(index * m_frameSize.x, 0,
                        m_frameSize.x, m_frameSize.y)
    );
}
