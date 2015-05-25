#ifndef GLOBAL_VARIABLE_DEF
#define GLOBAL_VARIABLE_DEF

#include <vector>
#include <utility>
#include <string>


namespace GlobalVariable{

    /**
     *  @brief Initialize the GlobalVariable envirnment
     */
    void InitGlobalVariable();

    /**
     *  @brief Get value by its name
     *  @param
     *      name: value's name
     *  @return 
     *      value's value
     */
    int GetValue(std::string name);

    /**
     *  @brief Set value by its name
     *  @param 
     *      name: value's name
     *      a: value's value
     */
    void SetValue(std::string name, int a);

    /**
     *  @brief Dump value's name -> value Map
     *  @return 
     *      [(value name, value)]
     */
    std::vector< std::pair< std::string, int> > DumpValues();

    /**
     *  @brief Erase all value
     */
    void ClearValue();
    
    /**
     *  @brief Get the flag by its name
     *  @param 
     *      name: flag's name
     *  @return 
     *      flag's value
     */
    bool GetFlag(std::string name);
    
    /**
     *  @brief Set the flag by its name
     *  @param 
     *      name: flag's name
     *      a: flag's value
     */
    void SetFlag(std::string name, bool a);

    /**
     *  @brief Dump flag's name -> value Map
     *  @return 
     *      [(flag name, value)]
     */
    std::vector< std::pair< std::string, bool> > DumpFlags();

    /**
     *  @brief Erase all flag
     */
    void ClearFlag();
};

#endif
