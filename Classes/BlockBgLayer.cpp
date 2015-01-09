#include "BlockBgLayer.h"


BlockBgLayer::BlockBgLayer(const char szBgPath[])
{
    m_szBgPath = szBgPath;
}

BlockBgLayer *BlockBgLayer::create(const char szBgPath[])
{
    BlockBgLayer *pLayer = new BlockBgLayer(szBgPath);

	if (pLayer && pLayer->init())
    {
        pLayer->autorelease();
		return pLayer;
    }

    CC_SAFE_DELETE(pLayer);
	pLayer = NULL;

	return NULL;
}

bool BlockBgLayer::init()
{
	if (!Layer::init())
    {
		return false;
    }

	initBg();

	return true;
}


void BlockBgLayer::initBg()
{
    m_pBg = Sprite::create(m_szBgPath);
    m_pBg->setPosition(BLOCKPOS(DWIDTH / 2, DHEIGHT / 2));
	addChild(m_pBg);
}
