#ifndef __BLOCK_PASS_LAYER_H__
#define __BLOCK_PASS_LAYER_H__


#include "BlockFgLayer.h"
#include "BlockGameScene.h"
#include "BlockMainScene.h"
#include "FgShareLayer.h"


class BlockPassLayer : public BlockFgLayer
{
public:
	BlockPassLayer(int m, bool isPass);

	static BlockPassLayer* create(int m, bool isPass);

	bool init();

private:
	void initBg();
	void initAction();
	void initMenu();

	void backCallback(Ref *pSender);
	void shareCallback(Ref *pSender);
	void replayCallback(Ref *pSender);

private:
	Sprite *m_pBg;
	const char *m_pPath;

	int m_mode;
	bool m_bIsPass;
};

#endif