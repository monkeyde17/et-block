#ifndef __BLOCK_TOUCH_LAYER_H__
#define __BLOCK_TOUCH_LAYER_H__


#include "BlockCommon.h"
#include "BlockGameScene.h"


class BlockTouchLayer : public Layer
{
public:
	CREATE_FUNC(BlockTouchLayer);

	virtual void onEnter();

	bool onTouchBegan(Touch *pT, Event *pE);
};

#endif