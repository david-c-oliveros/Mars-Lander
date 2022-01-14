#include "Lander.h"

Lander::Lander(float x, float y, float fTheta)
{
    landerSprite = new olc::Sprite("./res/sprites/temp/enemy_1_sprite.png");
    landerDecal = new olc::Decal(landerSprite);
    vPos = { x, y, 0};
    v2Pos = { x, y };
    fAngle = fTheta;
    vCenter = { landerSprite->width / 2, landerSprite->height / 2 };
}


Lander::~Lander() {}


olc::GFX3D::vec3d Lander::getVel()
{
    return this->vVel;
}


void Lander::drawSelf(olc::PixelGameEngine* pge)
{
    pge->DrawRotatedDecal(v2Pos, landerDecal, fAngle, vCenter, vSpriteScale);
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
