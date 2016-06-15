//Header
#include "GameObject.h"

//Usings
USING_NS_GAME_FROGGER;

////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void GameObject::update(float dt)
{
    //Empty...
}

void GameObject::draw()
{
    m_sprite.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
//Position
void GameObject::setPosition(const Lore::Vector2 &pos)
{
    m_sprite.setPosition(pos);
}

const Lore::Vector2& GameObject::getPosition() const
{
    return m_sprite.getPosition();
}


//Speed
void GameObject::setSpeed(const Lore::Vector2 &speed)
{
    m_speed = speed;
}

const Lore::Vector2& GameObject::getSpeed() const
{
    return m_speed;
}


//State
void GameObject::setState(State state)
{
    m_state = state;
}

GameObject::State GameObject::getState() const
{
    return m_state;
}


//Sprite
Lore::Sprite& GameObject::getSprite()
{
    return m_sprite;
}





