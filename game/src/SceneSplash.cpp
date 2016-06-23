//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        SceneSplash.cpp                           //
//            █ █        █ █        Game_Frogger                              //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016                        //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

//Header
#include "SceneSplash.h"
//Game_Frogger
#include "GameConstants.h"
#include "SceneGame.h"
#include "SceneMenu.h"

//Usings
USING_NS_GAME_FROGGER


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
SceneSplash::SceneSplash()
{
    Lore::WindowManager::instance()->setClearColor(Lore::Color::White());

    initSprites();
    initTimers ();
    initSounds ();
}

////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void SceneSplash::update(float dt)
{
    //Update the timers.
    m_timer.update(dt);

    if(!m_updateColors)
        return;

    constexpr int step = 5;
    auto currColor = m_sprite.getColor();

    // Red
    if     (currColor.r > m_targetColor.r) currColor.r -= step;
    else if(currColor.r < m_targetColor.r) currColor.r += step;
    // Blue
    if     (currColor.g > m_targetColor.g) currColor.g -= step;
    else if(currColor.g < m_targetColor.g) currColor.g += step;
    //Green
    if     (currColor.b > m_targetColor.b) currColor.b -= step;
    else if(currColor.b < m_targetColor.b) currColor.b += step;

    m_sprite.setColor(currColor);
}

void SceneSplash::draw()
{
    if(!m_updateColors)
        return;

    m_sprite.draw();
    m_text.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Inits                                                                      //
////////////////////////////////////////////////////////////////////////////////
void SceneSplash::initSprites()
{
    auto gm = Lore::GameManager::instance();
    auto winCenter = Lore::WindowManager::instance()->getWindowRect().getCenter();

    //Color
    m_targetColor = Lore::Color(
                        gm->getRandomNumber(0, 255),
                        gm->getRandomNumber(0, 255),
                        gm->getRandomNumber(0, 255)
                    );

    //Sprite
    m_sprite.loadTexture("Images/AmazingCow_Logo_Big.png");
    m_sprite.setOrigin(Lore::ITransformable::OriginHelpers::TopCenter());
    m_sprite.setPosition(
        Lore::Vector2::OffsetBy(winCenter, 0, -m_sprite.getBounds().getHeight())
    );

    //Text
    m_text.loadFont(kFontName, kFontSize_AmazingCowLogoText);
    m_text.setString("amazingcow");
    m_text.setOrigin(Lore::ITransformable::OriginHelpers::TopCenter());
    m_text.setPosition(
        winCenter.x,
        m_sprite.getBounds().getBottom() + 20
    );
    m_text.setForegroundColor(Lore::Color::Black());


    //Others
    m_updateColors = false;
}

void SceneSplash::initTimers()
{
    m_timer.setInterval(0.4f);
    m_timer.setRepeatCount(5);

    m_timer.setTickCallback([this](){
        if(!m_updateColors)
        {
            auto soundMgr = Lore::SoundManager::instance();
            soundMgr->playEffect(kSoundName_AmazingIntro);
            m_updateColors = true;
        }
    });

    m_timer.setDoneCallback([this]() {
        auto gm = Lore::GameManager::instance();
        gm->changeScene(Lore::make_unique<SceneMenu>());
    });

    m_timer.start();
}

void SceneSplash::initSounds()
{
    auto soundMgr = Lore::SoundManager::instance();
    soundMgr->loadEffect(kSoundName_AmazingIntro);
}
