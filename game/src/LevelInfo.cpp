
//Header
#include "LevelInfo.h"
//std
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

NS_GAME_FROGGER_BEGIN
using namespace std;

std::array<int, kTilesCount_X> asIntArray(const std::string &str)
{
    std::array<int, kTilesCount_X> arr;
    std::stringstream ss(str);

    std::string s;

    for(auto &e : arr)
    {
        ss >> s;
        if(s == "-")
            e = 0;
        else
            e = std::stoi(s);
    }

    return arr;
}

std::string stringTrimAndUpper(const std::string &str)
{
    int start  = str.find_first_not_of(" ");
    int finish = str.find_last_not_of (" ");

    auto ret =  str.substr(start, (finish - start) + 1);
    for(auto &c : ret) c = std::toupper(c);

    return ret;
}

void buildEnemyInfo(const std::string &line, LevelInfo &levelInfo)
{
    //Each line of enemy info is defined as:
    //    Row |     Type        |  Dir       | MIN  | MAX  | PATTERN
    //    int | Tree/Turtle/Car | Left/Right | int  | int  | int array
    //Each field of each line must be separated by the '|' (pipe) char.
    //So let's read it :D

    std::vector<std::string> fields;
    fields.reserve(6); //We have at most 6 fields.

    auto index = 0;
    while(true)
    {
        auto pos   = line.find_first_of("|", index);
        auto field = line.substr(index, pos - index);

        fields.push_back(stringTrimAndUpper(field));

        index = pos + 1;

        //Reach the end of fields...
        if(pos == std::string::npos)
            break;
    }


    //COWTODO: Check errors.
    EnemyInfo enemyInfo;

    enemyInfo.row       = std::stoi(fields[0]);
    FROGGER_DLOG("ROW : %d", enemyInfo.row);
    enemyInfo.direction = (fields[2] == "LEFT") ? -1 : 1;
    enemyInfo.minSpeed  = std::stoi(fields[3]);
    enemyInfo.maxSpeed  = std::stoi(fields[4]);
    enemyInfo.pattern   = asIntArray(fields[5]);

         if(fields[1] == "CAR"   ) levelInfo.carsInfo.push_back   (enemyInfo);
    else if(fields[1] == "TREE"  ) levelInfo.treesInfo.push_back  (enemyInfo);
    else if(fields[1] == "TURTLE") levelInfo.turtlesInfo.push_back(enemyInfo);
}

LevelInfo LevelInfo_GetInfoForLevel(int level)
{
    LevelInfo levelInfo;
    levelInfo.level = level;

    //Open the file
    auto levelName = CoreGame::StringUtils::format("LevelData/level%d.txt", level);
    auto levelPath = Lore::AssetsManager::instance()->fullpath(levelName);
    auto infile    = std::ifstream(levelPath);

    COREGAME_VERIFY(infile.is_open());


    std::string line;
    int         lineIndex = 0;

    while(!infile.eof())
    {
        getline(infile, line);

        //Empty or commented line...
        if(line.empty() || line[0] == '#')
            continue;

        //Fist line of file is the LevelTime
        if(lineIndex == 0)
            //COWTODO: Check errors.
            levelInfo.time = std::stoi(line);
        else
            buildEnemyInfo(line, levelInfo);

        ++lineIndex;
    }

    return levelInfo;
}

NS_GAME_FROGGER_END
