#pragma once

#include "vendor/olcPixelGameEngine.h"



class Lander
{
    private:
        olc::vf2d vVel;
        olc::vf2d vPos;
        float fAngle;

    public:
        olc::Sprite* landerSprite = nullptr;
        olc::Decal* landerDecal = nullptr;

        Lander(float x, float y, float fTheta);
        ~Lander();

        olc::vf2d getVel();
        void setVel(olc::vf2d vVel);
        olc::vf2d getPos();
        void setPos(olc::vf2d vPos);
        void drawSelf(olc::PixelGameEngine* pge);

        void addVel(olc::vf2d v);
        void update(olc::vf2d vDeltaVel, float fTheta);
};
