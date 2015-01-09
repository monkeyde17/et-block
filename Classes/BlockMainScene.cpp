#include "BlockMainScene.h"

BlockMainScene::BlockMainScene()
{
    m_bIsMusicOn = BlockEncrypt::getInstance()->getMusic();
    m_bIsHelpOn = BlockEncrypt::getInstance()->getHelp();
}

bool BlockMainScene::init()
{
	if(!Scene::init())
    {
		return false;
    }

    initBgLayer();
	initMenuLayer();
	
	return true;
}

void BlockMainScene::initBgLayer()
{
    m_pBgLayer = BlockBgLayer::create(szImgBgMain);
    addChild(m_pBgLayer, zOrderBlockBgLayer, kTagBlockBgLayer);
}

void BlockMainScene::initMenuLayer()
{
	m_pMenuLayer = Menu::create();
    m_pMenuLayer->setPosition(CCPointZero);
    addChild(m_pMenuLayer, zOrderBlockMenuLayer, kTagBlockMenuLayer);
	
	// game mode
    MenuItemImage *pClassic;
    MenuItemImage *pTime;
    MenuItemImage *pStep;

	// set btn
    MenuItemImage *pMore;
    MenuItemImage *pRank;
    MenuItemImage *pAbout;

	// public size 
	Size s;

    pClassic = MenuItemImage::create("", "", CC_CALLBACK_1(BlockMainScene::gameModeCallback, this));
    pClassic->setNormalSpriteFrame(Sprite::create(szImgBtnClassic)->getDisplayFrame());
    pClassic->setTag(100);
    s = BLOCKGETSIZE(pClassic);
    pClassic->setPosition(BLOCKPOS(s.width / 2, DHEIGHT - s.height / 2));
    m_pMenuLayer->addChild(pClassic);

    pStep = MenuItemImage::create("", "", CC_CALLBACK_1(BlockMainScene::gameModeCallback, this));
    pStep->setNormalSpriteFrame(Sprite::create(szImgBtnStep)->getDisplayFrame());
    pStep->setTag(101);
    s = BLOCKGETSIZE(pStep);
    pStep->setPosition(BLOCKPOS(DWIDTH - s.width / 2, DHEIGHT - s.height / 2));
    m_pMenuLayer->addChild(pStep);


    pTime = MenuItemImage::create("", "", CC_CALLBACK_1(BlockMainScene::gameModeCallback, this));
    pTime->setNormalSpriteFrame(Sprite::create(szImgBtnTime)->getDisplayFrame());
    pTime->setTag(102);
    s = BLOCKGETSIZE(pTime);
    pTime->setPosition(BLOCKPOS(s.width / 2, s.height / 2));
    m_pMenuLayer->addChild(pTime);

	// set btn as follow
    pMore = MenuItemImage::create("", "", CC_CALLBACK_1(BlockMainScene::moregameCallback, this));
    pMore->setNormalSpriteFrame(Sprite::create(szImgBtnMore)->getDisplayFrame());
    s = BLOCKGETSIZE(pMore);
    pMore->setPosition(BLOCKPOS(404 + s.width / 2, DHEIGHT - 685 - s.height / 2));
    m_pMenuLayer->addChild(pMore);

    m_pMusic = MenuItemImage::create("", "", CC_CALLBACK_1(BlockMainScene::setCallback, this));
    m_pMusic->setNormalSpriteFrame(Sprite::create(m_bIsMusicOn ? szImgBtnMusicOn : szImgBtnMusicOff)->getDisplayFrame());
    m_pMusic->setTag(0);
    s = BLOCKGETSIZE(m_pMusic);
    m_pMusic->setPosition(BLOCKPOS(530 + s.width / 2, DHEIGHT - 633 - s.height / 2));
    m_pMenuLayer->addChild(m_pMusic);

    m_pHelp = MenuItemImage::create("", "", CC_CALLBACK_1(BlockMainScene::setCallback, this));
    m_pHelp->setNormalSpriteFrame(Sprite::create(m_bIsHelpOn ? szImgBtnHelpOn : szImgBtnHelpOff)->getDisplayFrame());
    m_pHelp->setTag(1);
    s = BLOCKGETSIZE(m_pHelp);
    m_pHelp->setPosition(BLOCKPOS(614 + s.width / 2, DHEIGHT - 721 - s.height / 2));
    m_pMenuLayer->addChild(m_pHelp);

    pRank = MenuItemImage::create("", "", CC_CALLBACK_1(BlockMainScene::rankCallback, this));
    pRank->setNormalSpriteFrame(Sprite::create(szImgBtnRank)->getDisplayFrame());
    s = BLOCKGETSIZE(pRank);
    pRank->setPosition(BLOCKPOS(596 + s.width / 2, DHEIGHT - 841 - s.height / 2));
    m_pMenuLayer->addChild(pRank);

    pAbout = MenuItemImage::create("", "", CC_CALLBACK_1(BlockMainScene::aboutCallback, this));
    pAbout->setNormalSpriteFrame(Sprite::create(szImgBtnAbout)->getDisplayFrame());
    s = BLOCKGETSIZE(pAbout);
    pAbout->setPosition(BLOCKPOS(515 + s.width / 2, DHEIGHT - 924 - s.height / 2));
    m_pMenuLayer->addChild(pAbout);
}

void BlockMainScene::gameModeCallback(Object *pSender)
{
    BlockSongManager::getInstance()->button();
    Node *pNode = dynamic_cast<Node*>(pSender);
    int tag = pNode->getTag();

    BlockGameScene *pScene = BlockGameScene::create(tag % 10);
    Director::getInstance()->replaceScene(pScene);
}

void BlockMainScene::moregameCallback(Object *pSender)
{
    BlockSongManager::getInstance()->button();
    CCLOG("More");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,
        "org/cocos2dx/lib/Cocos2dxActivity",
        "openUrl",
        "()V");

    if (isHave)
    {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    }
#endif
}


void BlockMainScene::setCallback(Object *pSender)
{
    BlockSongManager::getInstance()->button();
    Node *pNode = dynamic_cast<Node*>(pSender);
    CCLOG("Set %d", pNode->getTag());
    int tag = pNode->getTag();

    // music
	if (tag == 0)
    {
        m_bIsMusicOn = !m_bIsMusicOn;
        BlockEncrypt::getInstance()->setMusic(m_bIsMusicOn);
        m_pMusic->setNormalSpriteFrame(Sprite::create(m_bIsMusicOn ? szImgBtnMusicOn : szImgBtnMusicOff)->getDisplayFrame());
    }
    else
    {
        m_bIsHelpOn = !m_bIsHelpOn;
        BlockEncrypt::getInstance()->setHelp(m_bIsHelpOn);
        m_pHelp->setNormalSpriteFrame(Sprite::create(m_bIsHelpOn ? szImgBtnHelpOn : szImgBtnHelpOff)->getDisplayFrame());
    }
}

void BlockMainScene::rankCallback(Object *pSender)
{
	CCLOG("Rank");
    BlockEncrypt::destroyInstance();
    BlockSongManager::destroyInstance();
    Director::getInstance()->end();
}

void BlockMainScene::aboutCallback(Object *pSender)
{
    BlockSongManager::getInstance()->button();
	CCLOG("About");
    BlockFgToast *pToast = BlockFgToast::create(szImgToastAbout);
	addChild(pToast, 99999, 99999);
}