/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
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
#include "Application.h"

//-------------------------------------------------------------------------------------
Application::Application(void)
{
	m_Blocks = new block_t[WORLD_SIZE * WORLD_SIZE * WORLD_SIZE];
    memset(m_Blocks, 0, sizeof(block_t) * WORLD_SIZE * WORLD_SIZE * WORLD_SIZE);
	initWorldBlocksSphere();
	m_ChunkID = 1;

	initWorldBlocksSphere();

}
//-------------------------------------------------------------------------------------
Application::~Application(void)
{
    delete[] m_Blocks;
}


void Application::initWorldBlocksSphere (void)
{
	for (int z = 0; z < WORLD_SIZE; ++z)
	{
		for (int y = 0; y < WORLD_SIZE; ++y)
		{
			for (int x = 0; x < WORLD_SIZE; ++x)
			{
				if (sqrt((float) (x-WORLD_SIZE/2)*(x-WORLD_SIZE/2) + (y-WORLD_SIZE/2)*(y-WORLD_SIZE/2) + (z-WORLD_SIZE/2)*(z-WORLD_SIZE/2)) < WORLD_SIZE/2) GetBlock(x,y,z) = 1;
			}
		}
	}
}

void Application::initWorldBlocksRandom (const int Divisor)
{


	for (int z = 0; z < WORLD_SIZE; ++z)
	{
		for (int y = 0; y < WORLD_SIZE; ++y)
		{
			for (int x = 0; x < WORLD_SIZE; ++x)
			{
				GetBlock(x,y,z) = rand() % Divisor;
			}
		}
	}

}


void Application::createWorldChunks (void)
{
	for (int z = 0; z < WORLD_SIZE; z += CHUNK_SIZE)
	{
		for (int y = 0; y < WORLD_SIZE; y += CHUNK_SIZE)
		{
			for (int x = 0; x < WORLD_SIZE; x += CHUNK_SIZE)
			{
				createChunk(x,y,z);
			}
        }
	}
}


