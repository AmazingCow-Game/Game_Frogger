//Game_Frogger
#include "GameFrogger_Utils.h"
#include "SceneMenu.h"
#include "SceneGame.h"
#include "SceneSplash.h"
#include "Tile_Constants.h"


//Usings
USING_NS_GAME_FROGGER;

int main()
{
    auto windowMgr = Lore::WindowManager::instance();
    auto assetsMgr = Lore::AssetsManager::instance();
    auto inputMgr  = Lore::InputManager::instance ();
    auto soundMgr  = Lore::SoundManager::instance ();
    auto gameMgr   = Lore::GameManager::instance  ();

    // Init //
    //Window and Assets.
    windowMgr->initialize("Amazing Cow - Frogger - v1.0.0", //Caption
                           kTilesCount_X * kTileSize, 600,  //Design Resolution
                           kTilesCount_X * kTileSize, 600,  //Window Size
                           SDL_WINDOW_SHOWN,                //SDL Flags
                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    std::vector<std::string> paths = {
        "./assets",
        "/usr/local/share/amazingcow_game_frogger/assets"
    };
    assetsMgr->initialize(paths);

    //Sound and Input.
    soundMgr->initialize(Lore::SoundManager::kDefaultFrequency,
                         Lore::SoundManager::kDefaultFormat,
                         Lore::SoundManager::kDefaultChannels,
                         Lore::SoundManager::kDefaultChunkSize / 4);
    inputMgr->initialize();

    //Game.
    gameMgr->initialize(CoreRandom::Random::kRandomSeed, 60);


    // Run //
    gameMgr->run(Lore::make_unique<SceneSplash>());


    // Shutdown //
    windowMgr->shutdown();
    assetsMgr->shutdown();
    soundMgr->shutdown ();
    inputMgr->shutdown ();
    gameMgr->shutdown  ();


    return 0;
}
