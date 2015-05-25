#ifndef MASK_DEF
#define MASK_DEF

#include "Type.h"

namespace Mask{
    /**
     *  @brief Initialize mask variables
     */
    void InitMask();

    /**
     *  @brief Setting up the color mask
     *  @param
     *      st: start color
     *      ed: end color
     *      time: passing time (ms)
     */
    void SetMask(Color4f st, Color4f ed, int time);

    /**
     *  @brief Trigger tick event
     *  @param
     *      a: passing time(ms)
     */
    void TickEvent(int a);

    /**
     *  @brief Render the mask
     */
    void Render();

    /**
     *  @brief Check if it is any mask
     */
    bool IsMasking();

    /**
     *  @brief Clear the mask
     */
    void Clear();
};

#endif
