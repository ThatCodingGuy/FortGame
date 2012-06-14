/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include <OgreManualObject.h>
#include <iostream>

typedef unsigned char block_t;

class Application : public BaseApplication
{
public:
    Application(void);
    virtual ~Application(void);
    Ogre::ManualObject* createCubeMesh(Ogre::String meshName, Ogre::String matName);

    void createPlayer(void);
    void createWorldChunks (void);
    void createChunk (const int StartX, const int StartY, const int StartZ);
    void createPlayerCamera(void);

protected:

    static const int WORLD_SIZE = 64;	// We'll change these later for various test worlds
	static const int CHUNK_SIZE = 16;

	int m_ChunkID;		        // Used for uniquely naming our chunks

	block_t* m_Blocks;	        // Holds the block worlds in a [WORLD_SIZE][WORLD_SIZE][WORLD_SIZE] array

	// Read/write access method for our block world (doesn't check input)
	block_t& GetBlock (const int x, const int y, const int z)
	{
		return m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE];
	}

    // Used for filling our block world
    void initWorldBlocksRandom (const int Divisor);
	void initWorldBlocksSphere (void);

    // Displays the world using the slow shitty method
    // Do not use, here for sake of history
	void displaySimpleWorld (void);


    virtual void createScene(void);
};

#endif // #ifndef __TutorialApplication_h_
