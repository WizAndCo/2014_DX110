#include "ExampleFrameListener.h"

//nous utiliserons OIS pour gérer les entrées de l'utilisateur
#include <OIS/OIS.h>

//la classe ExampleFrameListener ExampleApplication met déjà en oeuvre une gestion des entrées eet attend un ExampleFrameListener
//ExampleFrameListener s'occupe aussi de construire les objets nécessaires à l'écoute des entrées
class InputListener : public ExampleFrameListener, OIS::KeyListener, OIS::MouseListener
{
    public:
        InputListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr, 
                        bool bufferedKeys = false, bool bufferedMouse = false, 
                        bool bufferedJoy = false);
        
        //nous allons juste devoir redefinir frameRenderingQueued() pour implementer notre propre gestion des entrees a la place de celle prevue par ExampleFrameListener.
        virtual bool frameRenderingQueued(const FrameEvent& evt);
        
        //les 5 methodes suivantes sont des methodes virtuelles pures a reimplementer
        //ces methodes seront appelees lors de levenmnt correspondant, leur valeur de retour ne dit pas si on doit continuer ou pas, d'ou l'interet de mContinuer
        bool mouseMoved(const OIS::MouseEvent &e);      //evenmnt: la souris a bouge
        bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);//evenmnt: un bouton de la souris a ete presse
        bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);//evenmnt: un bouton de la souris a ete relache 
        bool keyPressed(const OIS::KeyEvent &e);//evenmnt: un bouton a ete presse 
        bool keyReleased(const OIS::KeyEvent &e);//evenmnt: un bouton a ete relache 
        

        private:
            Ogre::SceneManager *mSceneMgr;
            Ogre::Camera *mCamera;
            
            //permettra d'enregistrer l'appuie sur ECHAP
            bool mContinuer;

            //vecteur de la direction ds lqll on doit bouger
            Ogre::Vector3 mMouvement;
            Ogre::Real mVitesse;
            
            //pour ajuster la vitesse de rotation de la souris
            Ogre::Real mVitesseRotation;

            Ogre::Radian mRotationX;
            Ogre::Radian mRotationY;
};
