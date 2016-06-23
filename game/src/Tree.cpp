//Header
#include "Tree.h"

//Usings
USING_NS_GAME_FROGGER


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Tree::Tree(int type)
{
    //Init the Sprite.
    auto &sprite = getSprite();
    sprite.loadTexture(
        CoreGame::StringUtils::format("Images/tree_%d.png", type)
    );
}

Tree::~Tree()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void Tree::setSpeed(const Lore::Vector2 &speed)
{
    Enemy::setSpeed(speed);
    getSprite().setFlipX(speed.x > 0);
}
