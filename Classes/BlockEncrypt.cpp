#include "BlockEncrypt.h"

static const char szSavePath[] = "gamedata";
static const char szPassword[] = "Etond";

BlockEncrypt *BlockEncrypt::m_pBlockEncrypt;

BlockEncrypt *BlockEncrypt::getInstance()
{
	if (m_pBlockEncrypt == NULL)
    {
        m_pBlockEncrypt = new BlockEncrypt();
    }

	return m_pBlockEncrypt;
}

void BlockEncrypt::destroyInstance()
{
    if (m_pBlockEncrypt)
    {
        delete m_pBlockEncrypt;
        m_pBlockEncrypt = NULL;
    }
}

BlockEncrypt::BlockEncrypt()
{
    m_pGameData = new BlockGameData;

    memset(m_pGameData, 0, sizeof(BlockGameData));

    m_pGameData->m_bIsMusicOn = true;
    m_pGameData->m_bIsHelpOn = true;

    m_pGameData->m_fShortest = 999999999.0f;
    m_pGameData->m_iTimeCount = 0;
    m_pGameData->m_iStepCount = 0;
}

BlockEncrypt::~BlockEncrypt()
{
    if (m_pGameData) 
    {
        delete m_pGameData;
		m_pGameData = NULL;
    }
}


bool BlockEncrypt::initFromFile()
{
    // CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(szSavePath);
   
    std::string  path;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
    ssize_t len;
    unsigned char *data;
    data = FileUtils::getInstance()->getFileDataFromZip(szSavePath, "rb", &len);
    path = FileUtils::getInstance()->getWritablePath();

    if (data)
    {
        delete []data;
        data = NULL;
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    path = "";
#endif

    path += szSavePath;

    FILE *pFile = NULL;
    pFile = fopen(path.c_str(), "rb");

    if (pFile == NULL)
    {
        
        saveToFile();
        return false;
    }

    fread(m_pGameData, sizeof(char), sizeof(BlockGameData), pFile);

    fclose(pFile);
    
    pFile = NULL;

    decode();
    
    return true;
}

void BlockEncrypt::encode()
{
    char *pBuf = NULL;
    int i, j = 0;
    int len;

    pBuf = (char *) m_pGameData;
    len = strlen(szPassword);
    
    for (i = 0; i < sizeof(BlockGameData); i++)
    {
        pBuf[i] ^= szPassword[j++];
        j %= len;
    }
}

void BlockEncrypt::encode(char *pBuf)
{
    int i, j = 0;
    int len;

    len = strlen(szPassword);
    
    for (i = 0; i < sizeof(BlockGameData); i++)
    {
        pBuf[i] ^= szPassword[j++];
        j %= len;
    }
}

void BlockEncrypt::decode()
{
    char *pBuf = NULL;
    int i, j = 0;
    int len;

    pBuf = (char *) m_pGameData;
    len = strlen(szPassword);
    
    for (i = 0; i < sizeof(BlockGameData); i++)
    {
        pBuf[i] ^= szPassword[j++];
        j %= len;
    }
}

bool BlockEncrypt::saveToFile()
{
    std::string path;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ssize_t len;
    unsigned char *data;
    data = FileUtils::getInstance()->getFileDataFromZip(szSavePath, "wb", &len);
    path = FileUtils::getInstance()->getWritablePath();
    
    if(data)
    {
        delete []data;
        data = NULL;
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    path = "";
#endif
    
    path += szSavePath;

    FILE *pFile = NULL;
    char buf[512];

    pFile = fopen(path.c_str(), "wb");

    if (NULL == pFile)
    {
        return false;
    }

    memcpy(buf, m_pGameData, sizeof(BlockGameData));

    encode(buf);

    fwrite(buf, sizeof(char), sizeof(BlockGameData), pFile);

    fclose(pFile);

    return true;
}

void BlockEncrypt::initConfig()
{
    initFromFile();
}

void BlockEncrypt::setMusic(bool isOn)
{
    m_pGameData->m_bIsMusicOn = isOn;
    saveToFile();
}

void BlockEncrypt::setHelp(bool isOn)
{
    m_pGameData->m_bIsHelpOn = isOn;
    saveToFile();
}

void BlockEncrypt::setClassic(float isOn)
{
    if (fabs(m_pGameData->m_fShortest - isOn) < 0.000001) return ;
    m_pGameData->m_fShortest = isOn;
    saveToFile();
}

void BlockEncrypt::setTime(int isOn)
{
    if (isOn <= m_pGameData->m_iTimeCount) return ;

    m_pGameData->m_iTimeCount = isOn;
    saveToFile();
}

void BlockEncrypt::setStep(int isOn)
{
    if (isOn <= m_pGameData->m_iStepCount) return ;

    m_pGameData->m_iStepCount = isOn;
    saveToFile();
}


bool BlockEncrypt::getMusic()
{
    return m_pGameData->m_bIsMusicOn;
}

bool BlockEncrypt::getHelp()
{
    return m_pGameData->m_bIsHelpOn;
}

float BlockEncrypt::getClassic()
{
    return m_pGameData->m_fShortest;
}

int BlockEncrypt::getTime()
{
    return m_pGameData->m_iTimeCount;
}

int BlockEncrypt::getStep()
{
    return m_pGameData->m_iStepCount;
}
