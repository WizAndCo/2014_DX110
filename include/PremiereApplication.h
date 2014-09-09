using namespace std;

#include <ExampleApplication.h>
#include <OgreMovableObject.h>

#include "InputListener.h"

class PremiereApplication : public ExampleApplication
{    
    public:        
        void createScene();
        
        void createCamera();
        
        void createViewports();

        void createFrameListener();
        
        void createLux(std::string, MovableObject *);
};
