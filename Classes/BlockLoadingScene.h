#ifndef __BLOCK_LOADING_SCENE_H__
#define __BLOCK_LOADING_SCENE_H__

#include "BlockCommon.h"
#include "BlockMainScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

class BlockLoadingScene : public Scene
{
public:
	bool init();
    CREATE_FUNC(BlockLoadingScene);

	void loading();
private:
	void initAction();
	void loadingCallBack(Node *pNode);
};

#endif