void Application::createChunk (const int StartX, const int StartY, const int StartZ)
{
    Ogre::ManualObject* MeshChunk = new Ogre::ManualObject("MeshManChunk" + Ogre::StringConverter::toString(m_ChunkID));
	MeshChunk->begin("DirtMat");

	int iVertex = 0;
	block_t Block;
	block_t Block1;

	for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
	{
		for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
		{
			for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
			{
				Block = GetBlock(x,y,z);
				if (Block == 0) continue;

					//x-1
				Block1 = 0;
				if (x > StartX) Block1 = GetBlock(x-1,y,z);

                if (Block1 == 0)
				{
					MeshChunk->position(x, y,   z+1);	MeshChunk->normal(-1,0,0);	MeshChunk->textureCoord(0, 1);
					MeshChunk->position(x, y+1, z+1);	MeshChunk->normal(-1,0,0);	MeshChunk->textureCoord(1, 1);
					MeshChunk->position(x, y+1, z);		MeshChunk->normal(-1,0,0);	MeshChunk->textureCoord(1, 0);
					MeshChunk->position(x, y,   z);		MeshChunk->normal(-1,0,0);	MeshChunk->textureCoord(0, 0);

					MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
					MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

					iVertex += 4;
				}

					//x+1
				Block1 = 0;
				if (x < StartX + CHUNK_SIZE - 1) Block1 = GetBlock(x+1,y,z);

				if (Block1 == 0)
				{
					MeshChunk->position(x+1, y,   z);	MeshChunk->normal(1,0,0); MeshChunk->textureCoord(0, 1);
					MeshChunk->position(x+1, y+1, z);	MeshChunk->normal(1,0,0); MeshChunk->textureCoord(1, 1);
					MeshChunk->position(x+1, y+1, z+1);	MeshChunk->normal(1,0,0); MeshChunk->textureCoord(1, 0);
					MeshChunk->position(x+1, y,   z+1);	MeshChunk->normal(1,0,0); MeshChunk->textureCoord(0, 0);

					MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
					MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

					iVertex += 4;
				}

					//y-1
				Block1 = 0;
				if (y > StartY) Block1 = GetBlock(x,y-1,z);

				if (Block1 == 0)
				{
					MeshChunk->position(x,   y, z);		MeshChunk->normal(0,-1,0); MeshChunk->textureCoord(0, 1);
					MeshChunk->position(x+1, y, z);		MeshChunk->normal(0,-1,0); MeshChunk->textureCoord(1, 1);
					MeshChunk->position(x+1, y, z+1);	MeshChunk->normal(0,-1,0); MeshChunk->textureCoord(1, 0);
					MeshChunk->position(x,   y, z+1);	MeshChunk->normal(0,-1,0); MeshChunk->textureCoord(0, 0);

					MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
					MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

					iVertex += 4;
				}


					//y+1
				Block1 = 0;
				if (y < StartY + CHUNK_SIZE - 1) Block1 = GetBlock(x,y+1,z);

				if (Block1 == 0)
				{
					MeshChunk->position(x,   y+1, z+1);		MeshChunk->normal(0,1,0); MeshChunk->textureCoord(0, 1);
					MeshChunk->position(x+1, y+1, z+1);		MeshChunk->normal(0,1,0); MeshChunk->textureCoord(1, 1);
					MeshChunk->position(x+1, y+1, z);		MeshChunk->normal(0,1,0); MeshChunk->textureCoord(1, 0);
					MeshChunk->position(x,   y+1, z);		MeshChunk->normal(0,1,0); MeshChunk->textureCoord(0, 0);

					MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
					MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

					iVertex += 4;
				}

					//z-1
				Block1 = 0;
				if (z > StartZ) Block1 = GetBlock(x,y,z-1);

				if (Block1 == 0)
				{
					MeshChunk->position(x,   y+1, z);		MeshChunk->normal(0,0,-1); MeshChunk->textureCoord(0, 1);
					MeshChunk->position(x+1, y+1, z);		MeshChunk->normal(0,0,-1); MeshChunk->textureCoord(1, 1);
					MeshChunk->position(x+1, y,   z);		MeshChunk->normal(0,0,-1); MeshChunk->textureCoord(1, 0);
					MeshChunk->position(x,   y,   z);		MeshChunk->normal(0,0,-1); MeshChunk->textureCoord(0, 0);

					MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
					MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

					iVertex += 4;
				}


					//z+1
				Block1 = 0;
				if (z < StartZ + CHUNK_SIZE - 1) Block1 = GetBlock(x,y,z+1);

				if (Block1 == 0)
				{
					MeshChunk->position(x,   y,   z+1);		MeshChunk->normal(0,0,1); MeshChunk->textureCoord(0, 1);
					MeshChunk->position(x+1, y,   z+1);		MeshChunk->normal(0,0,1); MeshChunk->textureCoord(1, 1);
					MeshChunk->position(x+1, y+1, z+1);		MeshChunk->normal(0,0,1); MeshChunk->textureCoord(1, 0);
					MeshChunk->position(x,   y+1, z+1);		MeshChunk->normal(0,0,1); MeshChunk->textureCoord(0, 0);

					MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
					MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

					iVertex += 4;
				}
			}
		}
	}

	MeshChunk->end();
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(MeshChunk);

	++m_ChunkID;
}

