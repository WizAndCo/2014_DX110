#include "PremiereApplication.h"

void PremiereApplication::createScene()
{
    //creation d une entite
    Entity *head= mSceneMgr->createEntity("Tete", "ogrehead.mesh" );
    
    //creation d un noeud
    SceneNode *node= mSceneMgr->getRootSceneNode( )->createChildSceneNode( "nodeTete " , Vector3::ZERO, Quaternion::IDENTITY);
    
    node->yaw(Radian(Math::PI));
    node->yaw(Radian(Math::PI));

    Vector3 position = Vector3(30.0, 50.0, 0.0);
    node->setPosition(position);

    node->setPosition(30.0, 50.0, 0.0); 
    node->translate(-30.0, 50.0, 0.0); 
    
    
    //attachement de l entite au noeud
    node->attachObject ( head );

    Plane plan(Vector3::UNIT_Y, 0) ;
    MeshManager::getSingleton().createPlane("sol",
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                plan, 500, 500, 1, 1, true, 1, 1, 1, Vector3::UNIT_Z); 

    Entity *ent= mSceneMgr->createEntity("EntiteSol", "sol");
    ent->setMaterialName("Examples/GrassFloor");
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);


}

