#ifndef PYLOCK_DEF
#define PYLOCK_DEF

#include <mutex>
void PyLock();
void PyUnlock();
std::mutex& PyGetMutex();

#endif
