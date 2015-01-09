#include "FgShareLayer.h"

FgShareLayer::FgShareLayer()
{
    m_pMenu = NULL;
    m_bIsTouched = false;
}

FgShareLayer::~FgShareLayer()
{

}

bool FgShareLayer::init()
{
    if (!LayerColor::initWithColor(ccc4(0, 0, 0, 124)))
    {
        return false;
    }

	addBg();
	addBtn();

    return true;
}

void FgShareLayer::onEnter()
{
	LayerColor::onEnter();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(FgShareLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(FgShareLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(FgShareLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool FgShareLayer::onTouchBegan(Touch *pT, Event *pE)
{
    m_bIsTouched = m_pMenu->onTouchBegan(pT, pE);
	return true;
}

void FgShareLayer::onTouchMoved(Touch *pT, Event *pE)
{
	if (m_bIsTouched)
    {
        m_pMenu->onTouchMoved(pT, pE);
    }
}

void FgShareLayer::onTouchEnded(Touch *pT, Event *pE)
{
	if (m_bIsTouched)
    {
        m_pMenu->onTouchEnded(pT, pE);
    }
}


void FgShareLayer::addBg()
{
	m_pBg = Sprite::create(szImgFgShare);
    m_pBg->setPosition(BLOCKPOS(DWIDTH / 2, DHEIGHT / 2));
	addChild(m_pBg);
}

void FgShareLayer::addBtn()
{
	CCMenuItemImage *pWeixin;
	CCMenuItemImage *pQzone;
	CCMenuItemImage *pRenren;
	CCMenuItemImage *pWeibo;

	CCSize s;
	CCSize bg = m_pBg->getContentSize();


    pWeixin = CCMenuItemImage::create("", "", CC_CALLBACK_1(FgShareLayer::weixinCallback, this));
    pWeixin->setNormalSpriteFrame(Sprite::create(szImgFgBtnShareWeixin)->getDisplayFrame());
    s = pWeixin->getContentSize();
    pWeixin->setPosition(ccp(bg.width / 3 - FIXWIDTH, bg.height * 2 / 3 + FIXHEIGHT));

 
    pQzone = CCMenuItemImage::create("", "", CC_CALLBACK_1(FgShareLayer::qzoneCallback, this));
    pQzone->setNormalSpriteFrame(Sprite::create(szImgFgBtnShareQzone)->getDisplayFrame());
    s = pQzone->getContentSize();
    pQzone->setPosition(ccp(bg.width * 2 / 3 + FIXWIDTH, bg.height * 2 / 3 + FIXHEIGHT));

    pRenren = CCMenuItemImage::create("", "", CC_CALLBACK_1(FgShareLayer::renrenCallback, this));
    pRenren->setNormalSpriteFrame(Sprite::create(szImgFgBtnShareRenren)->getDisplayFrame());
    s = pRenren->getContentSize();
    pRenren->setPosition(ccp(bg.width / 3 - FIXWIDTH, bg.height / 3 - FIXHEIGHT));

    pWeibo = CCMenuItemImage::create("", "", CC_CALLBACK_1(FgShareLayer::weiboCallback, this));
    pWeibo->setNormalSpriteFrame(Sprite::create(szImgFgBtnShareWeibo)->getDisplayFrame());
    s = pWeibo->getContentSize();
    pWeibo->setPosition(ccp(bg.width * 2 / 3 + FIXWIDTH, bg.height / 3 - FIXHEIGHT));
	
    m_pMenu = Menu::create();
    m_pMenu->addChild(pWeixin);
    m_pMenu->addChild(pQzone);
    m_pMenu->addChild(pRenren);
    m_pMenu->addChild(pWeibo);
    m_pMenu->setPosition(CCPointZero);
	m_pBg->addChild(m_pMenu);
}

void FgShareLayer::weixinCallback(CCObject *pSender)
{
    BlockSongManager::getInstance()->button();
    setVisible(false);
	char imgPath[128];
	SaveScreenPic *pSaveScreen = SaveScreenPic::createSaveScreenPic();
    pSaveScreen->saveJPG(imgPath);
    addChild(pSaveScreen);
    setVisible(true);
	
	

	CCLOG("%s", imgPath);
	
    std::string pstr = imgPath;
    auto callback = [pstr](float delta)
    {
        CCLOG("XXXXXXXXXFinishScreenShotXXXXXXXXXX");
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,
			"org/cocos2dx/lib/Cocos2dxActivity",
			"shareToWeixin",
            "(Ljava/lang/String;)V");
		if (isHave)
        {
			jstring jpath = methodInfo.env->NewStringUTF(pstr.c_str());
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jpath);
        }
#endif
    };

    Director::getInstance()->getScheduler()->schedule(callback, Director::getInstance(), 0.0, 0, 0.0, false, "key");

	CCLOG("********** Share Finish***********");
    removeFromParentAndCleanup(true);
}

void FgShareLayer::qzoneCallback(CCObject *pSender)
{
    //SimpleAudioEngine::sharedEngine()->playEffect(szSndEffectBtn);
    BlockSongManager::getInstance()->button();

    setVisible(false);
	char imgPath[128];
	SaveScreenPic *pSaveScreen = SaveScreenPic::createSaveScreenPic();
    pSaveScreen->saveJPG(imgPath);
    addChild(pSaveScreen);
    setVisible(true);

	CCLOG("%s", imgPath);
	
    std::string pstr = imgPath;
    auto callback = [pstr](float delta)
    {
        CCLOG("XXXXXXXXXFinishScreenShotXXXXXXXXXX");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,
			"org/cocos2dx/lib/Cocos2dxActivity",
			"shareToPengyouquan",
            "(Ljava/lang/String;)V");
		if (isHave)
        {
			jstring jpath = methodInfo.env->NewStringUTF(pstr.c_str());
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jpath);
        }
#endif
    };

    Director::getInstance()->getScheduler()->schedule(callback, Director::getInstance(), 0.0, 0, 0.0, false, "key");

	CCLOG("********** Share Finish***********");
    removeFromParentAndCleanup(true);
}

