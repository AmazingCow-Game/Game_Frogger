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
    sprite.loadTexture("Images/car_sprites.png");

    auto spriteRect = sprite.getBounds    ();
    auto width      = spriteRect.getWidth () / kCarsFramesCount;
    auto height     = spriteRect.getHeight();

    int index = Lore::GameManager::instance()->getRandomNumber(0, kCarsFramesCount -1);
    getSprite().setSourceRectangle(
        Lore::Rectangle(index * width, 0,
                        width, height)
    );
}

Car::~Car()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void Car::setSpeed(const Lore::Vector2 &speed)
{
    Enemy::setSpeed(speed);
    getSprite().setFlipX(speed.x > 0);
}
