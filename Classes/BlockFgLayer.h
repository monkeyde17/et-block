#ifndef __BLOCK_FG_LAYER_H__
#define __BLOCK_FG_LAYER_H__


#include "BlockCommon.h"
#include "BlockSongManager.h"


class BlockFgLayer : public Layer
{
public:
    BlockFgLayer() : m_bIsTouch(false) {}

	CREATE_FUNC(BlockFgLayer);

	virtual void onEnter();

	bool onTouchBegan(Touch *pT, Event *pE);
	void onTouchMoved(Touch *pT, Event *pE);
	void onTouchEnded(Touch *pT, Event *pE);
	void onTouchCancelled(Touch *pT, Event *pE);

protected:
	Menu *m_pMenu;

private:
	bool m_bIsTouch;
};

#endif