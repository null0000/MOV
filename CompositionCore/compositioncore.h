#ifndef COMPOSITIONCORE_H
#define COMPOSITIONCORE_H

#include "compositioncore_ie.h"

#include <scKeyboardInput.h>
#include <coWorld.h>

CMP_IE coWorld_p coBootUp(scInputDevice_p inputDevice, QRect CameraBounds, QRect windowDim);

#endif // COMPOSITIONCORE_H
