#ifndef __BLOCK_GAME_SCENE_H__
#define __BLOCK_GAME_SCENE_H__

#include "BlockCommon.h"
#include "BlockBar.h"
#include "BlockTouchLayer.h"
#include "BlockBgLayer.h"
#include "BlockPassLayer.h"
#include "BlockSongManager.h"

class BlockTouchLayer;
class BlockBar;

class BlockGameScene : public Scene
{
public:
    BlockGameScene(int gamemode);
	virtual bool init();
    static BlockGameScene* create(int gamemode);

	bool onTouch(Touch *pT, Event *pE);

	void resumeBar(float delta);
	
	void moveBar(float delta);

	BlockBar *queueTail();

    float getCurrentTime() { return m_fCurrentTime; }
    int getCurrentCount() { return m_iRightCount; }
private:
	void initBgLayer();
	void initActionLayer();
	void initTouchLayer();
	void initMenuLayer();
	void initFgLayer();

	BlockBar *queueFront();
	void queuePop(); 
	
	void gameOverFls();
	void addPassLayer(Node *pNode);

private:

	Layer			*m_pBgLayer;
	Layer			*m_pActoinLayer;
	BlockTouchLayer	*m_pTouchLayer;
	Menu			*m_pMenuLayer;

	float			m_fMoveDistance;
	// 0 : classic
	// 1 : step
	// 2 : time
	int		m_iGameMode;

	// for the m_pBars
	// replace the queue
	int		m_iCurrentPos;
	
    BlockBar* m_pBars[BLOCKBARCNT];

	bool	m_bIsGameOver;

	// for classic mode
	bool	m_bIsWin;

	bool	m_bIsFirstClick;

	float	m_fCurrentTime;
	float	m_fRate;
	int		m_iRightCount;

    LabelBMFont *m_pLabel;

	Sprite *m_pStartWrd;
};

#endif
