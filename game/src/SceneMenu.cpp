//Header
#include "SceneMenu.h"
//Game_Frooger
#include "GameConstants.h"
#include "SceneGame.h"
#include "SceneCredits.h"

//Usings
USING_NS_GAME_FROGGER

////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
#define kBackgroundColor Lore::Color(0, 0, 72) //Same as water
constexpr int kSelectionIndex_Play    = 0;
constexpr int kSelectionIndex_Credits = 1;

////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
SceneMenu::SceneMenu()
{
    Lore::WindowManager::instance()->setClearColor(kBackgroundColor);
    m_selectionIndex = kSelectionIndex_Play;

    initSprites();
    initTexts  ();
    initPlayer ();
    initSounds ();
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void SceneMenu::update(float dt)
{
    auto inputMgr = Lore::InputManager::instance();

    if(inputMgr->isKeyClick(SDL_SCANCODE_RETURN))
    {
        auto gameMgr = Lore::GameManager::instance();

        if(m_selectionIndex == kSelectionIndex_Play)
            gameMgr->changeScene(Lore::make_unique<SceneGame>());
        else
            gameMgr->changeScene(Lore::make_unique<SceneCredits>());

        return;
    }

    // Player want selects other thing?
    if(inputMgr->isKeyClick(SDL_SCANCODE_UP))
        changeSelectionIndex(-1);
    else if(inputMgr->isKeyClick(SDL_SCANCODE_DOWN))
        changeSelectionIndex(+1);


    //Update the frog in case the player make it jumps.
    m_selectionFrog.update(dt);
}

void SceneMenu::draw()
{
    //Logo
    m_logo.draw();

    //Texts
    m_playText.draw      ();
    m_creditsText.draw   ();
    m_amazingcowText.draw();

    //Frog
    m_selectionFrog.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Inits                                                                      //
////////////////////////////////////////////////////////////////////////////////
void SceneMenu::initSprites()
{
    m_logo.loadTexture("Images/frogger_title.png");

    auto winRect = Lore::WindowManager::instance()->getWindowRect();
    m_logo.setPosition(
        Lore::Vector2::OffsetBy(winRect.getCenter(), 0, -100)
    );
    m_logo.setOrigin(Lore::ITransformable::OriginHelpers::Center());
}

void SceneMenu::initTexts()
{
    //Load the fonts.
    m_playText.loadFont      (kFontName, kFontSize_Menu);
    m_creditsText.loadFont   (kFontName, kFontSize_Menu);
    m_amazingcowText.loadFont(kFontName, kFontSize_AmazingCowText);

    //Set the strings.
    m_playText.setString      ("Play");
    m_creditsText.setString   ("Credits");
    m_amazingcowText.setString("amazingcow - 2016");

    //Set the positions.
    auto winRect = Lore::WindowManager::instance()->getWindowRect();

    m_playText.setPosition(
        Lore::Vector2::OffsetBy(winRect.getCenter(),
                                -(m_playText.getBounds().getWidth() / 2),
                                0)
    );
    m_playText.setOrigin(Lore::ITransformable::OriginHelpers::TopLeft());


    m_creditsText.setPosition(
        Lore::Vector2::OffsetBy(m_playText.getPosition(), 0, 40)
    );
    m_creditsText.setOrigin(Lore::ITransformable::OriginHelpers::TopLeft());


    m_amazingcowText.setPosition(winRect.getCenter().x, winRect.getHeight() - 20);
    m_amazingcowText.setOrigin(Lore::ITransformable::OriginHelpers::BottomCenter());
}

void SceneMenu::initPlayer()
{
    auto textPos  = m_playText.getPosition();
    auto frogSize = m_selectionFrog.getSprite().getBounds().getWidth();
    auto finalPos = Lore::Vector2::OffsetBy(textPos, -frogSize - 10, -7);


    m_selectionFrog.setMovementBounds(
        Lore::Vector2::Zero(),
        Lore::Vector2(10000, 10000) //Arbitrary long values,
                                    //just to enable the frog to jump
    );

    m_selectionFrog.setInitialPosition(finalPos);
    m_selectionFrog.reset();
}

void SceneMenu::initSounds()
{
    Lore::SoundManager::instance()->loadEffect(kSoundName_Jump);
}


////////////////////////////////////////////////////////////////////////////////
// Selection                                                                  //
////////////////////////////////////////////////////////////////////////////////
void SceneMenu::changeSelectionIndex(int delta)
{
    //Out of selection bounds.
    if(m_selectionIndex + delta < 0 ||
       m_selectionIndex + delta > 1)
    {
        return;
    }

    //Update Selection
    m_selectionIndex += delta;

    //Move Frog
    auto direction = (delta < 0) ? Player::Direction::Up
                                 : Player::Direction::Down;

    m_selectionFrog.move(direction);

    //Play sound
    Lore::SoundManager::instance()->playEffect(kSoundName_Jump);
}
