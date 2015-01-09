#ifndef __BLOCK_BAR_H__
#define __BLOCK_BAR_H__

#include "BlockCommon.h"
#include "BlockGameScene.h"

class BlockBar : public LayerColor
{
public:
	BlockBar(int gamemode);
    virtual bool initWithColor(const Color4B &color, float w, float h);
	static BlockBar* create(int gamemode);

	virtual void onEnter();
	virtual void onExit();

    bool onTouchBegan(Touch *pT, Event *pE);

	void moveDown(float delta);
public:
	void randBlockPos();
	bool isClickBlack();
	bool isOverButtom();
	void runMoveDown();

	// before game start
	void getAllWhite();

	Point getBlackPos();

	void blinkBlackBlock();

private:
	void initBlock();
	void swapBlockPos(int src, int dst);
private:
	Sprite *m_pBlock[4];
	int m_iBlackPos;

	// -1 means the unclicked
	int m_iIsBlack;
	static int m_iRightCount;
	int m_iGameMode;
};

#endif