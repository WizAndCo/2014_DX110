using namespace std;

#include <ExampleApplication.h>
#include <OgreMovableObject.h>
#include "InputListener.h"

#include <Terrain/OgreTerrain.h>


/** @brief Premiere classe pour la prise en main de Ogre
 * 
 * Voir ci-dessous pour les détails
 * 
 @author Adkoba, Aklal
 @date August 2014
 */
class PremiereApplication : public ExampleApplication
{    
    public:
        Terrain *mTerrain;                      /**<gèrera les propriétés de notre terrain*/
        Ogre::TerrainGlobalOptions *mGlobals;   /**<objet obligatoire pr la gestion des terrains, définira les propriétés générales pour le terrain (ex: éclairage)*/
        Light *mLight;                          /**<contiendra les proriétés de la lumière*/
        
        /** Crée la scène avec une tête d'Ogre flottant sur un carré de pelouse
         */
        void createScene();
        
        /** Crée et place la caméra
         */
        void createCamera();
        
        /** Crée une seconde vue de la scene
         */
        void createViewports();

        /** Gère les entrées 
         */
        void createFrameListener();
        
        /** Crée une lumière selon le paramètre
         @param luxType - type de lumière désirée 
         @param lux - instance de lumière 
         @return distance to point
         */
        //void createLux(std::string luxType, MovableObject *lux);
        
        /** Initialise le terrain
         */
        void createTerrain();
};
