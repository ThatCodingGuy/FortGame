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

class Application : public BaseApplication
{
public:
    Application(void);
    virtual ~Application(void);
    Ogre::ManualObject* createCubeMesh(Ogre::String meshName, Ogre::String matName);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __TutorialApplication_h_
