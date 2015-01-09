#ifndef _BLOCK_COMMON_H_
#define _BLOCK_COMMON_H_

#include "cocos2d.h"
#include "BlockResouce.h"
#include "BlockSong.h"
#include "BlockEncrypt.h"

USING_NS_CC;

// Design
#define DWIDTH		(770)
#define DHEIGHT		(1140)

// Resouce
#define RWIDTH		(770)
#define RHEIGHT		(1140)

// Windows
#define WHEIGHT		(cocos2d::Director::getInstance()->getWinSize().height)
#define WWIDTH		(cocos2d::Director::getInstance()->getWinSize().width)

// Origin
#define OWIDTH		((WWIDTH - DWIDTH) / 2.0)
#define OHEIGHT		((WHEIGHT - DHEIGHT) / 2.0)

// 0 : classic
#define GAMEMODECLASSIC 0
// 1 : step
#define GAMEMODESTEP 1
// 2 : time
#define GAMEMODETIME 2

// Fix
#define FIXHEIGHT	(10)
#define FIXWIDTH	(10)

// block bar nubmer
#define BLOCKBARCNT 6

// Classic mode block count
#define CLASSICBLOCKCNT	(45)

// Time mode 
#define TIMETIMELEFT	(30)

// Block
#define BLOCKPOS(x, y)	((Point(OWIDTH + x, OHEIGHT + y)))

#define BLOCKGETSIZE(x)	((x)->getContentSize())

enum BlockOrder
{
	zOrderBlockBgLayer = 1,
	zOrderBlockActionLayer,
	zOrderBlockTouchLayer,
	zOrderBlockMenuLayer,
	zOrderBlockFgLayer
};

enum BlockTag
{
	kTagBlockBgLayer = 1,
	kTagBlockActionLayer,
	kTagBlockTouchLayer,
	kTagBlockMenuLayer,
	kTagBlockFgLayer
};

// Time & Date
class ETTime 
{
public:
    static unsigned long getCurrentTime()
    {
		time_t t;
		time(&t);
		return t;
    }

    static CCString* getCurrentDate(time_t *t)
    {
		struct tm *timeinfo;
		timeinfo = localtime(t);
    
        return CCString::createWithFormat("%4d-%02d-%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
    }
};

#endif