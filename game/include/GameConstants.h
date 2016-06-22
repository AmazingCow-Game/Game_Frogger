#ifndef __Game_Frogger_include_GameConstants_h__
#define __Game_Frogger_include_GameConstants_h__

//Game_Frogger
#include "GameFrogger_Utils.h"


NS_GAME_FROGGER_BEGIN

////////////////////////////////////////////////////////////////////////////////
// Fonts                                                                      //
////////////////////////////////////////////////////////////////////////////////
constexpr auto kFontName = "nokiafc22.ttf";
//Menu
constexpr int kFontSize_Menu = 22;
//Hud
constexpr int kFontSize_Hud_Big   = 12;
constexpr int kFontSize_Hud_Small =  8;
//Game
constexpr int kFontSize_StateText = 40;


////////////////////////////////////////////////////////////////////////////////
// Sounds                                                                     //
////////////////////////////////////////////////////////////////////////////////
constexpr auto kSoundName_MusicIntro   = "Music.wav";
constexpr auto kSoundName_Jump         = "Jump.wav";
constexpr auto kSoundName_Victory      = "Completion.wav";
constexpr auto kSoundName_ReachTarget  = "ReachTarget.wav";
constexpr auto kSoundName_DefeatWater  = "Dead_Water.wav";
constexpr auto kSoundName_DefeatNormal = "Dead_Normal.wav";
constexpr auto kSoundName_TimeUp       = "TimeUp.wav";

NS_GAME_FROGGER_END
#endif // defined(__Game_Frogger_include_GameConstants_h__)
