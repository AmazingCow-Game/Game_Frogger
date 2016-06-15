
//Game_Frogger
#include "GameFrogger_Utils.h"
#include "SceneMenu.h"
#include "SceneGame.h"

//Usings
USING_NS_GAME_FROGGER;

int main(int argc, char* args[])
{

    auto windowMgr = Lore::WindowManager::instance();
    auto assetsMgr = Lore::AssetsManager::instance();
    auto inputMgr  = Lore::InputManager::instance ();
    auto soundMgr  = Lore::SoundManager::instance ();
    auto gameMgr   = Lore::GameManager::instance  ();

    // Init //
    //Window and Assets.
    windowMgr->initialize("Amazing Cow - Frogger - v0.1",   //Caption
                           520, 600,                        //Design Resolution
                           520, 600,                        //Window Size
                           SDL_WINDOW_SHOWN,                //SDL Flags
                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    assetsMgr->initialize("./assets");

    //Sound and Input.
    soundMgr->initialize("./assets/"); //Use the Lore Defaults.
    inputMgr->initialize();

    //Game.
    gameMgr->initialize(CoreRandom::Random::kRandomSeed, 60);


    // Run //
    gameMgr->run(Lore::make_unique<SceneGame>());


    // Shutdown //
    windowMgr->shutdown();
    assetsMgr->shutdown();
    soundMgr->shutdown ();
    inputMgr->shutdown ();
    gameMgr->shutdown  ();


    return 0;
}
