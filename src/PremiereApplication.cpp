#include "PremiereApplication.h"



void PremiereApplication::createFrameListener()
{
    //activation du buffer pour la souris et le clavier
    mFrameListener = new InputListener(mWindow, mCamera, mSceneMgr, true, true, true);
    
    //root est l'élément de base de l'application Ogre qui s'occupe notamment de gérer les frames listeners
    mRoot -> addFrameListener(mFrameListener);
}


void PremiereApplication::createScene()
{
    //creation d une entite
    Entity *head= mSceneMgr->createEntity("Tete", "ogrehead.mesh" );
    
    //creation d un noeud
    SceneNode *node= mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeTete" , Vector3::ZERO, Quaternion::IDENTITY);
    
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
    node->attachObject(head);

    //creation d un plan
    Plane plan(Vector3::UNIT_Y, 0);

    //creation d un mesh cad l objet 3d visible ds la scene
    MeshManager::getSingleton().createPlane("sol",
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                plan, 500, 500, 10, 10, true, 1, 1, 1, Vector3::UNIT_Z); 

    //entite qui representera le plan
    Entity *ent= mSceneMgr->createEntity("EntiteSol", "sol");

    //ajout du materiau a l entite
    ent->setMaterialName("Examples/GrassFloor");//texture de pelouse
    /*les differents materiaux sont sous /media/materials/scritps, par ex:
    ent->setMaterialName("Examples/WaterStream");//texture d eau animee*/

    //creation d un noeud
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);

    createLux("ponctuelle", head);//lumiere ponctuelle
    //createLux("directionnelle", head);//lumiere directionnelle
    //createLux("spot", head);//lumiere projecteur

}

/*
cree une lumiere selon le parametre passe:
    createLux("ponctuelle"); -> lumiere ponctuelle
    createLux("directionnelle"); -> lumiere directionnelle
    createLux("spot"); -> lumiere projecteur

une lumiere noire est cree au debut de la methode

une ombre est cree en fin de methode
*/
void PremiereApplication::createLux(std::string prmLightType, MovableObject * prmEnt)
{
    //application d une couleur noire
    mSceneMgr->setAmbientLight(ColourValue(0.0, 0.0, 0.0)); 

    //definition d une lumiere 
    Light *light= mSceneMgr->createLight("lumiere1");

    if (prmLightType == "ponctuelle")
    {
        //definition du type de lumiere
        light->setType(Light::LT_POINT);//lumiere ponctuelle

        //definition de la position de la lumiere
        light->setPosition(-100, 200, 100);
    }
    else if (prmLightType == "directionnelle")
    {
        light->setType(Light::LT_DIRECTIONAL);//lumiere directionnelle
        light->setDirection(10.0, -20.0, -5);//vecteur directeur de la lumiere directionnelle

        //definition de la position de la lumiere
        light->setPosition(-100, 200, 100);
    }
    else
    {
        light->setType(Light::LT_SPOTLIGHT);//lumiere directionnelle
        light->setDirection(0.0, -1, 1);//vecteur directeur de la lumiere directionnelle
        light->setSpotlightRange(Degree(30), Degree(60), 1.0);
    }

    //definition des couleur des lumieres diffuse
    light->setDiffuseColour(1.0, 0.7, 0.1);
    //et speculaire
    light->setSpecularColour(1.0, 0.7, 0.1);

    //ombre
    //activation de la projection des ombres
    light->setCastShadows(true);
    prmEnt->setCastShadows(true);

    //activation des ombres
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
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

void PremiereApplication::createViewports()
{
    //la creation du Viewport, appelee par la fenetre et prenant en parametre la
    //camera concernee, le premier parametre est la camera de laqll le contenu
    //du viewport sera rendu, ce paramatre est le seul obligatoire
    Viewport *vue = mWindow->addViewport(mCamera);
    //Viewport *vue = mWindow->addViewport(mCamera, 0, 0, 0, 0.8, 0.8);

    //Grace a ce Viewport nouvellement cree, nous allons faire coincider
    //le rapport largeur / hauteur de notre camera avec celui du
    //Viewport, pour avoir une image non deformee
    mCamera->setAspectRatio(Real(vue->getActualWidth()) /  Real(vue->getActualHeight()));

    //on definit ici la couleur de fond
    vue->setBackgroundColour(ColourValue(0.0, 0.0, 1.0));     //bleu
    //vue->setBackgroundColour(ColourValue(0.980, 0.502, 0.447)); //saumon

   // creation d'un viewport dans le coin bas gauche
   //les parametres autres que le premier sont obligatoires pour la definition
   //de plusieurs viewport
   Viewport* vue2 = mWindow->addViewport(mCamera, 1, 0, 0.8, 0.2, 0.2);
   vue2->setBackgroundColour(ColourValue(0.561, 0.737, 0.561 ));  //darkseagreen
}

