#ifndef GAMEOBJECTDATA_DEF
#define GAMEOBJECTDATA_DEF

#include <vector>
#include <utility>
#include <string>

#include "Image.h"

namespace GameObjectData{

    /**
     *  @brief Read GameObject from game config
     */
    void InitGameObject();

    /**
     *  @brief Get the amount of GameObect by its name
     *  @param
     *      str: gameobject's name
     *  @return
     *      the amount of gameobject
     */
    int GetGameObjectCount(std::string str);

    /**
     *  @brief Get the image of GameObject by its name
     *  @param 
     *      str: gameobject's name
     *  @return
     *      the Image of GameObject
     */
    Image* GetGameObjectImage(std::string str);

    /**
     *  @brief Call the GameObject's Trigger function
     *  @param
     *      str: gameobject's name
     */
    void CallGameObject(std::string str); 

    /**
     *  @brief Set the GameObject's amount by its name
     *  @param
     *      str: gameobject's name
     *      val: amount of the gameobject
     */
    void SetGameObjectCount(std::string str, int val);
    
    /**
     *  @return
     *      the size of gameobjects
     */
    int GetSize();
    
    /**
     *  @brief Clear all gameobject counting
     */
    void ClearGameObject();
    
    /**
     *  @brief Dump the gameobject -> amount Map
     *  @return
     *      [(gameobject name, amount)]
     */
    std::vector< std::pair< std::string, int> > DumpCounts();
};

#endif
