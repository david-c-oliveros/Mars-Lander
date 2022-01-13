#include "Lander.h"

Lander::Lander(float x, float y, float fTheta)
{
    landerSprite = new olc::Sprite("./res/sprites/temp/enemy_1_sprite.png");
    landerDecal = new olc::Decal(landerSprite);
    vPos = { x, y };
    fAngle = fTheta;
}

Lander::~Lander() {}

olc::vf2d Lander::getVel()
{
    return this->vVel;
}

void Lander::setVel(olc::vf2d vVel)
{
    this->vVel = vVel;
}

void Lander::drawSelf(olc::PixelGameEngine* pge)
{
//    pge->DrawDecal(this->vPos, lander_dec, {4.0f, 4.0f });
    pge->DrawRotatedDecal(vPos, landerDecal, fAngle, { 0.0, 0.0 }, {4.0f, 4.0f });
}

olc::vf2d Lander::getPos()
{
    return this->vPos;
}

void Lander::setPos(olc::vf2d vPos)
{
    this->vPos = vPos;
}

void Lander::addVel(olc::vf2d v)
{
    this->vVel +=  v;
}

void Lander::update(olc::vf2d vDeltaVel, float fTheta)
{
    vVel += vDeltaVel;
    vPos += vVel;
    fAngle += fTheta;
}
