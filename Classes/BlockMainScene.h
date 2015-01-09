#ifndef __BLOCK_MAIN_SCENE_H__
#define __BLOCK_MAIN_SCENE_H__


#include "BlockCommon.h"
#include "BlockBgLayer.h"
#include "BlockGameScene.h"
#include "BlockSongManager.h"
#include "BlockFgToast.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

class BlockMainScene : public Scene
{
public:
	BlockMainScene();

	bool init();
    CREATE_FUNC(BlockMainScene);
private:
	void initBgLayer();
	void initMenuLayer();

    void gameModeCallback(Object *pSender);

    void moregameCallback(Object *pSender);
    void rankCallback(Object *pSender);
    void aboutCallback(Object *pSender);
	// set music and the help
    void setCallback(Object *pSender);

private:
	Layer *m_pBgLayer;
	Layer *m_pMenuLayer;

	bool m_bIsMusicOn;
	bool m_bIsHelpOn;

    MenuItemImage *m_pMusic;
    MenuItemImage *m_pHelp;
};

#endif
