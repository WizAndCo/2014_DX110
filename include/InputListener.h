#include "ExampleFrameListener.h"

//nous utiliserons OIS pour gérer les entrées de l'utilisateur
#include <OIS/OIS.h>

//la classe ExampleFrameListener ExampleApplication met déjà en oeuvre une gestion des entrées eet attend un ExampleFrameListener
//ExampleFrameListener s'occupe aussi de construire les objets nécessaires à l'écoute des entrées
class InputListener : public ExampleFrameListener
{
    public:
        InputListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr, 
                        bool bufferedKeys = false, bool bufferedMouse = false, 
                        bool bufferedJoy = false);
        
        //nous allons juste devoir redefinir frameRenderingQueued() pour implementer notre propre gestion des entrees a la place de celle prevue par ExampleFrameListener.
        virtual bool frameRenderingQueued(const FrameEvent& evt);

        private:
            Ogre::SceneManager *mSceneMgr;
            Ogre::Camera *mCamera;
            
            bool mContinuer;
            bool mToucheAppuyee;

            Ogre::Real mMouvement;
            Ogre::Real mVitesse;
            Ogre::Real mVitesseRotation;

            Ogre::Radian mRotationX;
            Ogre::Radian mRotationY;
};