void FgShareLayer::renrenCallback(CCObject *pSender)
{
    BlockSongManager::getInstance()->button();
    //SimpleAudioEngine::sharedEngine()->playEffect(szSndEffectBtn);
    setVisible(false);
	char imgPath[128];
	SaveScreenPic *pSaveScreen = SaveScreenPic::createSaveScreenPic();
    pSaveScreen->saveJPG(imgPath);
    addChild(pSaveScreen);
    setVisible(true);

	CCLOG("%s", imgPath);
	
    std::string pstr = imgPath;
    auto callback = [pstr](float delta)
    {
        CCLOG("XXXXXXXXXFinishScreenShotXXXXXXXXXX");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,
			"org/cocos2dx/lib/Cocos2dxActivity",
			"shareToRenren",
            "(Ljava/lang/String;)V");
		if (isHave)
        {
			jstring jpath = methodInfo.env->NewStringUTF(pstr.c_str());
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jpath);
        }

#endif
    };

    Director::getInstance()->getScheduler()->schedule(callback, Director::getInstance(), 0.0, 0, 0.0, false, "key");


	CCLOG("********** Share Finish***********");
    removeFromParentAndCleanup(true);
}

void FgShareLayer::weiboCallback(CCObject *pSender)
{
    BlockSongManager::getInstance()->button();
    //SimpleAudioEngine::sharedEngine()->playEffect(szSndEffectBtn);
    setVisible(false);
	char imgPath[128];
	SaveScreenPic *pSaveScreen = SaveScreenPic::createSaveScreenPic();
    pSaveScreen->saveJPG(imgPath);
    addChild(pSaveScreen);
    setVisible(true);

	CCLOG("%s", imgPath);
	
    std::string pstr = imgPath;
    auto callback = [pstr](float delta)
    {
        CCLOG("XXXXXXXXXFinishScreenShotXXXXXXXXXX");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,
			"org/cocos2dx/lib/Cocos2dxActivity",
			"shareToWeibo",
            "(Ljava/lang/String;)V");
		if (isHave)
        {
			jstring jpath = methodInfo.env->NewStringUTF(pstr.c_str());
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jpath);
        }
#endif
    };

    Director::getInstance()->getScheduler()->schedule(callback, Director::getInstance(), 0.0, 0, 0.0, false, "key");
	CCLOG("********** Share Finish***********");
	removeFromParentAndCleanup(true);
}
