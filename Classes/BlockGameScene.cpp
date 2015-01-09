#include "BlockGameScene.h"


BlockGameScene::BlockGameScene(int gamemode)
{
    m_iGameMode = gamemode;
    m_fMoveDistance = 0.0;
    m_iCurrentPos = 1;
    m_bIsGameOver = false;
    m_bIsWin = false;
    m_bIsFirstClick = false;
	m_fRate = 1.0;

    if (m_iGameMode == GAMEMODETIME) m_fCurrentTime = 30.0;
    else m_fCurrentTime = 0.0;

    m_iRightCount = 0;
}

bool BlockGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    initBgLayer();
    initActionLayer();
    initTouchLayer();
	initFgLayer();

    BlockSongManager::getInstance()->refresh();

    return true;
}

BlockGameScene* BlockGameScene::create(int gamemode)
{
    BlockGameScene *pScene = new BlockGameScene(gamemode);
    if (pScene && pScene->init())
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return nullptr;
}

void BlockGameScene::initBgLayer()
{
    m_pBgLayer = BlockBgLayer::create(szImgBgRand[rand() % 3]);
    addChild(m_pBgLayer, zOrderBlockBgLayer, kTagBlockBgLayer);
}

void BlockGameScene::initActionLayer()
{
    m_pActoinLayer = Layer::create();
    addChild(m_pActoinLayer, zOrderBlockActionLayer, kTagBlockActionLayer);

    for (int i = 0; i < BLOCKBARCNT; i++)
    {
        m_pBars[i] = BlockBar::create(m_iGameMode);
        m_pBars[i]->setPosition(Point(0, DHEIGHT * i / 4));
        m_pActoinLayer->addChild(m_pBars[i]);
    }
    m_pBars[0]->getAllWhite();

	// start wrd
    m_pStartWrd = Sprite::create(szImgWrdStart);
    m_pBars[1]->addChild(m_pStartWrd);
    m_pStartWrd->setPosition(m_pBars[1]->getBlackPos());
	


	// label
    m_pLabel = LabelBMFont::create(".0123456789\"", szFontNumber);
    m_pLabel->setPosition(Point(DWIDTH / 2.0, DHEIGHT * 0.9));
    m_pLabel->setColor(ccRED);
    m_pLabel->setScale(2);
    m_pActoinLayer->addChild(m_pLabel);

    if (m_iGameMode == GAMEMODECLASSIC)
    {
        m_pLabel->setString("0.000\"");
    }
    else if (m_iGameMode == GAMEMODETIME)
    {
        m_pLabel->setString("30.000\"");
    }
    else if (m_iGameMode == GAMEMODESTEP)
    {
        m_pLabel->setString("00");
    }
}

void BlockGameScene::initTouchLayer()
{
    m_pTouchLayer = BlockTouchLayer::create();
    addChild(m_pTouchLayer, zOrderBlockTouchLayer, kTagBlockTouchLayer);
}

void BlockGameScene::initFgLayer()
{
    if (! BlockEncrypt::getInstance()->getHelp()) return ;

    BlockFgToast *pToast = BlockFgToast::create(szImgToastHelp[m_iGameMode]);
	addChild(pToast, 99999, 99999);
}

bool BlockGameScene::onTouch(Touch *pT, Event *pE)
{
    if (m_bIsGameOver) return false;

    BlockBar *pBlockBar = queueFront();

    bool rv =  pBlockBar->onTouchBegan(pT, pE);

    if (rv)
    {
        if (pBlockBar->isClickBlack())
        {
            BlockSongManager::getInstance()->song();

            m_fMoveDistance += 0.5;
            queuePop();
            m_iRightCount++;
            CCLOG("***GAME CNT : %d", m_iRightCount);

            if (!m_bIsFirstClick)
            {
				// game start
                m_bIsFirstClick = true;

                m_pStartWrd->setVisible(false);

                if (m_iGameMode != GAMEMODESTEP) schedule(schedule_selector(BlockGameScene::resumeBar));
                else schedule(schedule_selector(BlockGameScene::moveBar));
            }

            if (m_iGameMode == GAMEMODECLASSIC)
            {
                if (m_iRightCount >= CLASSICBLOCKCNT)
                {
                    // win
                    m_bIsWin = true;
                    m_bIsGameOver = true;

                    unschedule(schedule_selector(BlockGameScene::resumeBar));
                    BlockEncrypt::getInstance()->setClassic(m_fCurrentTime);
                    gameOverFls();
                }
            }
            else if (m_iGameMode == GAMEMODESTEP)
            {
                m_pLabel->setString(String::createWithFormat("%002d", m_iRightCount)->_string);
            }
        }
        else
        {
            // fail
            BlockSongManager::getInstance()->button();

            m_bIsGameOver = true;

            if (m_iGameMode == GAMEMODECLASSIC)
            {
                m_bIsWin = false;
                unschedule(schedule_selector(BlockGameScene::resumeBar));

            }
            else if (m_iGameMode == GAMEMODETIME)
            {
                m_bIsWin = true;
                unschedule(schedule_selector(BlockGameScene::resumeBar));
                BlockEncrypt::getInstance()->setTime(m_iRightCount);
            }
            else 
            {
                m_bIsWin = true;
                m_pLabel->setString(String::createWithFormat("%002d", m_iRightCount)->_string);
                unschedule(schedule_selector(BlockGameScene::moveBar));
                BlockEncrypt::getInstance()->setStep(m_iRightCount);
            }

            // TODO
            gameOverFls();
        }
    }
    return rv;
}

