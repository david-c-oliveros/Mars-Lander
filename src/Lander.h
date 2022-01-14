#pragma once

#include "vendor/olcPixelGameEngine.h"
#include "vendor/olcPGEX_Graphics3D.h"



class Lander
{
    private:
        olc::GFX3D::vec3d vVel;
        olc::GFX3D::vec3d vPos;
        olc::vf2d v2Pos;
        float fAngle;
        olc::vf2d vCenter;

    public:
        olc::Sprite* landerSprite = nullptr;
        olc::Decal* landerDecal = nullptr;
        olc::vf2d vSpriteScale = { 4.0f, 4.0f };

        Lander(float x, float y, float fTheta);
        ~Lander();

        olc::GFX3D::vec3d getVel();
        olc::GFX3D::vec3d getPos();
        float getRot();

        void setVel(olc::GFX3D::vec3d vVel);
        void setPos(olc::GFX3D::vec3d vPos);

        void drawSelf(olc::PixelGameEngine* pge);

        void addVel(olc::GFX3D::vec3d v);
        void update(olc::GFX3D::vec3d vDeltaVel, float fTheta);

        void printSpriteSize();
};
