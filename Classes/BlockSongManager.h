#ifndef __BLOCK_SONG_MANAGER_H__
#define __BLOCK_SONG_MANAGER_H__

#include "BlockCommon.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

class BlockSongManager 
{
public:
	BlockSongManager();
    static BlockSongManager* getInstance();
    static void destroyInstance();

public:
	void refresh();
    void song(); 
    void button();

private:
	void playEffect(char c);

private:
	int m_iSongId;
	int m_iSongLength;
	int m_iNoteId;

    static BlockSongManager *m_instance;
};

#endif 
