#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "BlockCommon.h"
#include "BlockLoadingScene.h"

USING_NS_CC;
using namespace CocosDenshion;


AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    if(!glview) 
    {
        glview = GLView::createWithRect("Block", Rect(0, 0, 320, 480));
        director->setOpenGLView(glview);
    }

    director->setContentScaleFactor(RHEIGHT / DHEIGHT);

    glview->setDesignResolutionSize(RWIDTH, RHEIGHT, ResolutionPolicy::EXACT_FIT);

	//if (DHEIGHT * WWIDTH <= DWIDTH * WHEIGHT)
    //{
    //    glview->setDesignResolutionSize(RWIDTH, RHEIGHT, ResolutionPolicy::FIXED_WIDTH);
    //}
    //else
    //{
    //    glview->setDesignResolutionSize(RWIDTH, RHEIGHT, ResolutionPolicy::FIXED_HEIGHT);
    //}

    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);

    auto scene = BlockLoadingScene::create();
    director->runWithScene(scene);

    scene->loading();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();

    Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();

    Director::getInstance()->startAnimation();
}
