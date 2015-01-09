#include "BlockFgToast.h"

BlockFgToast::BlockFgToast(std::string path)
{
	m_sPath = path;
}

BlockFgToast* BlockFgToast::create(std::string path)
{
    BlockFgToast *pToast = new BlockFgToast(path);
    if (pToast && pToast->init())
    {
        pToast->autorelease();
		return pToast;
    }

	CC_SAFE_DELETE(pToast);
	return nullptr;
}

void BlockFgToast::onEnter()
{
	Layer::onEnter();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(BlockFgToast::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(BlockFgToast::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool BlockFgToast::onTouchBegan(Touch *pT, Event *pE)
{
	return true;
}

void BlockFgToast::onTouchEnded(Touch *pT, Event *pE)
{
    removeFromParent();
}

bool BlockFgToast::init()
{
    if (!LayerColor::initWithColor(ccc4(0, 0, 0, 123)))
    {
		return false;
    }

	initBg();

	return true;
}

void BlockFgToast::initBg()
{
    Size bSize = getContentSize();
	m_pBg = Sprite::create(m_sPath);
    m_pBg->setPosition(Point(bSize.width / 2, bSize.height / 2));
	addChild(m_pBg);
}