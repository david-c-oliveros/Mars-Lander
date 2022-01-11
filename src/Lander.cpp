#include "Lander.h"

Lander::Lander(float x, float y)
{
    lander_spr = new olc::Sprite("./res/sprites/temp/enemy_1_sprite.png");
    lander_dec = new olc::Decal(lander_spr);
    this->vPos = { x, y };
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

void Lander::draw(olc::PixelGameEngine* pge)
{
    pge->DrawDecal(this->vPos, lander_dec, {4.0f, 4.0f });
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

void Lander::update(olc::vf2d vDeltaVel)
{
    this->vVel += vDeltaVel;
    this->vPos += this->vVel;
}
