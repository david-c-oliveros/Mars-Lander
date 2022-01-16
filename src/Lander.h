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
        bool bEngineOn;

        olc::vf2d vSpriteScale = { 0.17f, 0.17f };
        olc::vf2d vCenter;
        float fOffset = 13.0f;
        float fScaledOffset = (fOffset * vSpriteScale.x);

        olc::vf2d vExhaustSourceSize = { 256, 300 };
        olc::vf2d vExhaustSourcePos = { 4 * vExhaustSourceSize.x, 4 * vExhaustSourceSize.y };
        olc::vf2d vExhaustScale = { 0.3f, 0.3f };
        olc::vf2d vExhaustCenter;

    public:
        olc::Sprite* landerSprite = nullptr;
        olc::Decal* landerDecal = nullptr;

        olc::Sprite* exhaustSprite = nullptr;
        olc::Decal* exhaustDecal = nullptr;

        Lander(float x, float y, float fTheta);
        ~Lander();

        olc::GFX3D::vec3d getVel();
        olc::GFX3D::vec3d getPos();
        float getRot();

        void setVel(olc::GFX3D::vec3d vVel);
        void setPos(olc::GFX3D::vec3d vPos);

        void drawSelf(olc::PixelGameEngine* pge);
        void drawExhaust(olc::PixelGameEngine* pge);

        void addVel(olc::GFX3D::vec3d v);
        void update(olc::GFX3D::vec3d vDeltaVel, float fTheta);

        void printSpriteSize();
        int getSpriteWidth();
        int getSpriteHeight();
};
