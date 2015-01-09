#ifndef __BLOCK_FG_TOAST_H__
#define __BLOCK_FG_TOAST_H__


#include "BlockCommon.h"
#include "BlockSongManager.h"


class BlockFgToast : public LayerColor
{
public:
    BlockFgToast(std::string path);
	
	bool init();

	static BlockFgToast* create(std::string path);

	virtual void onEnter();

	bool onTouchBegan(Touch *pT, Event *pE);
	void onTouchEnded(Touch *pT, Event *pE);

protected:
	void initBg();

protected:
	Sprite *m_pBg;
	std::string m_sPath;
};

#endif