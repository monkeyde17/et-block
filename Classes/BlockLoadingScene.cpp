#include "BlockLoadingScene.h"

bool BlockLoadingScene::init()
{
	if (!Scene::init())
    {
		return false;
    }
	initAction();
	return true;
}

void BlockLoadingScene::initAction()
{
	Sprite *pIcon = Sprite::create(szImgBlockBlackUnClicked);
    pIcon->setPosition(BLOCKPOS(DWIDTH / 2, DHEIGHT / 2));
    pIcon->setOpacity(0);
    pIcon->runAction(
        Sequence::create(
        FadeIn::create(1.0f),
        DelayTime::create(1.5f),
        CallFuncN::create(this, callfuncN_selector(BlockLoadingScene::loadingCallBack)),
		NULL));
    addChild(pIcon);
}

void BlockLoadingScene::loadingCallBack(Node *pNode)
{
    BlockMainScene *pScene = BlockMainScene::create();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, pScene));
}

void BlockLoadingScene::loading()
{
	// srand once
	srand((unsigned int)time(NULL));

	// init the config
    BlockEncrypt::getInstance()->initConfig();

	// loading sound

	for (int i = 0; i < 26; i++)
    {
        SimpleAudioEngine::getInstance()->preloadEffect(szSndKey[i]);
    }

	// loading image

}