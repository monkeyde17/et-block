#include "BlockPassLayer.h"

bool BlockPassLayer::init()
{
	if (!BlockFgLayer::init())
    {
		return false;
    }

	initBg();
	initAction();
	initMenu();

	return true;
}

BlockPassLayer::BlockPassLayer(int m, bool isPass)
{
	// fail pass bg
    if (!isPass) { m_pPath = szImgBgFail; }
	
	m_mode = m;
	m_bIsPass = isPass;
}

BlockPassLayer* BlockPassLayer::create(int m, bool isPass)
{
	BlockPassLayer *pLayer = new BlockPassLayer(m, isPass);
	if (pLayer && pLayer->init())
    {
        pLayer->autorelease();
		return pLayer;
    }

    CC_SAFE_DELETE(pLayer);
	return nullptr;
}

void BlockPassLayer::initBg()
{
    if (!m_bIsPass)
    {
        m_pBg = Sprite::create(m_pPath);
        m_pBg->setAnchorPoint(Point(0, 0));
        addChild(m_pBg);
    }

	Size s;

    Sprite *pName = Sprite::create(szImgWrdName);
    s = pName->getContentSize();
    pName->setPosition(BLOCKPOS(DWIDTH - s.width * 0.6, DHEIGHT - s.height));
	addChild(pName);
    pName->runAction(FadeIn::create(1));

	Sprite *pMode;
    if (m_mode == GAMEMODECLASSIC) pMode = Sprite::create(szImgWrdClassic);
    else if (m_mode == GAMEMODESTEP) pMode = Sprite::create(szImgWrdStep);
    else if (m_mode == GAMEMODETIME) pMode = Sprite::create(szImgWrdTime);
	s = pMode->getContentSize();
	pMode->setPosition(BLOCKPOS(DWIDTH / 2, DHEIGHT - s.height * 1.5));
	addChild(pMode);
    pMode->runAction(FadeIn::create(1));
}

void BlockPassLayer::initAction()
{


	Size s;

    BlockGameScene *pScene = dynamic_cast<BlockGameScene*>(Director::getInstance()->getRunningScene());
    int iBlockCnt = pScene->getCurrentCount();
    float fCurTime = pScene->getCurrentTime(); 
    bool bIsHigh = false;

	std::string sCur, sBest;

    if (m_mode == GAMEMODECLASSIC) 
    {
        bIsHigh = (fabs(fCurTime - BlockEncrypt::getInstance()->getClassic()) < 0.000001);

        sCur = String::createWithFormat("%.3f", fCurTime)->_string;
		sBest = String::createWithFormat("%.3f", BlockEncrypt::getInstance()->getClassic())->_string;
    }
    else if (m_mode == GAMEMODETIME) 
    {
        bIsHigh = (iBlockCnt == BlockEncrypt::getInstance()->getTime());

        sCur = String::createWithFormat("%002d", iBlockCnt)->_string;
		sBest = String::createWithFormat("%002d", BlockEncrypt::getInstance()->getTime())->_string;
    }
    else if (m_mode == GAMEMODESTEP) 
    {
        bIsHigh = (iBlockCnt == BlockEncrypt::getInstance()->getStep());

        sCur = String::createWithFormat("%002d", iBlockCnt)->_string;
		sBest = String::createWithFormat("%002d", BlockEncrypt::getInstance()->getStep())->_string;
    }

    if (m_bIsPass)
    {
        LabelBMFont *pCurLabel = LabelBMFont::create(sCur, szFontNumber);
        pCurLabel->setScale(3);
        pCurLabel->setPosition(BLOCKPOS(DWIDTH / 2, DHEIGHT * 0.6));
        addChild(pCurLabel);
    }
    else
    {
        Sprite *pFail = Sprite::create(szImgWrdFail);
        pFail->setPosition(BLOCKPOS(DWIDTH / 2, DHEIGHT * 0.6));
        pFail->setScale(3);
        addChild(pFail);
		
    }

	if (!bIsHigh)
    {
        if (sBest.length() < 10)
        {
            LabelBMFont *pBestLabel = LabelBMFont::create(sBest, szFontNumber);
            pBestLabel->setScale(1.5);
            s = pBestLabel->getContentSize();
            pBestLabel->setPosition(BLOCKPOS(DWIDTH / 2 + s.width * 0.8, DHEIGHT * 0.4));
            addChild(pBestLabel);

            Sprite *pWrdBest = Sprite::create(szImgWrdBest);
            s = pWrdBest->getContentSize();
            pWrdBest->setPosition(BLOCKPOS(DWIDTH / 2 - s.width * 0.8, DHEIGHT * 0.4));
            addChild(pWrdBest);
        }
    }
    else
    {
        Sprite *pWrdNew = Sprite::create(szImgWrdNew);
        s = pWrdNew->getContentSize();
        pWrdNew->setPosition(Point(DWIDTH / 2, DHEIGHT * 0.4));
        addChild(pWrdNew);
    }
}

void BlockPassLayer::initMenu()
{
	m_pMenu = Menu::create();
    m_pMenu->setPosition(Point::ZERO);
	addChild(m_pMenu);
	

	MenuItemImage *pShare;
	MenuItemImage *pBack;
	MenuItemImage *pReplay;

	Size s;

    pBack = MenuItemImage::create(szImgBtnBack, "", "", CC_CALLBACK_1(BlockPassLayer::backCallback, this));
    s = pBack->getContentSize();
    pBack->setPosition(BLOCKPOS(DWIDTH / 2.0, DHEIGHT / 5 + s.height / 2));
    m_pMenu->addChild(pBack);
    pBack->runAction(FadeIn::create(1));

    pShare = MenuItemImage::create(szImgBtnShare, "", "", CC_CALLBACK_1(BlockPassLayer::shareCallback, this));
    s = pShare->getContentSize();
    pShare->setPosition(BLOCKPOS(DWIDTH / 2.0 - s.width * 2, DHEIGHT / 5 + s.height / 2));
    m_pMenu->addChild(pShare);
    pShare->runAction(FadeIn::create(1));

    pReplay = MenuItemImage::create(szImgBtnReplay, "", "", CC_CALLBACK_1(BlockPassLayer::replayCallback, this));
    s = pReplay->getContentSize();
    pReplay->setPosition(BLOCKPOS(DWIDTH / 2.0 + s.width * 2, DHEIGHT / 5 + s.height / 2));
    m_pMenu->addChild(pReplay);
    pReplay->runAction(FadeIn::create(1));
}

void BlockPassLayer::backCallback(Ref *pSender)
{
	CCLOG("*****back*******");
    BlockSongManager::getInstance()->button();
    Director::getInstance()->replaceScene(BlockMainScene::create());
}

void BlockPassLayer::shareCallback(Ref *pSender)
{
	CCLOG("*****share*******");
    BlockSongManager::getInstance()->button();

    auto pScene = Director::getInstance()->getRunningScene();

    pScene->addChild(FgShareLayer::create(), 9999, 9999);
}

void BlockPassLayer::replayCallback(Ref *pSender)
{
	CCLOG("*****replay*******");
    BlockSongManager::getInstance()->button();
    Director::getInstance()->replaceScene(BlockGameScene::create(m_mode));
}