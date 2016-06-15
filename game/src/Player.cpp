//Header
#include "Player.h"

//Usings
USING_NS_GAME_FROGGER

////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kFramesCount_Alive = 8;
constexpr int kFramesCount_Dying = 3;
constexpr int kFramesCount       = kFramesCount_Alive + kFramesCount_Dying;

constexpr int kFrameIndex_InitialFrame = 0;

////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Player::Player()
{
    initSprite();
    initFrames();
    initTimers();

    setFrameRect(kFrameIndex_InitialFrame);
    setSpeed(Lore::Vector2(40, 40));
    setLateralMovementSpeed(0);
}

Player::~Player()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void Player::update(float dt)
{
    m_moveAnimationTimer.update (dt);
    m_dyingAnimationTimer.update(dt);


    auto targetPosition = getPosition() + (m_lateralSpeed * dt);

    if(canMove(targetPosition))
        setPosition(targetPosition);
}


////////////////////////////////////////////////////////////////////////////////
// Actions                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Player::move(Direction dir)
{
    //Is Dead/Dying or not moving to anywhere.
    if(getState() != GameObject::State::Alive ||
       dir == Player::Direction::None)
    {
        return;
    }


    auto targetPosition = getPosition();
    auto speed          = getSpeed   ();

    switch(dir)
    {
        case Direction::Left  : targetPosition.x -= speed.x; break;
        case Direction::Right : targetPosition.x += speed.x; break;
        case Direction::Up    : targetPosition.y -= speed.y; break;
        case Direction::Down  : targetPosition.y += speed.y; break;
    }

    m_currentDirection = dir;
    if(canMove(targetPosition))
       setPosition(targetPosition);

    setFrameRect(static_cast<int>(dir) + 1);
    m_moveAnimationTimer.start();
}

void Player::kill()
{
    //Already dying or dead...
    if(getState() != GameObject::State::Alive)
       return;

    setState(GameObject::State::Dying);

    m_moveAnimationTimer.stop  ();
    m_dyingAnimationTimer.start();

    onDyingAnimationTimerTick(); //Start change the frame imediatelly.
}

void Player::reset()
{
    setPosition (m_initialPosition       );
    setState    (GameObject::State::Alive);
    setFrameRect(kFrameIndex_InitialFrame);
}


////////////////////////////////////////////////////////////////////////////////
// Others                                                                     //
////////////////////////////////////////////////////////////////////////////////
void Player::setInitialPosition(const Lore::Vector2 &pos)
{
    m_initialPosition = pos;
}

void Player::setMovementBounds(const Lore::Vector2 &min,
                               const Lore::Vector2 &max)
{
    m_minBounds = min;
    m_maxBounds = max;
}

void Player::setDieAnimationCallback(const DieCallback &callback)
{
    m_dieAnimationCallback = callback;
}

Lore::Rectangle Player::getBoundingBox()
{
    return getSprite().getBounds();
}

void Player::setLateralMovementSpeed(float speed)
{
    m_lateralSpeed.x = speed;
}

bool Player::isSafe() const
{
    return m_isSafe;
}
void Player::setIsSafe(bool safe)
{
    m_isSafe = safe;
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
//Inits
void Player::initSprite()
{
    auto &sprite = getSprite();
    sprite.loadTexture("frog_sprites.png");
}

void Player::initFrames()
{
    auto spriteBounds = getSprite().getBounds ();
    auto frameWidth   = spriteBounds.getWidth () / kFramesCount;
    auto frameHeight  = spriteBounds.getHeight();

    //Init the Frames Rects.
    m_aliveFramesRect.reserve(kFramesCount_Alive);
    for(int i = 0; i < kFramesCount_Alive; ++i)
    {
        m_aliveFramesRect.push_back(
            Lore::Rectangle(i * frameWidth, 0, frameWidth, frameHeight)
        );
    }

    m_dyingFramesRect.reserve(kFramesCount_Dying);
    for(int i = kFramesCount_Alive;
        i < kFramesCount_Alive + kFramesCount_Dying;
        ++i)
    {
        m_dyingFramesRect.push_back(
            Lore::Rectangle(i * frameWidth, 0, frameWidth, frameHeight)
        );
    }
}

void Player::initTimers()
{
    //Move Animation
    m_moveAnimationTimer.setInterval   (0.1);
    m_moveAnimationTimer.setRepeatCount(1);

    auto moveTick = COREGAME_CALLBACK_0(Player::onMoveAnimationTimerTick, this);
    //COWTODO: Should we use the done callback to prevent player from moving \
    //         when the animation is going?
    m_moveAnimationTimer.setTickCallback(moveTick);

    //Dying Animation
    m_dyingAnimationTimer.setInterval   (0.5);
    m_dyingAnimationTimer.setRepeatCount(kFramesCount_Dying -1); //ZERO BASED.

    auto dyingTick = COREGAME_CALLBACK_0(Player::onDyingAnimationTimerTick, this);
    auto dyingDone = COREGAME_CALLBACK_0(Player::onDyingAnimationTimerDone, this);
    m_dyingAnimationTimer.setTickCallback(dyingTick);
    m_dyingAnimationTimer.setDoneCallback(dyingDone);
}


void Player::setFrameRect(int index)
{
    //Get the current state frames vec.
    auto &framesVec = (getState() == GameObject::State::Alive)
                       ? m_aliveFramesRect
                       : m_dyingFramesRect;

    COREGAME_ASSERT_ARGS(
        index >= 0 && index < framesVec.size(),
        "Player::setFrameRect - Trying to set a invalid frame (%d) - State: (%d)",
        index, getState()
    );

    getSprite().setSourceRectangle(framesVec[index]);
}

bool Player::canMove(const Lore::Vector2 &targetPos) const
{
    //Dying or Dead - Don't move...
    if(getState() != GameObject::State::Alive)
        return false;

    //FROGGER_DLOG(
    //    "Player::canMove: Pos (%.2f %.2f) - Min (%.2f %.2f) - Max (%.2f %.2f)",
    //    targetPos.x, targetPos.y,
    //    m_minBounds.x, m_minBounds.y,
    //    m_maxBounds.x, m_maxBounds.y
    //);

    return targetPos.y >= m_minBounds.y &&
           targetPos.x >= m_minBounds.x &&
           targetPos.y < m_maxBounds.y &&
           targetPos.x < m_maxBounds.x;
}



// Timer Callbacks //
void Player::onMoveAnimationTimerTick()
{
    setFrameRect(static_cast<int>(m_currentDirection));
}


void Player::onDyingAnimationTimerTick()
{
    auto index = m_dyingAnimationTimer.getTickCount();
    FROGGER_DLOG("Player::onDyingAnimationTimerTick - index: %d", index);
    setFrameRect(index);
}

void Player::onDyingAnimationTimerDone()
{
    FROGGER_DLOG("Player::onDyingAnimationTimerDone");

    setState(GameObject::State::Dead);
    m_dieAnimationCallback();
}
