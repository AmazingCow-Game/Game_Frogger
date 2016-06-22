//Header
#include "Tree.h"

//Usings
USING_NS_GAME_FROGGER

////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kTreesFramesCount = 4;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Tree::Tree()
{
    //Init the Sprite.
    auto &sprite = getSprite();
    sprite.loadTexture("tree_3.png");
}

Tree::~Tree()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                             //
////////////////////////////////////////////////////////////////////////////////
void Tree::update(float dt)
{
    auto newPos = getPosition() + (getSpeed() * dt);

    //Moving to left...
    if(newPos.x < getMovementMinX() && getSpeed().x < 0)
        newPos.x = getMovementMaxX();

    //Moving to right...
    if(newPos.x > getMovementMaxX() && getSpeed().x > 0)
        newPos.x = getMovementMinX();

    setPosition(newPos);
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void Tree::setSpeed(const Lore::Vector2 &speed)
{
    Enemy::setSpeed(speed);
    getSprite().setFlipX(speed.x > 0);
}
