#ifndef __Game_Frogger_include_SceneMenu_h__
#define __Game_Frogger_include_SceneMenu_h__

//std
#include <vector>
//Game_Frogger
#include "GameFrogger_Utils.h"
#include "Player.h"


NS_GAME_FROGGER_BEGIN

class SceneMenu : public Lore::Scene
{
    // CTOR / DTOR //
public:
    SceneMenu();


    // Update / Draw //
public:
    virtual void update(float dt) override;
    virtual void draw() override;


    // Inits //
private:
    void initSprites();
    void initTexts  ();
    void initPlayer ();


    // Selection //
private:
    void changeSelectionIndex(int delta);


    // iVars //
private:
    //Sprites
    Lore::Sprite m_background;
    Lore::Sprite m_logo;

    //Texts
    Lore::Text m_1PlayerGameText;
    Lore::Text m_2PlayersGameText;
    Lore::Text m_creditsText;

    //Selection
    Player m_selectionFrog;
    int    m_selectionIndex;
};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_SceneMenu_h__ //
