#ifndef __Game_Frogger_include_Enemy_h__
#define __Game_Frogger_include_Enemy_h__

//Game_Frogger
#include "GameFrogger_Utils.h"
#include "GameObject.h"


NS_GAME_FROGGER_BEGIN

class Enemy : public GameObject
{
    // CTOR / DTOR //
public:
    Enemy();
    virtual ~Enemy();

    // Update / Draw
public:
    virtual void update(float dt) override;
    virtual void draw() override;


    // Public Methods //
public:
    //Movement Bounds
    void setMovementBounds(int minX, int maxX);
    int  getMovementMinX() const;
    int  getMovementMaxX() const;

    //Position
    virtual void setPosition(const Lore::Vector2 &pos) override;
    virtual const Lore::Vector2& getPosition() const override;

    //Bounding Box
    virtual Lore::Rectangle getRealBoundingBox    ();
    virtual Lore::Rectangle getWrappingBoundingBox();

    //Collision
    virtual bool checkCollision(const Lore::Rectangle &testRect,
                                float safeOffset);


    // Protected Methods //
protected:
    void setWrapping(bool wrapping);
    bool isWrapping() const;

    const Lore::Vector2 getRealPosition() const;
    void setRealPosition(const Lore::Vector2 &position);

    const Lore::Vector2 getWrappingPosition() const;
    void setWrappingPosition(const Lore::Vector2 &position);


    // iVars //
private:
    int  m_minX;
    int  m_maxX;

    Lore::Vector2 m_realPosition;
    Lore::Vector2 m_wrappingPosition;

    bool m_isWrapping;

    Lore::Color m_realColor;
    Lore::Color m_wrappingColor;
};

NS_GAME_FROGGER_END
#endif // __Game_Frogger_include_Enemy_h__ //
