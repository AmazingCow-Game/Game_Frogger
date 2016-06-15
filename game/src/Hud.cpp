//Header
#include "Hud.h"
//Game_Frogger
#include "GameConstants.h"

//Usings
USING_NS_GAME_FROGGER

////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kTextOffset_Small = 10;
constexpr int kTextOffset_Big   = 15;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Hud::Hud()
{
    initSprites  ();
    initTexts    ();
    initPositions();
}

Hud::~Hud()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Draw                                                                       //
////////////////////////////////////////////////////////////////////////////////
void Hud::draw()
{
    m_scoreText.draw     ();
    m_scoreValueText.draw();

    m_highScoreText.draw     ();
    m_highScoreValueText.draw();

    m_livesText.draw     ();
    m_livesValueText.draw();

    m_timeText.draw     ();
    m_timeValueText.draw();
}


// Public Methods //
void Hud::updateScore(int score)
{
    m_scoreValueText.setString("%05d", score);
}

void Hud::updateHighScore(int score)
{
    m_highScoreValueText.setString("%05d", score);
}

void Hud::updateRemainingTime(int time)
{
    m_timeValueText.setString("%03d", time);
}

void Hud::updateLives(int lives)
{
    m_livesValueText.setString("%02d", lives);
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void Hud::initSprites()
{
    //COWTODO: Decide if will put the logo here.
}

void Hud::initTexts()
{
    //Score
    m_scoreText.loadFont     (kFontName, kFontSize_Hud_Small);
    m_scoreValueText.loadFont(kFontName, kFontSize_Hud_Big  );

    //HighScore
    m_highScoreText.loadFont     (kFontName, kFontSize_Hud_Small);
    m_highScoreValueText.loadFont(kFontName, kFontSize_Hud_Big  );

    //Time
    m_timeText.loadFont     (kFontName, kFontSize_Hud_Small);
    m_timeValueText.loadFont(kFontName, kFontSize_Hud_Big  );

    //Lives
    m_livesText.loadFont     (kFontName, kFontSize_Hud_Small);
    m_livesValueText.loadFont(kFontName, kFontSize_Hud_Big  );

    //Strings
    m_scoreText.setString    ("Score"   );
    m_highScoreText.setString("Hi-Score");
    m_timeText.setString     ("Time"    );
    m_livesText.setString    ("Lives"   );

    updateScore        (0);
    updateHighScore    (0);
    updateRemainingTime(0);
    updateLives        (0);
}

void Hud::initPositions()
{
    auto winRect  = Lore::WindowManager::instance()->getWindowRect();
    auto winWidth = winRect.getWidth();

    //Score
    m_scoreText.setPosition(kTextOffset_Small, kTextOffset_Small);
    m_scoreValueText.setPosition(
        Lore::Vector2::OffsetBy(m_scoreText.getPosition(),
                                0, kTextOffset_Small)
    );

    //High Score
    m_highScoreText.setPosition(
        Lore::Vector2::OffsetBy(m_scoreValueText.getPosition(),
                                0, kTextOffset_Big)
    );
    m_highScoreValueText.setPosition(
        Lore::Vector2::OffsetBy(m_highScoreText.getPosition(),
                                0, kTextOffset_Small)
    );


    //Lives
    m_livesText.setPosition(winWidth - kTextOffset_Small, kTextOffset_Small);
    m_livesText.setOrigin(Lore::ITransformable::OriginHelpers::TopRight());

    m_livesValueText.setPosition(
        Lore::Vector2::OffsetBy(m_livesText.getPosition(),
                                0, kTextOffset_Small)
    );
    m_livesValueText.setOrigin(m_livesText.getOrigin());


    //Time
    m_timeText.setPosition(
        Lore::Vector2::OffsetBy(m_livesValueText.getPosition(),
                                0, kTextOffset_Big)
    );
    m_timeText.setOrigin(m_livesValueText.getOrigin());

    m_timeValueText.setPosition(
        Lore::Vector2::OffsetBy(m_timeText.getPosition(),
                                0, kTextOffset_Small)
    );
    m_timeValueText.setOrigin(m_timeText.getOrigin());
}
