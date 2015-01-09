#ifndef _BLOCK_ENCRYPT_H_
#define _BLOCK_ENCRYPT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include "BlockCommon.h"

/**
 * ���ݴ洢
 */
typedef struct __BlockGameData
{
	bool m_bIsMusicOn;
	bool m_bIsHelpOn;

	// the classic mode
	float m_fShortest;

	// the time mode
	int m_iTimeCount;

	// the step mode
	int m_iStepCount;

}BlockGameData;

class BlockEncrypt
{
public:
    BlockEncrypt();
    ~BlockEncrypt();
	
    static BlockEncrypt* getInstance();
	static void destroyInstance();

	void setMusic(bool isOn);
	void setHelp(bool isOn);
	void setClassic(float isOn);
	void setTime(int isOn);
	void setStep(int isOn);

	bool getMusic();
	bool getHelp();
	float getClassic();
	int getTime();
	int getStep();

public:
	void initConfig();

private:
    /**
     * ���ļ���ȡ
     */
    bool initFromFile();

    /*
     * ����
     */
    void encode();
    void encode(char *buf);

    /**
     * ����
     */
    void decode();

    /**
     * �������ļ�
     */
    bool saveToFile();

private:
    BlockGameData		*m_pGameData;
    static BlockEncrypt	*m_pBlockEncrypt;
};

#endif /* _STAR_ENCRYPT_H_ */