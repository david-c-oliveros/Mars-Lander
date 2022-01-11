#include "Lander.h"
#include "vendor/olcPixelGameEngine.h"


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
        olc::vf2d vGrav;
        olc::vf2d vDeltaVel;
        float fTargetFrameTime = 1.0f / 200.0f;
        float fAccumulatedTime = 0.0f;
        int iFrameCount = 0;
        float fAvg;
        float fTotalTime;

    public:
        Game()
        {
            sAppName = "Hello";
        }


    public:
        bool OnUserCreate() override
        {
            // Set gravity variable - will later encapsulate into gravity function

            marsLander = new Lander(50, 50);
            marsLander->setPos({ (float)ScreenWidth() / 2, 50 });
            vGrav = { 0.0, 1.0 };
            vDeltaVel = { 0.0, 0.0 };

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
            this->vDeltaVel = { 0.0, 0.0 };
            if (GetKey(olc::Key::NP0).bHeld) vDeltaVel += {  0.0, -1.5};
            if (GetKey(olc::Key::A).bHeld) vDeltaVel   += { -0.5,  0.0};
            if (GetKey(olc::Key::D).bHeld) vDeltaVel   += {  0.5,  0.0};

            vDeltaVel += vGrav;
            vDeltaVel *= fElapsedTime;
            marsLander->update(vDeltaVel);

            Clear(olc::VERY_DARK_BLUE);

            // Debug - Set Lander position to top of screen after it falls off the bottom
            if (marsLander->getPos().y > ScreenHeight())
            {
                marsLander->setPos({ (float)ScreenWidth() / 2, 50 });
                marsLander->setVel({ 0.0, 0.0 });
            }

            marsLander->draw(this);

            fTotalTime += fElapsedTime;
            iFrameCount++;
            if (iFrameCount % 1000 == 0)
            {
                fAvg = fTotalTime / 1000;
                std::cout << fAvg << std::endl;
                fTotalTime = 0.0f;
            }
            return true;
        }
};



/***************************/
/*        Functions        */
/***************************/



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
