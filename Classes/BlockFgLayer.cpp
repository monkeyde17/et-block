#include "BlockFgLayer.h"

void BlockFgLayer::onEnter()
{
	Layer::onEnter();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(BlockFgLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(BlockFgLayer::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(BlockFgLayer::onTouchCancelled, this);
    listener->onTouchEnded = CC_CALLBACK_2(BlockFgLayer::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool BlockFgLayer::onTouchBegan(Touch *pT, Event *pE)
{
    if (m_pMenu)
    {
        m_bIsTouch =  m_pMenu->onTouchBegan(pT, pE);
    }
	
	return true;
}

void BlockFgLayer::onTouchMoved(Touch *pT, Event *pE)
{
	if (m_bIsTouch)
    {
		m_pMenu->onTouchMoved(pT, pE);
    }
}

void BlockFgLayer::onTouchCancelled(Touch *pT, Event *pE)
{
	if (m_bIsTouch)
    {
		m_pMenu->onTouchCancelled(pT, pE);
    }
}

void BlockFgLayer::onTouchEnded(Touch *pT, Event *pE)
{
	if (m_bIsTouch)
    {
		m_pMenu->onTouchEnded(pT, pE);
    }
}