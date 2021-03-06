//Header
#include "BonusEnemy.h"

//Usings
USING_NS_GAME_FROGGER


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
//Frames
constexpr int kFramesCount = 4;
//Appear
constexpr int kTimerAppearMin = 10;
constexpr int kTimerAppearMax = 15;
//Stay
constexpr int kTimerStayMin = 3;
constexpr int kTimerStayMax = 7;
//Timer
constexpr int kRepeatCount_OneTime = 1;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
BonusEnemy::BonusEnemy()
{
    //Sprite / Frames
    auto &sprite = getSprite();
    sprite.loadTexture("Images/bonus_sprites.png");

    auto spriteRect = getSprite().getBounds();
    m_spriteSize.x  = spriteRect.getWidth  () / kFramesCount;
    m_spriteSize.y  = spriteRect.getHeight ();


    //Timers
    auto appearTick = COREGAME_CALLBACK_0(BonusEnemy::onAppearTimerTick, this);
    auto stayTick   = COREGAME_CALLBACK_0(BonusEnemy::onStayTimerTick,   this);

    m_appearTimer.setTickCallback(appearTick);
    m_stayTimer.setTickCallback  (stayTick);

     m_appearTimer.setRepeatCount(kRepeatCount_OneTime);
     m_stayTimer.setRepeatCount  (kRepeatCount_OneTime);

    //Init type.
    setType(BonusEnemy::Type::None);

    resetAppearTimer();
}

BonusEnemy::~BonusEnemy()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void BonusEnemy::update(float dt)
{
   m_appearTimer.update(dt);
   m_stayTimer.update  (dt);
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                              //
////////////////////////////////////////////////////////////////////////////////
void BonusEnemy::turnToFrog()
{
    setType(BonusEnemy::Type::Frog);

    m_appearTimer.stop();
    m_stayTimer.stop  ();
}

BonusEnemy::Type BonusEnemy::getType() const
{
    return m_currentType;
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void BonusEnemy::setType(Type type)
{
    m_currentType = type;

    //Set the frame.
    auto typeIndex = static_cast<int>(type);

    getSprite().setSourceRectangle(
        Lore::Rectangle(typeIndex * m_spriteSize.x, 0,
                        m_spriteSize.x, m_spriteSize.y)
    );
}

//Timers
void BonusEnemy::resetAppearTimer()
{
    auto time = Lore::GameManager::instance()->getRandomNumber(kTimerAppearMin,
                                                               kTimerAppearMax);
    m_appearTimer.setInterval(time);
    m_appearTimer.start();
}

void BonusEnemy::resetStayTimer()
{
    auto time = Lore::GameManager::instance()->getRandomNumber(kTimerStayMin,
                                                               kTimerStayMax);
    m_stayTimer.setInterval(time);
    m_stayTimer.start();
}

//Callbacks
void BonusEnemy::onAppearTimerTick()
{
    // 0 - Alligator
    // 1 - Fly
    // 2 - None;
    int number = Lore::GameManager::instance()->getRandomNumber(0, 2);

    auto type = (number == 0) ? BonusEnemy::Type::Alligator :
                (number == 1) ? BonusEnemy::Type::Fly
                              : BonusEnemy::Type::None;
    setType(type);

    m_appearTimer.stop();
    resetStayTimer();

    FROGGER_DLOG("BonusEnemy::onAppearTimerTick - SELECTED [0,2]: %d", number);
}

void BonusEnemy::onStayTimerTick()
{
    FROGGER_DLOG("BonusEnemy::onStayTimerTick");

    setType(BonusEnemy::Type::None);

    m_stayTimer.stop();
    resetAppearTimer();
}

