#ifndef _FG_SHARE_LAYER_H_
#define _FG_SHARE_LAYER_H_

#include "SaveScreenPic.h"
#include "BlockCommon.h"
#include "BlockSongManager.h"

using namespace CocosDenshion;

class FgShareLayer : public LayerColor
{
public:
    FgShareLayer();
    virtual ~FgShareLayer();

    virtual bool init();

    virtual void onEnter() override;

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

    CREATE_FUNC(FgShareLayer);
private:
	void addBtn();
	void addBg();
private:
	void renrenCallback(Ref *pSender);
	void qzoneCallback(Ref *pSender);
	void weiboCallback(Ref *pSender);
	void weixinCallback(Ref *pSender);
private:
	Menu *m_pMenu;
	Sprite *m_pBg;

	bool m_bIsTouched;
};

#endif
