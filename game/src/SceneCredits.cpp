//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        SceneCredits.cpp                          //
//            █ █        █ █        Game_Kaboom                               //
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
#include "SceneCredits.h"
//Game
#include "SceneMenu.h"
#include "GameConstants.h"


//Usings
USING_NS_GAME_FROGGER;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
SceneCredits::SceneCredits()
{
    Lore::WindowManager::instance()->setClearColor(Lore::Color::White());
    initStuff();
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void SceneCredits::update(float /* dt */)
{
    auto inputMgr = Lore::InputManager::instance();
    if(inputMgr->isKeyClick(SDL_SCANCODE_RETURN))
    {
        auto gameMgr = Lore::GameManager::instance();
        gameMgr->changeScene(Lore::make_unique<SceneMenu>());
    }
}

void SceneCredits::draw()
{
    m_logo.draw();

    for(auto &text : m_textsVec)
        text.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Inits                                                                      //
////////////////////////////////////////////////////////////////////////////////
void SceneCredits::initStuff()
{
    auto winRect   = Lore::WindowManager::instance()->getWindowRect();
    auto winCenter = winRect.getCenter();
    auto gm        = Lore::GameManager::instance();

    //Sprite
    m_logo.loadTexture("Images/AmazingCow_Logo_Small.png");
    m_logo.setPosition(winCenter.x, 20);
    m_logo.setOrigin(Lore::ITransformable::OriginHelpers::TopCenter());
    m_logo.setColor(
        Lore::Color(gm->getRandomNumber(0, 255),
                    gm->getRandomNumber(0, 255),
                    gm->getRandomNumber(0, 255))
    );


    //COWTODO: Fix the help message to AACD...
    //Message
    std::vector<std::string> msg {
        "This remake was made with <3 by Amazing Cow.",
        "We hope that you enjoy this little game (!)"
        "",
        "We have other projects at:",
        "www.amazingcow.com",
        "Take a look :)",
        "",
        "This game is entirely FREE SOFTWARE",
        "This means that you're welcome to",
        "SHARE and HACK IT (!!!)",
        "",
        "You can find the sources at:",
        "opensource.amazingcow.com",
        "",
        "Dev / Graphics / Sound by N2OMatt",
        "","",
        "THANKS FOR PLAYING..."
        "", "",
        "AACD do a WONDERFUL job helping people ",
        "with motor disability.",
        "Why you don't look and help their work? <3",
        "www.aacd.org.br"
    };

    float startOffset = 140;
    float lineOffset  =  20;

    for(int i = 0; i < (int)msg.size(); ++i)
    {
        m_textsVec.push_back(
            Lore::Text(kFontName_Credits, kFontSize_CreditsMsg)
        );

        auto &text = m_textsVec.back();

        text.setString(msg[i]);
        text.setPosition(winCenter.x, startOffset + (i * lineOffset));
        text.setOrigin(Lore::ITransformable::OriginHelpers::TopCenter());
        text.setForegroundColor(Lore::Color::Black());
    }
}
