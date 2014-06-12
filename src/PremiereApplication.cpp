#include "PremiereApplication.h"

void PremiereApplication::createScene()
{
    //creation d une entite
    Entity *head= mSceneMgr->createEntity("Tete", "ogrehead.mesh" );
    
    //creation d un noeud
    SceneNode *node= mSceneMgr->getRootSceneNode( )->createChildSceneNode( "nodeTete " , Vector3::ZERO, Quaternion::IDENTITY);
    
    node->yaw(Radian(Math::PI));
    node->yaw(Radian(Math::PI));

    //setPosition place le noeud aux coord passees en parametres
    Vector3 position = Vector3(30.0, 50.0, 0.0);
    node->setPosition(position);

    node->setPosition(30.0, 50.0, 0.0); 
    /*equivalent a
    Vector3 position = Vector3(30.0, 50.0, 0.0);
    node->setPosition(position);
    */

    //deplace le noeud par rapport a sa position actuelle
    node->translate(-30.0, 50.0, 0.0); //par defaut la trnslt se fait par rap a TS_WORLD
   
    //attachement de l entite au noeud
    node->attachObject ( head );

    //creation d un plan
    Plane plan(Vector3::UNIT_Y, 0);

    //creation d un mesh cad l objet 3d visible ds la scene
    MeshManager::getSingleton().createPlane("sol",
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                plan, 500, 500, 1, 1, true, 1, 1, 1, Vector3::UNIT_Z); 

    //entite qui representera le plan
    Entity *ent= mSceneMgr->createEntity("EntiteSol", "sol");

    //ajout du materiau a l entite
    ent->setMaterialName("Examples/GrassFloor");//texture de pelouse
    /*les differents materiaux sont sous /media/materials/scritps, par ex:
    ent->setMaterialName("Examples/WaterStream");//texture d eau animee*/

    //creation d un noeud
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
}

/*definit la position de notre point de vue*/
void PremiereApplication::createCamera()
{
    //creation de la camera
    mCamera = mSceneMgr->createCamera("Ma Camera");

    //position de la camera
    mCamera->setPosition(Vector3(-100.0, 150.0, 200.0));

    //permet de determiner le point de la scene que regarde notre camera
    mCamera->lookAt(Vector3(0.0, 100.0, 0.0));

    //definition des distances de near clip et de far clip, qui
    //sont les distances minimale et maximale auxquelles doit se
    //trouver un objet pour être affichr à l'écran.
    mCamera->setNearClipDistance(1);
    mCamera->setFarClipDistance(1000);
}


