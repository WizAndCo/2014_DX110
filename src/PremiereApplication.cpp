#include "PremiereApplication.h"


/**
 * createFrameListener: creation des frames listener pour la prise en compte des entrees utilisateurs
 */
void PremiereApplication::createFrameListener()
{
    //activation du buffer pour la souris et le clavier
    mFrameListener = new InputListener(mWindow, mCamera, mSceneMgr, true, true, true);
    
    //root est l'élément de base de l'application Ogre qui s'occupe notamment de gérer les frames listeners
    mRoot -> addFrameListener(mFrameListener);
}

/**
 * createScene: creation de la scene avec une tete d'ogre flottant au-dessus d'un carre de pelouse
 */
void PremiereApplication::createScene()
{
    createTerrain();
}









void PremiereApplication::createTerrain()
{
    
    Ogre::Vector3 lightdir(0.55f, -0.3f, 0.75f);
    
    mLight = mSceneMgr->createLight("terrainLight");
    mLight->setType(Light::LT_DIRECTIONAL);
    mLight->setDirection(lightdir);
    mLight->setDiffuseColour(Ogre::ColourValue::White);
    mLight->setSpecularColour(Ogre::ColourValue(0.4f, 0.4f, 0.4f)); 
    
    mGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
    mGlobals->setMaxPixelError(8);                                      /**<spécifie la précision de rendu (en nbr de pixel) du terrain*/    
    
    //application des réglages de lumière aux options globales
    mGlobals->setLightMapDirection(mLight->getDerivedDirection());
    mGlobals->setCompositeMapDistance(3000);
    mGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
    mGlobals->setCompositeMapDiffuse(mLight->getDiffuseColour());
    
    
    mTerrain = OGRE_NEW Ogre::Terrain(mSceneMgr);/**<Création du terrain*/
    
    Ogre::Image img;
    img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);/**<Chargement de l'image Heighmaps contenant les infos pour le relief*/
    
    ///Mise en place des propriétés générales du terrain
    Ogre::Terrain::ImportData imp;/**<Création de l'objet qui contiendra toutes les infos pour le terrain*/
    imp.inputImage = &img;/**<recuperation de l image*/
    imp.terrainSize = img.getWidth();/**<recuperation de la taille de l image (les terrains sont carres, l'image doit donc etre carree)*/

    imp.worldSize = 8000;/**<taille du terrain en unites de la scene (plus ce nbre est grande, plus l'image est grande)*/
    imp.inputScale = 600;/**<echelle adoptee pour l altitude du terrain (difference entre un pt a l'altitude 0 (pt en blanc ds terrain.png) et un point à l'altitude max (pt en noir))*/
    imp.minBatchSize = 33;/**<taille min du batch pour le terrain*/
    imp.maxBatchSize = 65;/**<taille max du batch pour le terrain*/
    
    ///Mise en place des textures
    imp.layerList.resize(1);/**<donne la taille de la liste des calques*/
    imp.layerList[0].worldSize = 100;/**<donne la taille de la texture ds le monde (plus le nbre est gd plus la texture est zoomée)*/
    ///insertion de textures dans notre calque
    imp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds");/**>contient les couleurs, les motifs du materiau*/
    imp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds");/**<contient des infos sur le relief du materiau*/
    
    ///Filtrage anisotropique (affecte toutes les textures)
    Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
    Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(8);
    
    
    
    
    
    
    ///Rajout de calques dans notre liste
    imp.layerList.resize(3);
    imp.layerList[0].worldSize = 100;
    imp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds");
    imp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds");
    imp.layerList[1].worldSize = 30;
    imp.layerList[1].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
    imp.layerList[1].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
    imp.layerList[2].worldSize = 200;
    imp.layerList[2].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    imp.layerList[2].textureNames.push_back("dirt_grayrocky_normalheight.dds");
    
    mTerrain->prepare(imp);/**<on fournit toutes les informations necessaires au terrain*/
    mTerrain->load();/**<chragement du terrain*/    
    
    
    
    
    ///pour definir des bandes d'altitude avec une texture différente
    Ogre::Real minHeight1 = 70;
    Ogre::Real fadeDist1 = 40;
    Ogre::Real minHeight2 = 70;
    Ogre::Real fadeDist2 = 15;
    
    
    ///recuperation du blend map pour le premier terrain
    Ogre::TerrainLayerBlendMap* blendMap1 = mTerrain->getLayerBlendMap(1);/**<recuperation du blend map*/
    Ogre::TerrainLayerBlendMap* blendMap2 = mTerrain->getLayerBlendMap(2);/**<recuperation du blend map*/
    
    ///plaquage de la texture..
    float* pBlend1 = blendMap1->getBlendPointer();
    float* pBlend2 = blendMap2->getBlendPointer();
    ///..en fonction de l'altitude
    for (Ogre::uint16 y = 0; y < mTerrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < mTerrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real terrainX, terrainY, transparence;
            
            blendMap1->convertImageToTerrainSpace(x, y, &terrainX, &terrainY);
            Ogre::Real height = mTerrain->getHeightAtTerrainPosition(terrainX, terrainY);
            
            transparence = (height - minHeight1) / fadeDist1;
            transparence = Ogre::Math::Clamp(transparence, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = transparence * 255;
            
            transparence = (height - minHeight2) / fadeDist2;
            transparence = Ogre::Math::Clamp(transparence, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend2++ = transparence * 255;
        }
    }
    
    blendMap1->dirty();/**<precise que les donnees de la blend Map st obsolètes*/
    blendMap1->update();/**<fait la mise a jour des donnees de la blend map*/
    blendMap2->dirty();/**<precise que les donnees de la blend Map st obsolètes*/
    blendMap2->update();/**<fait la mise a jour des donnees de la blend map*/ 
    
    mTerrain->freeTemporaryResources();/**<liberation de la memoire allouee temporairement*/
}


/**
 * createCamera: definit la position de notre point de vue
 */
void PremiereApplication::createCamera()
{
    //creation de la camera
    mCamera = mSceneMgr->createCamera("Ma Camera");

    //position de la camera
    mCamera->setPosition(Vector3(-100.0, 150.0, 200.0));    
    mCamera->setPosition(-100, 500, 200);

    //permet de determiner le point de la scene que regarde notre camera
    mCamera->lookAt(Vector3(0.0, 100.0, 0.0));

    //definition des distances de near clip et de far clip, qui
    //sont les distances minimale et maximale auxquelles doit se
    //trouver un objet pour être affichr à l'écran.
    mCamera->setNearClipDistance(1);
    mCamera->setFarClipDistance(20000);

    if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE)){
        mCamera->setFarClipDistance(0);
    }
}

/**
 * createViewports: creation d'un second viewport
 */
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
    mCamera->setAspectRatio(Real(vue->getActualWidth()) / Real(vue->getActualHeight()));

    //on definit ici la couleur de fond
    vue->setBackgroundColour(ColourValue(0.0, 0.0, 1.0));     //bleu
    //vue->setBackgroundColour(ColourValue(0.980, 0.502, 0.447)); //saumon

   // creation d'un viewport dans le coin bas gauche
   //les parametres autres que le premier sont obligatoires pour la definition
   //de plusieurs viewport
   Viewport* vue2 = mWindow->addViewport(mCamera, 1, 0, 0.8, 0.2, 0.2);
   vue2->setBackgroundColour(ColourValue(0.561, 0.737, 0.561 ));  //darkseagreen
}

