#include "Lander.h"

Lander::Lander(float x, float y, float fTheta)
{
    landerSprite = new olc::Sprite("./res/sprites/Razzi_ship.png");
    landerDecal = new olc::Decal(landerSprite);

    exhaustSprite = new olc::Sprite("./res/sprites/exhaust.png");
    exhaustDecal = new olc::Decal(exhaustSprite);

    bEngineOn = true;

    vPos = { x, y, 0};
    v2Pos = { x, y };
    fAngle = fTheta;

    // Lander sprite offset from center of rotation
    vCenter = { landerSprite->width / 2, landerSprite->height / 2 };

    // Exhaust sprite offset from center of rotation
    vExhaustCenter = { ((vExhaustSourceSize.x / 2) ) + fScaledOffset, -((getSpriteHeight() / 2) - (getSpriteHeight() / 20)) / vExhaustScale.y };
}


Lander::~Lander() {}


olc::GFX3D::vec3d Lander::getVel()
{
    return this->vVel;
}


void Lander::drawSelf(olc::PixelGameEngine* pge)
{
    olc::vf2d vSourcePos = { 0, 0 };
    olc::vf2d vSourceSize = { 406, 1254 };
    pge->DrawRotatedDecal(v2Pos, landerDecal, fAngle, vCenter, vSpriteScale);
}


void Lander::drawExhaust(olc::PixelGameEngine* pge)
{
    // Offset - 126 px on the left
    // Offset - 153 px on the right
    // Offset - 27 px

    // Add an offset to account for engine in sprite not being centered

    olc::vf2d vExhaustPos = { (v2Pos.x),
                              (v2Pos.y) };

    pge->DrawPartialRotatedDecal(vExhaustPos, exhaustDecal, fAngle, vExhaustCenter, vExhaustSourcePos, vExhaustSourceSize, vExhaustScale);
}


olc::GFX3D::vec3d Lander::getPos()
{
    return this->vPos;
}


float Lander::getRot()
{
    return this->fAngle;
}


void Lander::setVel(olc::GFX3D::vec3d vVel)
{
    this->vVel = vVel;
}


void Lander::setPos(olc::GFX3D::vec3d vPos)
{
    this->vPos = vPos;
}


void Lander::addVel(olc::GFX3D::vec3d v)
{
    this->vVel = olc::GFX3D::Math::Vec_Add(this->vVel, v);
}


void Lander::update(olc::GFX3D::vec3d vDeltaVel, float fTheta)
{
    this->vVel = olc::GFX3D::Math::Vec_Add(this->vVel, vDeltaVel);
    this->vPos = olc::GFX3D::Math::Vec_Add(this->vPos, this->vVel);
    this->v2Pos = { this->vPos.x, this->vPos.y };
    fAngle += fTheta;
}


void Lander::printSpriteSize()
{
    std::cout << "Width: " << landerSprite->width << std::endl;
    std::cout << "Height: " << landerSprite->height << std::endl;
}


int Lander::getSpriteWidth()
{
    return landerSprite->width * vSpriteScale.x;
}


int Lander::getSpriteHeight()
{
    return landerSprite->height * vSpriteScale.x;
}
