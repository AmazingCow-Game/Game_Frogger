
#ifndef __Game_Frogger_include_GameFrogger_Utils_h__
#define __Game_Frogger_include_GameFrogger_Utils_h__

#define NS_GAME_FROGGER_BEGIN namespace GameFrogger {
#define NS_GAME_FROGGER_END   }
#define USING_NS_GAME_FROGGER using namespace GameFrogger;

//Lore
#include "Lore.h"

#define FROGGER_DLOG(_fmt_, ...) \
    COREGAME_DLOG(CoreGame::Log::Type::Debug1, _fmt_, ##__VA_ARGS__)

#endif // __Game_Frogger_include_GameFrogger_Utils_h__ //
