#ifndef __Game_Frogger_include_GameConstants_h__
#define __Game_Frogger_include_GameConstants_h__

//Game_Frogger
#include "GameFrogger_Utils.h"


NS_GAME_FROGGER_BEGIN

////////////////////////////////////////////////////////////////////////////////
// Fonts                                                                      //
////////////////////////////////////////////////////////////////////////////////
constexpr auto kFontName         = "Fonts/nokiafc22.ttf";
constexpr auto kFontName_Credits = "Fonts/SourceCodePro-Regular.ttf";

//Splash
constexpr int kFontSize_AmazingCowLogoText = 30;
//Menu
constexpr int kFontSize_Menu            = 22;
constexpr int kFontSize_AmazingCowText  = 20;
//Hud
constexpr int kFontSize_Hud_Big   = 12;
constexpr int kFontSize_Hud_Small =  8;
//Game
constexpr int kFontSize_StateText = 40;
//Credits
constexpr int kFontSize_CreditsMsg = 18;

////////////////////////////////////////////////////////////////////////////////
// Sounds                                                                     //
////////////////////////////////////////////////////////////////////////////////
constexpr auto kSoundName_AmazingIntro = "Sounds/amazing_intro.wav";
constexpr auto kSoundName_MusicIntro   = "Sounds/Music.wav";
constexpr auto kSoundName_Jump         = "Sounds/Jump.wav";
constexpr auto kSoundName_Victory      = "Sounds/Completion.wav";
constexpr auto kSoundName_ReachTarget  = "Sounds/ReachTarget.wav";
constexpr auto kSoundName_DefeatWater  = "Sounds/Dead_Water.wav";
constexpr auto kSoundName_DefeatNormal = "Sounds/Dead_Normal.wav";
constexpr auto kSoundName_TimeUp       = "Sounds/TimeUp.wav";

NS_GAME_FROGGER_END
#endif // defined(__Game_Frogger_include_GameConstants_h__)
