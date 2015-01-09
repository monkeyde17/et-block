#ifndef __SAVESCREENPIC_H__
#define __SAVESCREENPIC_H__


#include "cocos2d.h"
#include "BlockCommon.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

USING_NS_CC;

class ETRenderTexture : public RenderTexture
{
public:
	static ETRenderTexture * create(int w, int h, Texture2D::PixelFormat eFormat);

    virtual bool saveToFile(const std::string& fileName, Image::Format format);

};	

class SaveScreenPic : public Node
{
public:
	static SaveScreenPic* createSaveScreenPic();

	// return the pic path
	bool saveJPG(char *path);

	void runActionCallback(Node *pNode);

	LayerColor* getWhiteLayer();

private:
    Layer *m_pLayer;
};

#endif