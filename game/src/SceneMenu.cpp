//Header
#include "SceneMenu.h"
//Game_Frooger
#include "GameConstants.h"
#include "SceneGame.h"

//Usings
USING_NS_GAME_FROGGER

//COWTODO: Remove the magic numbers.
//COWTODO: Add comments.

////////////////////////////////////////////////////////////////////////////////
// Load / Unload                                                              //
////////////////////////////////////////////////////////////////////////////////
void SceneMenu::load()
{

    Lore::WindowManager::instance()->setClearColor(Lore::Color(0, 0, 72));
    m_selectionIndex = 0;

    initSprites();
    initTexts  ();
    initPlayer ();
}

void SceneMenu::unload()
{

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
        gameMgr->changeScene(Lore::make_unique<SceneGame>());

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
    //m_background.draw();
    m_logo.draw      ();

    m_1PlayerGameText.draw ();
    m_2PlayersGameText.draw();
    m_creditsText.draw     ();

    m_selectionFrog.draw();
}

////////////////////////////////////////////////////////////////////////////////
// Inits                                                                      //
////////////////////////////////////////////////////////////////////////////////
void SceneMenu::initSprites()
{
    m_background.loadTexture("background.png");
    m_logo.loadTexture("frogger_title.png");

    auto winRect = Lore::WindowManager::instance()->getWindowRect();
    m_logo.setPosition(
        Lore::Vector2::OffsetBy(winRect.getCenter(), 0, -100)
    );
    m_logo.setOrigin(Lore::ITransformable::OriginHelpers::Center());
}

void SceneMenu::initTexts()
{
    //Load the fonts.
    m_1PlayerGameText.loadFont (kFontName, kFontSize_Menu);
    m_2PlayersGameText.loadFont(kFontName, kFontSize_Menu);
    m_creditsText.loadFont     (kFontName, kFontSize_Menu);

    //Set the strings.
    m_1PlayerGameText.setString ("1 - Player Game");
    m_2PlayersGameText.setString("2 - Players Game");
    m_creditsText.setString     ("Credits");

    //Set the positions.
    auto winRect = Lore::WindowManager::instance()->getWindowRect();

    m_1PlayerGameText.setPosition(
        Lore::Vector2::OffsetBy(winRect.getCenter(),
                                -(m_1PlayerGameText.getBounds().getWidth() / 2),
                                0)
    );
    m_1PlayerGameText.setOrigin(Lore::ITransformable::OriginHelpers::TopLeft());

    m_2PlayersGameText.setPosition(
        Lore::Vector2::OffsetBy(m_1PlayerGameText.getPosition(), 0, 40)
    );
    m_2PlayersGameText.setOrigin(Lore::ITransformable::OriginHelpers::TopLeft());

    m_creditsText.setPosition(
        Lore::Vector2::OffsetBy(m_2PlayersGameText.getPosition(), 0, 40)
    );
    m_creditsText.setOrigin(Lore::ITransformable::OriginHelpers::TopLeft());
}

void SceneMenu::initPlayer()
{
    auto textPos  = m_1PlayerGameText.getPosition();
    auto frogSize = m_selectionFrog.getSprite().getBounds().getWidth();
    auto finalPos = Lore::Vector2::OffsetBy(textPos, -frogSize - 10, -7);

    m_selectionFrog.setInitialPosition(finalPos);
    m_selectionFrog.reset();
}


////////////////////////////////////////////////////////////////////////////////
// Selection                                                                  //
////////////////////////////////////////////////////////////////////////////////
void SceneMenu::changeSelectionIndex(int delta)
{
    //Out of selection bounds.
    if(m_selectionIndex + delta < 0 ||
       m_selectionIndex + delta > 2)
    {
        return;
    }

    m_selectionIndex += delta;

    auto direction = (delta < 0) ? Player::Direction::Up
                                 : Player::Direction::Down;

    m_selectionFrog.move(direction);
}
