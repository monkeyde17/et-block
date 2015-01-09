#include "BlockBar.h"

int BlockBar::m_iRightCount;

BlockBar::BlockBar(int gamemode)
{
    m_iBlackPos = -1;
	m_iIsBlack = -1;
    m_iRightCount = 0;
	m_iGameMode = gamemode;
}

bool BlockBar::initWithColor(const Color4B &color, float w, float h)
{
    if (!LayerColor::initWithColor(color, w, h))
    {
		return false;
    }

	initBlock();
    randBlockPos();

	return true;
}

void BlockBar::initBlock()
{
	Size bSize = getContentSize();

	Size s;
	for (int i = 0; i < 4; i++)
    {
		// first is black
        m_pBlock[i] = Sprite::create(i != 0 ? szImgBlockWhiteUnClicked : szImgBlockBlackUnClicked);
        s = m_pBlock[i]->getContentSize();
		// black is 1
        m_pBlock[i]->setTag(100 + i * 10 + (i != 0 ? 0 : 1));
        m_pBlock[i]->setPosition(Point(i * bSize.width / 4.0 + s.width / 2, bSize.height / 2.0));
        addChild(m_pBlock[i]);
    }

    m_iBlackPos = 0;
}

void BlockBar::randBlockPos()
{
	int nPos = rand() % 4;

    if (m_iBlackPos == -1)
    {
		m_iBlackPos = nPos;
        m_iIsBlack = -1;

        m_pBlock[nPos]->setDisplayFrame(Sprite::create(szImgBlockBlackUnClicked)->getDisplayFrame());
        m_pBlock[nPos]->setTag(191);
        return ;
    }

    m_pBlock[m_iBlackPos]->setOpacity(255);

    swapBlockPos(m_iBlackPos, nPos);

	m_iBlackPos = nPos;

    m_iIsBlack = -1;
}

void BlockBar::swapBlockPos(int src , int dst)
{
	if (src == dst) return ;

    Point srcP = m_pBlock[src]->getPosition();
    Point dstP = m_pBlock[dst]->getPosition();

    m_pBlock[src]->setPosition(dstP);
    m_pBlock[dst]->setPosition(srcP);

	Sprite *tmp = m_pBlock[src];
	m_pBlock[src] = m_pBlock[dst]; 
	m_pBlock[dst] = tmp;
}


BlockBar* BlockBar::create(int gamemode)
{
    BlockBar *pBar = new BlockBar(gamemode);

    if (pBar && pBar->initWithColor(ccc4(0, 0, 0, 255), DWIDTH, DHEIGHT / 4.0))
    {
		pBar->autorelease();
		return pBar;
    }

	CC_SAFE_DELETE(pBar);
	return nullptr;
}

void BlockBar::onEnter()
{
    LayerColor::onEnter();

    //auto listener = EventListenerTouchOneByOne::create();
    //listener->setSwallowTouches(true);

    //listener->onTouchBegan = CC_CALLBACK_2(BlockBar::onTouchBegan, this);

    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void BlockBar::onExit()
{
	LayerColor::onExit();
}

bool BlockBar::onTouchBegan(Touch *pT, Event *pE)
{
    Point point = pT->getLocation();

    if ( point.y > getPositionY() + getContentSize().height || point.y < getPositionY())
    {
        return false;
    }

    int pX = (int)((point.x / DWIDTH) * 4);
    int tag = m_pBlock[pX]->getTag();

	CCLOG("***BlockBar -- point:%lf,%lf, pX:%d Tag:%d", point.x, point.y, pX, tag);

	if (tag % 10)
    {
        m_pBlock[pX]->setOpacity(124);
        m_iIsBlack = 1;
    }
    else
    {
		Sprite *pWhiteClicked = Sprite::create(szImgBlockWhiteClicked);
        pWhiteClicked->setAnchorPoint(Point::ZERO);
        m_pBlock[pX]->addChild(pWhiteClicked);

        pWhiteClicked->runAction(RepeatForever::create(
				Sequence::create(
					FadeOut::create(0.08),
					FadeIn::create(0.08),
					nullptr
				)
            ));
        m_iIsBlack = 0;
    }
    return true;
}

bool BlockBar::isClickBlack()
{
    return m_iIsBlack == 1;
}


bool BlockBar::isOverButtom()
{
    Point pos = getPosition();

    if (pos.y < -DHEIGHT / 4)
    {
        //setPositionY(DHEIGHT / 4 * (BLOCKBARCNT - 1));
        blinkBlackBlock();
        return true;
    }

    return false;
}

void BlockBar::moveDown(float delta)
{

    do
    {
        if (getPositionY() < -getContentSize().height + 0.00001)
        {
            if (GAMEMODECLASSIC == m_iGameMode && m_iRightCount >= (CLASSICBLOCKCNT - BLOCKBARCNT + 1))
            {
                break;
            }

            CCLOG("*****BAR RC %d*****", m_iRightCount);

            setPositionY(getPositionY() + DHEIGHT / 4 * (BLOCKBARCNT));
            randBlockPos();

            m_iRightCount++;
        }
    } while (0);

    setPositionY(getPositionY() - (DHEIGHT / 4 * delta * 2));
}

void BlockBar::getAllWhite()
{
    m_pBlock[m_iBlackPos]->setDisplayFrame(m_pBlock[(m_iBlackPos + 1) % 4]->getDisplayFrame());
    m_pBlock[m_iBlackPos]->setTag(190);

    m_iBlackPos = -1;
}

Point BlockBar::getBlackPos()
{
    if (m_iBlackPos == -1) return Point::ZERO;

    return m_pBlock[m_iBlackPos]->getPosition();
}

void BlockBar::blinkBlackBlock()
{
	m_pBlock[m_iBlackPos]->runAction(
			RepeatForever::create(
				Sequence::create(
					FadeTo::create(0.06, 23),
					FadeTo::create(0.06, 255),
					nullptr
				)
			)
        );
}