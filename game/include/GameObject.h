#ifndef __Game_Frogger_include_GameObject_h__
#define __Game_Frogger_include_GameObject_h__

//Game_Frogger
#include "GameFrogger_Utils.h"

NS_GAME_FROGGER_BEGIN

class GameObject
{
    // Enums //
public:
    enum class State
    {
        Alive,
        Dying,
        Dead
    };


    // CTOR / DTOR //
public:
    GameObject();
    virtual ~GameObject();


    // Update / Draw //
public:
    virtual void update(float dt);
    virtual void draw  ();


    // Public Methods  //
public:
    //Position
    virtual void setPosition(const Lore::Vector2 &pos);
    virtual const Lore::Vector2& getPosition() const;

    //Speed
    virtual void setSpeed(const Lore::Vector2 &speed);
    virtual const Lore::Vector2& getSpeed() const;

    //State
    virtual void setState(State state);
    virtual State getState() const;

    //Sprite
    Lore::Sprite& getSprite();

    //Bounding Box
    virtual Lore::Rectangle getBoundingBox() = 0;


    // iVars //
private:
    Lore::Sprite  m_sprite;
    State         m_state;
    Lore::Vector2 m_speed;
};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_GameObject_h__ //
