#include "BlockSongManager.h"

BlockSongManager *BlockSongManager::m_instance;

BlockSongManager::BlockSongManager()
{
	m_iSongId = rand() % SONGCNT;
	m_iNoteId = 0;

    m_iSongLength = strlen(szSong[m_iSongId]);
}

BlockSongManager * BlockSongManager::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new BlockSongManager();
    }
	return m_instance;
}

void BlockSongManager::destroyInstance()
{
	if (m_instance)
    {
		delete m_instance;
		m_instance = nullptr;
    }
}

void BlockSongManager::song()
{
    playEffect(szSong[m_iSongId][m_iNoteId]);

    m_iNoteId++;
    m_iNoteId %= m_iSongLength;
}

void BlockSongManager::playEffect(char c)
{
    if (!BlockEncrypt::getInstance()->getMusic()) return ;

    SimpleAudioEngine::getInstance()->playEffect(szSndKey[tolower(c) - 'a']);
}

void BlockSongManager::button()
{
    playEffect(rand() % 26 + 'a');
}

void BlockSongManager::refresh()
{
    m_iSongId = rand() % SONGCNT;
	m_iNoteId = 0;

    m_iSongLength = strlen(szSong[m_iSongId]);
}
