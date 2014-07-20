#include <OIS/OIS.h>
#include "InputListener.h"



InputListener::InputListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr,
                                bool bufferedKeys, bool bufferedMouse, bool bufferedJoy) 
    : ExampleFrameListener(win, cam, bufferedKeys, bufferedMouse, bufferedJoy)

    {
        mCamera = cam;
        mSceneMgr = sceneMgr;
        mVitesse = 100;
        mVitesseRotation = 0.3;
        mToucheAppuyee = false;
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
   
   
   if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
       mContinuer = false;
   }
   else{
       mContinuer= true;
   }
   
   Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;
   mMouvement = mVitesse * evt.timeSinceLastFrame;
   
   
    // La touche A d’un clavier QWERTY correspond au Q sur un AZERTY
    if ( mKeyboard->isKeyDown(OIS::KC_LEFT) || mKeyboard->isKeyDown(OIS::KC_A) ){
        deplacement.x -= mMouvement;
    }
    
    if ( mKeyboard->isKeyDown(OIS::KC_RIGHT) || mKeyboard->isKeyDown(OIS::KC_D) ){
        deplacement.x += mMouvement;
    }
    

    // W correspond au Z du AZERTY
    if ( mKeyboard->isKeyDown(OIS::KC_UP) || mKeyboard->isKeyDown(OIS::KC_W)){
        deplacement.z -= mMouvement;
    }
    
    if ( mKeyboard->isKeyDown(OIS::KC_DOWN) || mKeyboard->isKeyDown(OIS::KC_S)){
        deplacement.z += mMouvement;
    }
    
    //*
    const OIS::MouseState &mouseState = mMouse->getMouseState();
    mRotationX = Degree(-mouseState.Y.rel * mVitesseRotation);
    mRotationY = Degree(-mouseState.X.rel * mVitesseRotation);
    
    //pour que la camera bouge selon les touches pressees et le mouvement de la souris
    //mCamera->yaw(mRotationY);
    //mCamera->pitch(mRotationX);        
    //mCamera->moveRelative(deplacement);
    
    //pour que le noeud "nodeTete" bouge selon les touches pressees et le mouvement de la souris
    mSceneMgr->getSceneNode("nodeTete")->yaw(mRotationY);
    mSceneMgr->getSceneNode("nodeTete")->pitch(mRotationX);
    mSceneMgr->getSceneNode("nodeTete")->translate(deplacement, Ogre::Node::TS_LOCAL);
    
    return mContinuer;
}