#include "Lander.h"
#include "vendor/olcPixelGameEngine.h"
#include "vendor/olcPGEX_Graphics3D.h"
#include "vendor/olcPGEX_TransformedView.h"
#include <sstream>




/***************************/
/*        Functions        */
/***************************/

void printVec(olc::GFX3D::vec3d v)
{
    std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;
}





/**********************************/
/*        Global Variables        */
/**********************************/




/****************************/
/*        Game Class        */
/****************************/
class Game : public olc::PixelGameEngine
{
    private:
        olc::Sprite* spr = nullptr;
        olc::Decal* dec = nullptr;
        Lander* marsLander = nullptr;

        olc::GFX3D::vec3d vGrav;
        olc::GFX3D::vec3d vDeltaVel;
        float fThrustMag = -1.5f;

        float fTargetFrameTime = 1.0f / 200.0f;
        float fAccumulatedTime = 0.0f;
        int iFrameCount = 0;
        float fAvg;
        float fTotalTime;
        float fRotate = 0.0f;

    public:
        Game()
        {
            sAppName = "Hello";
        }


    public:
        bool OnUserCreate() override
        {
            marsLander = new Lander(50, 50, 0);
            marsLander->setPos({ (float)ScreenWidth() / 2, 50 });
            vGrav = { 0.0f, 0.4f, 0.0f };
            vDeltaVel = { 0.0f, 0.0f, 0.0f };
            marsLander->printSpriteSize();

            return true;
        }


        bool OnUserUpdate(float fElapsedTime) override
        {
//            fAccumulatedTime += fElapsedTime;
//            if (fAccumulatedTime >= fTargetFrameTime)
//            {
//                fAccumulatedTime -= fTargetFrameTime;
//                fElapsedTime = fTargetFrameTime;
//            } else {
//                return true;
//            }


            /***********************************/
            /*     Respond to Player Input     */
            /***********************************/
            vDeltaVel = { 0.0f, 0.0f, 0.0f };
            fRotate = 0.0f;

            olc::GFX3D::vec3d vUnitVec = { 0, 1, 0 };
            olc::GFX3D::mat4x4 mRotMatrix = olc::GFX3D::Math::Mat_MakeRotationZ(marsLander->getRot());
//            olc::GFX3D::vec3d vVelDir = olc::GFX3D::Math::Mat_MultiplyVector(mRotMatrix, vUnitVec);

            if (GetKey(olc::Key::NP0).bHeld)
            {
                olc::GFX3D::vec3d vVelDir = olc::GFX3D::Math::Mat_MultiplyVector(mRotMatrix, vUnitVec);
                olc::GFX3D::vec3d vThrustVec = olc::GFX3D::Math::Vec_Mul(vVelDir, fThrustMag);
                vDeltaVel = olc::GFX3D::Math::Vec_Add(vDeltaVel, vThrustVec);
            }

            if (GetKey(olc::Key::A).bHeld) fRotate -= 0.01f;
            if (GetKey(olc::Key::D).bHeld) fRotate += 0.01f;

//            vDeltaVel = olc::GFX3D::Math::Vec_Add(vDeltaVel, vVelDir);

            /******************************************/
            /*        Add Acceleration Vectors        */
            /******************************************/
            vDeltaVel = olc::GFX3D::Math::Vec_Add(vDeltaVel, vGrav);
            vDeltaVel = olc::GFX3D::Math::Vec_Mul(vDeltaVel, fElapsedTime);
            marsLander->update(vDeltaVel, fRotate);


            /******************************/
            /*        Clear Screen        */
            /******************************/
            Clear(olc::VERY_DARK_BLUE);


            /***************************/
            /*        Draw Call        */
            /***************************/
            marsLander->drawSelf(this);

            // Debug - Print average fElapsedTime
            fTotalTime += fElapsedTime;
            iFrameCount++;
            if (iFrameCount % 1000 == 0)
            {
                fAvg = fTotalTime / 1000;
                std::cout << fAvg << std::endl;
                fTotalTime = 0.0f;
            }

            // Debug - Draw Lander's velcity
            std::stringstream ss;
            olc::vf2d vVel2D = { marsLander->getVel().x, marsLander->getVel().y };
            ss << vVel2D;
            std::string s = ss.str();
            DrawString(25, 25, s, olc::WHITE, 4);

            /***********************************/
            /*     Check Border Collisions     */
            /***********************************/
            if (marsLander->getPos().y >= ScreenHeight() - 75)
            {
                marsLander->setPos({ marsLander->getPos().x, (float)ScreenHeight() - 75 });
//                olc::GFX3D::vec3d vV = { 0.4f,  0.0f, 0.0f };
//                olc::GFX3D::vec3d vV = { 0.0f, -0.1f, 0.0f };
//                olc::GFX3D::vec3d vNewVel = marsLander->getVel() * vV;
//                marsLander->setVel(vNewVel);
            }

            return true;
        }
};



/**********************/
/*        Main        */
/**********************/
int main()
{
    Game demo;
    if (demo.Construct(1600,  1200, 1, 1))
    {
        demo.Start();
    }
    return 0;
}
