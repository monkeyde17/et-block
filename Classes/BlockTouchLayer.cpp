#include "BlockTouchLayer.h"

void BlockTouchLayer::onEnter()
{
	Layer::onEnter();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(BlockTouchLayer::onTouchBegan, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool BlockTouchLayer::onTouchBegan(Touch *pT, Event *pE)
{

    Scene *pScene = Director::getInstance()->getRunningScene();
    BlockGameScene *pGameScene = dynamic_cast<BlockGameScene*>(pScene);
	
    return pGameScene->onTouch(pT, pE);
	
	//return true;
}



