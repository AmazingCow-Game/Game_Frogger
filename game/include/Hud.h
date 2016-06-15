#ifndef __Game_Frogger_include_Hud_h__
#define __Game_Frogger_include_Hud_h__

//Game_Frogger
#include "GameFrogger_Utils.h"

NS_GAME_FROGGER_BEGIN

class Hud : Lore::IDrawable
{
    // CTOR / DTOR //
public:
    Hud();
    ~Hud();


    // Draw //
public:
    virtual void draw() override;


    // Public Methods //
public:
    void updateScore        (int score);
    void updateHighScore    (int score);
    void updateRemainingTime(int time );
    void updateLives        (int lives);


    // Private Methods //
public:
    void initSprites  ();
    void initTexts    ();
    void initPositions();


    // iVars //
private:
    Lore::Text m_scoreText;
    Lore::Text m_scoreValueText;

    Lore::Text m_highScoreText;
    Lore::Text m_highScoreValueText;

    Lore::Text m_timeText;
    Lore::Text m_timeValueText;

    Lore::Text m_livesText;
    Lore::Text m_livesValueText;
};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_Hud_h__ //
