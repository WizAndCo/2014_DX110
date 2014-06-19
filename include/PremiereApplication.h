using namespace std;

#include <ExampleApplication.h>
#include <OgreMovableObject.h>



class PremiereApplication : public ExampleApplication
{
    public:
        void createScene();
        void createCamera();
        void createViewports();

        void createLux(std::string, MovableObject *);
};
