//Header
#include "Turtle.h"

//Usings
USING_NS_GAME_FROGGER

////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr auto kTurtlesFramesCount = 4;
constexpr std::array<int, 6> kAnimationIndexes = {0, 1, 2, 3, 2, 1};
constexpr float kTimerFrameUpdate_Min = 1.0f;
constexpr float kTimerFrameUpdate_Max = 3.0f;

////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Turtle::Turtle(int type)
{
    //Init the Sprite.
    auto &sprite = getSprite();
    sprite.loadTexture(
        CoreGame::StringUtils::format("Images/turtle_%d_sprites.png", type)
    );

    auto spriteRect = sprite.getBounds();
    m_spriteSize.x  = spriteRect.getWidth() / kTurtlesFramesCount;
    m_spriteSize.y  = spriteRect.getHeight();


    //Init the Timer.
    //COWNOTE: Would be nice if lore had a randomReal too.
    //Random between 1.0 to 3.0 seconds.
    auto time = Lore::GameManager::instance()->getRandomNumber(
                    kTimerFrameUpdate_Min * 10,
                    kTimerFrameUpdate_Max * 10
                );
    m_updateFrameClock.setInterval(time / 10.0f);

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

    //Base
    Enemy::update(dt);
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


//Collision
bool Turtle::checkCollision(const Lore::Rectangle &testRect, float safeOffset)
{
    return isAboveWater() && Enemy::checkCollision(testRect, safeOffset);
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
