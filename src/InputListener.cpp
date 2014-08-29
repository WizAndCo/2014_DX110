#include <OIS/OIS.h>
#include "InputListener.h"



InputListener::InputListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr,
                                bool bufferedKeys, bool bufferedMouse, bool bufferedJoy) 
    : ExampleFrameListener(win, cam, bufferedKeys, bufferedMouse, bufferedJoy)
    {
        mCamera = cam;
        mSceneMgr = sceneMgr;
        
        mContinuer = true;//permettra l enregistrmnt de l appuie sur ECHAP
        mMouvement = Ogre::Vector3::ZERO;//sera le vct de la direection ds laqll on doit se deplacer
        
        mVitesse = 100;
        mVitesseRotation = 0.3;//fcteur multiplicatif pour ajuster la rotation de la camera
       
        //enregistrement d un ecouteur pour la souris et pour le clavier
        mMouse->setEventCallback(this);
        mKeyboard->setEventCallback(this);
    }



bool InputListener::frameRenderingQueued(const FrameEvent& evt)
{
    //ces lignes permettent la mise à jour de nos objets pour obtenir le nom des touches enfoncées
   if(mMouse){
       mMouse->capture();
   }
   if(mKeyboard){
       mKeyboard->capture();
   }
   
   //gestion du mouvement de la camera
   Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;
   deplacement = mMouvement * mVitesse * evt.timeSinceLastFrame;
   mCamera->moveRelative(deplacement);
    
   return mContinuer;
}



//les 5 methodes suivantes sont des methodes virtuelles pures a reimplementer
//si la souris a bouge
bool InputListener::mouseMoved(const OIS::MouseEvent &e)
{    
    mCamera->yaw(Ogre::Degree(-mVitesseRotation * e.state.X.rel));
    mCamera->pitch(Ogre::Degree(-mVitesseRotation * e.state.Y.rel));
    
    return true;
}

//si une touche de la souris est pressee
bool InputListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
    return true;
}

//si une touche de la souris est relachee 
bool InputListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
    return true;
}

//si une touche est pressee
bool InputListener::keyPressed(const OIS::KeyEvent &e)
{
    switch(e.key)
    {
        case OIS::KC_ESCAPE:
            mContinuer = false;
            break;
        case OIS::KC_W:
            mMouvement.z -= 1;
            break;
        case OIS::KC_S:
            mMouvement.z += 1;
            break;
        case OIS::KC_A:
            mMouvement.x -= 1;
            break;
        case OIS::KC_D:
            mMouvement.x += 1;
            break;
        case OIS::KC_LSHIFT:
            mVitesse *= 2;
            break;

        //without this switch default statement g++ raises a warning because all values
        //for OIS enumeration are not handled
        default:
            break;
    }
    
    return true;
}

//si une touche est relachee
bool InputListener::keyReleased(const OIS::KeyEvent &e)
{
    
    switch(e.key)
    {
        case OIS::KC_W:
            mMouvement.z += 1;
            break;
        case OIS::KC_S:
            mMouvement.z -= 1;
            break;
        case OIS::KC_A:
            mMouvement.x += 1;
            break;
        case OIS::KC_D:
            mMouvement.x -= 1;
            break;
        case OIS::KC_LSHIFT:
            mVitesse /= 2;
            break;

        //without this switch default statement g++ raises a warning because all values
        //for the OIS enumeration are not handled
        default:
            break;
    } 
    
    return true;
}