// the classic and time
void BlockGameScene::resumeBar(float delta)
{
    int dT = (int) (m_fMoveDistance * 2) + 1;
    float tDec = 0;

    if (m_fMoveDistance > 0)
    {
        if (m_fMoveDistance > dT * delta) 
        {
            m_fMoveDistance -= dT * delta;
            tDec = dT * delta;
        }
        else 
        {
            tDec = m_fMoveDistance;
            m_fMoveDistance = 0;
        }

        for (int i = 0; i < BLOCKBARCNT; i++)
        {
            m_pBars[i]->moveDown(tDec);
        }
    }


    if (m_iGameMode == GAMEMODECLASSIC)
    {
        m_fCurrentTime += delta;
        m_pLabel->setString(String::createWithFormat("%.3lf\"", m_fCurrentTime)->_string);
    }
    else if (m_iGameMode == GAMEMODETIME)
    {
        m_fCurrentTime -= delta;
        if (m_fCurrentTime < -0.000001) 
        {
            m_fCurrentTime = 0.0;
			m_bIsWin = true;
            m_bIsGameOver = true;
        }

        m_pLabel->setString(String::createWithFormat("%.3lf\"", m_fCurrentTime)->_string);

        if (m_bIsGameOver)
        {
            BlockEncrypt::getInstance()->setTime(m_iRightCount);
            gameOverFls();
        }
    }
}

void BlockGameScene::moveBar(float delta)
{
    m_fRate += 0.0005;
    if (m_fRate >= 4.0) m_fRate = 4.0;
    for (int i = 0; i < BLOCKBARCNT; i++)
    {
        m_pBars[i]->moveDown(m_fRate * delta);
    }

    if (queueFront()->isOverButtom())
    {
        m_bIsWin = true;
        m_bIsGameOver = true;
        unschedule(schedule_selector(BlockGameScene::moveBar));

        BlockEncrypt::getInstance()->setStep(m_iRightCount);
        BlockSongManager::getInstance()->button();

        for (int i = 0; i < BLOCKBARCNT; ++i) m_pBars[i]->runAction(MoveBy::create(0.2, Point(0, DHEIGHT / 4)));

        gameOverFls();
    }
}

BlockBar* BlockGameScene::queueFront()
{
    return m_pBars[m_iCurrentPos];
}

void BlockGameScene::queuePop()
{
    m_iCurrentPos++;
    m_iCurrentPos %= BLOCKBARCNT;
}

BlockBar* BlockGameScene::queueTail()
{
    int pos = (m_iCurrentPos - 1 + BLOCKBARCNT) % BLOCKBARCNT;
    return m_pBars[pos];
}

void BlockGameScene::gameOverFls()
{
	// hide the label
    m_pLabel->setVisible(false);

    // add the pass layer
    runAction(
		Sequence::create(
		DelayTime::create(1.0),
        CallFuncN::create(this, callfuncN_selector(BlockGameScene::addPassLayer)),
		nullptr
        )
        );
}

void BlockGameScene::addPassLayer(Node *pNode)
{
    for (int i = 0; i < BLOCKBARCNT; ++i) m_pBars[i]->setVisible(false);

    BlockPassLayer *pLayer = BlockPassLayer::create(m_iGameMode, m_bIsWin);
    addChild(pLayer, zOrderBlockFgLayer, kTagBlockFgLayer);
}

