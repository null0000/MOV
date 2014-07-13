#ifndef COMPOSITIONCORE_H
#define COMPOSITIONCORE_H

#include "compositioncore_ie.h"

#include <simulationcore.h>
#include <QVector2D>
#include <QScopedPointer>
#include <gcRenderTransform.h>
#include <gcRenderList.h>

CMP_IE void coBootUp(scWorld_p world, gcRenderList_p list, scInputDevice_p inputDevice);

#endif // COMPOSITIONCORE_H
