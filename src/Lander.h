#pragma once

#include "vendor/olcPixelGameEngine.h"



class Lander
{
    private:
        olc::vf2d vVel;
        olc::vf2d vPos;

    public:
        olc::Sprite* lander_spr = nullptr;
        olc::Decal* lander_dec = nullptr;

        Lander(float x, float y);
        ~Lander();

        olc::vf2d getVel();
        void setVel(olc::vf2d vVel);
        olc::vf2d getPos();
        void setPos(olc::vf2d vPos);
        void draw(olc::PixelGameEngine* pge);

        void addVel(olc::vf2d v);
        void update(olc::vf2d vDeltaVel);
};
