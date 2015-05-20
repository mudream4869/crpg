#ifndef INPUTCTRL_DEF
#define INPUTCTRL_DEF

namespace InputCtrl{

    /**
     *  @brief Initialize the InputCtrl's envirnment 
     */
    void Init();
    
    /**
     *  @brief Let the special key be pressed 
     *  @param
     *      key: special key id
     */
    void PressSpecialKey(int key);

    /**
     *  @brief Let the normal key be pressed
     *  @param 
     *      key: key id
     */
    void PressNormalKey(unsigned char key);
    
    /**
     *  @brief Let the special key be freed
     *  @param
     *      key: special key id
     */
    void FreeSpecialKey(int key);

    /**
     *  @brief Let the normal key be freed
     *  @param 
     *      key: normal key id
     */
    void FreeNormalKey(unsigned char key);

    /**
     *  @brief Get the status of special key 
     *  @param 
     *      key: special key id
     *  @return 
     *      the key's press status
     */
    bool IsSpecialKeyPress(int key);

    /**
     *  @brief Get the status of normal key
     *  @param
     *      key: normal key id
     *  @return
     *      the key's press status
     */
    bool IsNormalKeyPress(unsigned char key);
    
    /**
     *  @return
     *      Left? Right? Up? Down? 
     */
    int GetDirCommand();
};

#endif
