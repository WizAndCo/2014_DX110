project(helloworld)
 #~project(Premiere Application - Insertion entite)
cmake_minimum_required(VERSION 2.6)

# ~ set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/")
set(CMAKE_MODULE_PATH "/usr/share/OGRE/cmake/modules")

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g")

# Il s'agit du tutoriel d'exemple, qui utilise quelques fichiers prdfini de Ogre. Il faut indiquer  cmake o se trouvent les includes en question
# ~ include_directories ("/usr/share/OGRE/Samples/Common/include/")
#include_directories ("/home/adkoba/Workspace/ogre_src_v1-8-1/Samples/Common/include")
include_directories ("include")

# Bien sur, pour compiler Ogre, il faut le chercher, et dfinir le rpertoire contenant les includes.
find_package(OGRE REQUIRED)
include_directories (${OGRE_INCLUDE_DIRS})

if (OGRE_Overlay_FOUND)
# pretty sure the following include is unneeded
# append OgreOverlay to the end of the OGRE_LIBRARIES variable
  set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Overlay_LIBRARIES})
  message(STATUS "Found OGRE_Terrain: ${OGRE_Overlay_LIBRARIES}")
else (OGRE_Overlay_FOUND)
  message(SEND_ERROR "OgreOverlay Library not found.")
endif(OGRE_Overlay_FOUND)


# L'exemple dpend aussi de OIS, une lib pour grer la souris, clavier, joystick...
find_package(OIS REQUIRED)

# On dfinit les sources qu'on veut compiler
SET( SOURCES
  src/InputListener.cpp  
  src/PremiereApplication.cpp
  src/main.cpp
)

# On les compile
add_executable (
  premiereapp ${SOURCES}
)

message(STATUS "OGRE Libraries used to link are ${OGRE_LIBRARIES}")

# Et pour finir, on lie l'excutable avec les librairies que find_package nous a gentillement trouve.
target_link_libraries(premiereapp ${OGRE_LIBRARIES} ${OIS_LIBRARY} -lboost_system)



set( RESOURCES_FILE
  media/
  resources/ogre.cfg
  resources/plugins.cfg
  resources/resources.cfg
)

# do the copying
foreach( file_i ${RESOURCES_FILE})
    add_custom_command(
      TARGET premiereapp
      POST_BUILD
      COMMAND cp -R ${CMAKE_SOURCE_DIR}/${file_i} ${CMAKE_BINARY_DIR}
      COMMENT "copy file ${file_i}"
      )
endforeach( file_i )