Ogre::ManualObject* Application::createCubeMesh(Ogre::String meshName, Ogre::String matName) {
     Ogre::ManualObject* cube = mSceneMgr->createManualObject(meshName);
    cube->begin(matName, Ogre::RenderOperation::OT_TRIANGLE_LIST);


    cube->position(0.5f,-0.5f,1.0f);cube->normal(0.408248f,-0.816497f,0.408248f);cube->textureCoord(1,0);
    cube->position(-0.5f,-0.5f,0.0f);cube->normal(-0.408248f,-0.816497f,-0.408248f);cube->textureCoord(0,1);
    cube->position(0.5f,-0.5f,0.0f);cube->normal(0.666667f,-0.333333f,-0.666667f);cube->textureCoord(1,1);
    cube->position(-0.5f,-0.5f,1.0f);cube->normal(-0.666667f,-0.333333f,0.666667f);cube->textureCoord(0,0);
    cube->position(0.5f,0.5f,1.0f);cube->normal(0.666667f,0.333333f,0.666667f);cube->textureCoord(1,0);
    cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667f,-0.333333f,0.666667f);cube->textureCoord(0,1);
    cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248f);cube->textureCoord(1,1);
    cube->position(-0.5,0.5,1.0);cube->normal(-0.408248,0.816497,0.408248);cube->textureCoord(0,0);
    cube->position(-0.5,0.5,0.0);cube->normal(-0.666667,0.333333,-0.666667);cube->textureCoord(0,1);
    cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(1,1);
    cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(1,0);
    cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(0,1);
    cube->position(0.5,0.5,0.0);cube->normal(0.408248,0.816497,-0.408248);cube->textureCoord(1,1);
    cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(0,0);
    cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(1,0);
    cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(0,0);
    cube->position(-0.5,0.5,1.0);cube->normal(-0.408248,0.816497,0.408248);cube->textureCoord(1,0);
    cube->position(0.5,0.5,0.0);cube->normal(0.408248,0.816497,-0.408248);cube->textureCoord(0,1);
    cube->position(-0.5,0.5,0.0);cube->normal(-0.666667,0.333333,-0.666667);cube->textureCoord(1,1);
    cube->position(0.5,0.5,1.0);cube->normal(0.666667,0.333333,0.666667);cube->textureCoord(0,0);

     cube->triangle(0,1,2);         cube->triangle(3,1,0);
     cube->triangle(4,5,6);         cube->triangle(4,7,5);
     cube->triangle(8,9,10);        cube->triangle(10,7,8);
     cube->triangle(4,11,12);       cube->triangle(4,13,11);
     cube->triangle(14,8,12);       cube->triangle(14,15,8);
     cube->triangle(16,17,18);      cube->triangle(16,19,17);

    cube->end();
    return cube;
    }


//Old shitty method of drawing
void Application::displaySimpleWorld (void) {



    //Create the one box and the supporting class objects
	Ogre::ManualObject* testBox  = createCubeMesh("TestBox1", "DirtMat");
    Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::MeshPtr Mesh = testBox->convertToMesh("TestBox2");
	//Not sure if this is ever free. Meh.
	Ogre::StaticGeometry* pGeom = new Ogre::StaticGeometry (mSceneMgr, "Boxes");
	Ogre::Entity* pEnt = mSceneMgr->createEntity("TestBox2");

	pGeom->setRegionDimensions(Ogre::Vector3(300, 300, 300));


    //Create out solid block world
	for (int z = 0; z < WORLD_SIZE; ++z)
	{
		for (int y = 0; y < WORLD_SIZE; ++y)
		{
			for (int x = 0; x < WORLD_SIZE; ++x)
			{
				if (GetBlock(x,y,z)) pGeom->addEntity(pEnt, Ogre::Vector3(x,y,z));
			}
		}
	}

	pGeom->build ();
}

void Application::createPlayer(void)
{
    // Create an Entity
    Ogre::Entity* ogreHead = mSceneMgr->createEntity("Player", "ogrehead.mesh");

    // Create a SceneNode and attach the Entity to it
    Ogre::SceneNode* playerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode");
    playerNode->attachObject(ogreHead);
    playerNode->scale( .1, .1, .1 );

    Ogre::SceneNode* playerCamNode = playerNode->createChildSceneNode("PlayerCamNode");

    Ogre::Camera* playerCam = mSceneMgr->createCamera("PlayerCam");
    playerCamNode->attachObject(playerCam);
    playerCamNode->translate(Ogre::Vector3(0,0,-400));
    playerCam->lookAt(playerNode->getPosition());
    playerCam->setNearClipDistance(5);
}

void Application::createPlayerCamera(void)
{


}

//-------------------------------------------------------------------------------------
void Application::createScene(void)
{
    // Set the scene's ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));


    createWorldChunks();
    createPlayer();
    //displaySimpleWorld();

    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");

    mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
    light->setPosition(20.0f, 80.0f, 50.0f);
}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Application app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
