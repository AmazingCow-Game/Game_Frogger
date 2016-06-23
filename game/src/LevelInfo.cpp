
//Header
#include "LevelInfo.h"
//std
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

NS_GAME_FROGGER_BEGIN
using namespace std;

std::vector<int> as_int_vector(const std::string &str)
{
    std::vector<int>  vec;
    std::stringstream ss;

    ss << str;
    while(ss)
    {
        int i;
        ss >> i;
        vec.push_back(i);
    }

    return vec;
}

void fillEnemyInfo(std::array<EnemyInfo, 5> &enemyInfo,
                   int       enemyInfoIndex,
                   const     std::string line)
{
    std::cout << line << std::endl;
    auto content = as_int_vector(line);

    enemyInfo[enemyInfoIndex].minSpeed = content[0];
    enemyInfo[enemyInfoIndex].maxSpeed = content[1];

    std::copy_n(
        std::begin(content)+2, 13,
        std::begin(enemyInfo[enemyInfoIndex].pattern)
    );
}

LevelInfo LevelInfo_GetInfoForLevel(int level)
{
    LevelInfo levelInfo;

    auto levelPath = Lore::AssetsManager::instance()->fullpath("LevelData/level1.txt");
    auto infile    = std::ifstream(levelPath);
    COREGAME_VERIFY(infile);

    std::string line;
    int currentLineCount = 0;

    while(!infile.eof())
    {
        getline(infile, line);

        //Empty or commented line...
        if(line.empty() || line[0] == '#')
            continue;

        ++currentLineCount;

        switch(currentLineCount)
        {
            //Time
            case 1 : {
                std::stringstream ss;
                ss << line;

                levelInfo.time = atoi(ss.str().c_str());
            } break;

            //Cars
            case 2 :
            case 3 :
            case 4 :
            case 5 :
            case 6 : {
                auto index = (currentLineCount - 2);
                fillEnemyInfo(levelInfo.carsInfo, index, line);
            }; break;

            //Trees
            case  7 :
            case  8 :
            case  9 :
            case 10 :
            case 11 : {
                auto index = (currentLineCount - 7);
                fillEnemyInfo(levelInfo.treesInfo, index, line);
            }

            //Trees
            case 12 :
            case 13 :
            case 14 :
            case 15 :
            case 16 : {
                auto index = (currentLineCount - 12);
                fillEnemyInfo(levelInfo.turtlesInfo, index, line);
            }
        }
    }

    return levelInfo;
}

NS_GAME_FROGGER_END
