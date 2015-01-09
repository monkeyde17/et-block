#ifndef _BLOCK_BG_LAYER_H_
#define _BLOCK_BG_LAYER_H_

#include "cocos2d.h"
#include "BlockCommon.h"


USING_NS_CC;

class BlockBgLayer : public Layer
{
public:
	BlockBgLayer(const char szBgPath[]);
    virtual bool init();
	static BlockBgLayer* create(const char szBgPath[]);

private:
	void initBg();

private:
	Sprite *m_pBg;
	const char *m_szBgPath;
};

#endif