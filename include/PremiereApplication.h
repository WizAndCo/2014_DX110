using namespace std;

#include <ExampleApplication.h>
#include <OgreMovableObject.h>

//#include <Overlay/OgreTextAreaOverlayElement.h>
//#include <Overlay/OgreFontManager.h>

#include "InputListener.h"



class PremiereApplication : public ExampleApplication
{
    public:
        void createScene();
        void createCamera();
        void createViewports();

        void createFrameListener();
        
        void createLux(std::string, MovableObject *);
        
        //InputListener *mFrameListener;
};
