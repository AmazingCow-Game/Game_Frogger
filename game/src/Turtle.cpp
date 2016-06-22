//Header
#include "Turtle.h"

//Usings
USING_NS_GAME_FROGGER

////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr auto kTurtlesSpriteNamesArr = {"turtle_2_sprites.png",
                                         "turtle_3_sprites.png"};
constexpr auto kTurtlesFramesCount = 4;
constexpr std::array<int, 6> kAnimationIndexes = {0, 1, 2, 3, 2, 1};


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Turtle::Turtle()
{
    auto spriteName  = *(std::begin(kTurtlesSpriteNamesArr) + 1);

    //Init the Sprite.
    auto &sprite = getSprite();
    sprite.loadTexture(spriteName);

    auto spriteRect = sprite.getBounds();
    m_spriteSize.x  = spriteRect.getWidth() / kTurtlesFramesCount;
    m_spriteSize.y  = spriteRect.getHeight();


    //Init the Timer.
    m_updateFrameClock.setInterval(1.5);
    m_updateFrameClock.setRepeatCount(CoreClock::Clock::kRepeatForever);
    m_updateFrameClock.setTickCallback(
        COREGAME_CALLBACK_0(Turtle::onUpdateFrameClockTick, this)
    );
    m_updateFrameClock.start();


    //Frames
    m_currAnimationIndex     = 0;
    updateFrame(); //Force the correct frame.
}

Turtle::~Turtle()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                             //
////////////////////////////////////////////////////////////////////////////////
void Turtle::update(float dt)
{
    //Timer
    m_updateFrameClock.update(dt);

    //Movement
    auto newPos = getPosition() + (getSpeed() * dt);

    //Moving to left...
    if(newPos.x < getMovementMinX() && getSpeed().x < 0)
        newPos.x = getMovementMaxX();

    //Moving to right...
    if(newPos.x > getMovementMaxX() && getSpeed().x > 0)
        newPos.x = getMovementMinX();

    setPosition(newPos);
}



////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void Turtle::setSpeed(const Lore::Vector2 &speed)
{
    Enemy::setSpeed(speed);
    getSprite().setFlipX(speed.x > 0);
}

bool Turtle::isAboveWater() const
{
    return kAnimationIndexes[m_currAnimationIndex] != (kTurtlesFramesCount -1);
}

////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void Turtle::updateFrame()
{
    getSprite().setSourceRectangle(
        Lore::Rectangle(kAnimationIndexes[m_currAnimationIndex] * m_spriteSize.x,
                        0,
                        m_spriteSize.x,
                        m_spriteSize.y)
    );
}

void Turtle::onUpdateFrameClockTick()
{
    m_currAnimationIndex = (m_currAnimationIndex + 1) % kAnimationIndexes.size();
    updateFrame();
}
