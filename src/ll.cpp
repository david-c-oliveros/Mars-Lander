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

        olc::GFX3D::vec3d vGrav = { 0.0f, 0.4f, 0.0f };
        olc::GFX3D::vec3d vDeltaVel = { 0.0f, 0.0f, 0.0f };
        float fThrustMag = -1.0f;

        float fTargetFrameTime = 1.0f / 200.0f;
        float fAccumulatedTime = 0.0f;
        int iFrameCount = 0;
        float fAvg;
        float fTotalTime;
        float fRotate = 0.0f;
        bool bControlSystem = true;
        bool bInput;

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

            olc::GFX3D::vec3d vUnitVec = { 0, 1, 0 };
            olc::GFX3D::mat4x4 mRotMatrix = olc::GFX3D::Math::Mat_MakeRotationZ(marsLander->getRot());

            if (GetKey(olc::Key::NP0).bHeld)
            {
                olc::GFX3D::vec3d vVelDir = olc::GFX3D::Math::Mat_MultiplyVector(mRotMatrix, vUnitVec);
                olc::GFX3D::vec3d vThrustVec = olc::GFX3D::Math::Vec_Mul(vVelDir, fThrustMag);
                vDeltaVel = olc::GFX3D::Math::Vec_Add(vDeltaVel, vThrustVec);
            }

            if (bControlSystem && !bInput) fRotate *= 0.99f;

            if (GetKey(olc::Key::A).bHeld)
            {
                bInput = true;
                fRotate -= 0.00005f;
            } else { bInput = false; }

            if (GetKey(olc::Key::D).bHeld)
            {
                bInput = true;
                fRotate += 0.00005f;
            } else { bInput = false; }


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
            marsLander->drawExhaust(this);


            // Debug - Draw Lander's velcity
            {
                std::stringstream ss;
                olc::vf2d vVel2D = { marsLander->getVel().x, marsLander->getVel().y };
                ss << vVel2D;
                std::string s = ss.str();
                DrawString(25, 25, s, olc::WHITE, 2);
            }


            // Debug - Draw Lander's position
            {
                std::stringstream ss;
                olc::vf2d vPos2D = { marsLander->getPos().x, marsLander->getPos().y };
                ss << vPos2D;
                std::string s = ss.str();
                DrawString(25, 75, s, olc::WHITE, 2);
            }



            /***********************************/
            /*     Check Border Collisions     */
            /***********************************/
            if (marsLander->getPos().y >= ScreenHeight() - (marsLander->getSpriteHeight() / 2))
            {
                marsLander->setPos({ marsLander->getPos().x, (float)ScreenHeight() - ((float)marsLander->getSpriteHeight() / 2)});
                olc::GFX3D::vec3d vNewVel = { marsLander->getVel().x * 0.4f, marsLander->getVel().y * -0.1f };
                marsLander->setVel(vNewVel);
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
    if (demo.Construct(1600,  1200, 1, 1, false, true))
    {
        demo.Start();
    }
    return 0;
}
