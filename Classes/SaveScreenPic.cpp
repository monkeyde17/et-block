#include "SaveScreenPic.h"

const char PICNAME[] = "NoWhiteCat";

SaveScreenPic* SaveScreenPic::createSaveScreenPic()
{
    SaveScreenPic* pSaveScreenPic = new SaveScreenPic();
    if (pSaveScreenPic && pSaveScreenPic->init())
    {
        pSaveScreenPic->autorelease();
        return pSaveScreenPic;
    }
    CC_SAFE_DELETE(pSaveScreenPic);
    return NULL;
}

bool SaveScreenPic::saveJPG(char *rePath)
{
    Size size = Director::getInstance()->getWinSize();
    std::string str = FileUtils::sharedFileUtils()->getWritablePath();

    char name[50];
    unsigned long len = 0;
    unsigned char* data = NULL;


    ETRenderTexture* pScreen = ETRenderTexture::create(size.width, size.height, kCCTexture2DPixelFormat_RGBA8888);

    Scene* pCurScene = Director::getInstance()->getRunningScene();

    pScreen->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    pCurScene->visit();
    pScreen->end();

    //pScreen->getSprite()->setTextureRect(CCRectMake(0, 0, size.width, size.height));

    time_t ct = ETTime::getCurrentTime();
    memset(name, 0, sizeof(name));
    sprintf(name, "%s%lu.jpg", PICNAME, ct);

    //sprintf(rePath, "%s%s", str.c_str(), name);

	//return true;
	
	// there are
	
    //Image *pImage = pScreen->newCCImage(true);
	//CCLOG(rePath);
	bool result = false;
	if (true)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,
			"org/cocos2dx/weibo/FilePath",
			"getScreenShotPath",
            "()Ljava/lang/String;");
		char *path;
		if (isHave)
        {
			jobject jobj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
			std::string tstr = JniHelper::jstring2string((jstring)jobj).c_str();
            //result = pImage->saveToFile(CCString::createWithFormat("%s/%s", tstr.c_str(), name)->getCString(), true);

            sprintf(rePath, "%s/%s", tstr.c_str(), name);
            CCLOG("%s", rePath);
			result = pScreen->saveToFile(rePath, Image::Format::JPG);
        }
        else
        {
			rePath = NULL;
			CCLOG("JNI ERROR");
			
        }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

        sprintf(rePath, "%s%s", str.c_str(), name);
		CCLOG("%s", rePath);
        result = pScreen->saveToFile(String::createWithFormat("%s%s", str.c_str(), name)->getCString(), Image::Format::JPG);
#endif 
    }

    //CC_SAFE_DELETE(pImage);
    //CC_SAFE_DELETE(pScreen);

    //return true;
    return result;
}

CCLayerColor* SaveScreenPic::getWhiteLayer()
{
	/*m_pLayer = StarForegroundLayer::create(ccc4(255, 255, 255, 123));

	CCSequence *seq = CCSequence::create(CCFadeOut::create(0.5f), CCCallFuncN::create(this, callfuncN_selector(SaveScreenPic::runActionCallback)), NULL);
	m_pLayer->runAction(seq);

	return m_pLayer;*/
	return nullptr;
}

void SaveScreenPic::runActionCallback(Node *pNode)
{
    Scene *pScene = dynamic_cast<Scene*>(m_pLayer->getParent());
    pScene->resumeSchedulerAndActions();
    m_pLayer->removeFromParentAndCleanup(true);
}

//ETRanderTexture
bool ETRenderTexture::saveToFile(const std::string& fullpath, Image::Format format)
{
    CCASSERT(format == Image::Format::JPG || format == Image::Format::PNG,
             "the image can only be saved as JPG or PNG format");
    
    std::string str = FileUtils::sharedFileUtils()->getWritablePath();

    _saveToFileCommand.init(_globalZOrder);
    _saveToFileCommand.func = CC_CALLBACK_0(ETRenderTexture::onSaveToFile,this,fullpath);
    CCLOG("%d", _saveToFileCommand.getType());
    
    Director::getInstance()->getRenderer()->addCommand(&_saveToFileCommand);
    return true;
}

ETRenderTexture * ETRenderTexture::create(int w, int h, Texture2D::PixelFormat eFormat)
{
    ETRenderTexture *ret = new ETRenderTexture();

    if(ret && ret->initWithWidthAndHeight(w, h, eFormat))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}