#ifndef SIMULATIONCORE_H
#define SIMULATIONCORE_H

#include <QtGlobal>
#include "GraphicsCore.h"

class scSimulatable
{
public:
    void Simulate(qreal timeDelta) = 0;
};


class scGameObject : public scSimulatable, public gcRenderable{};


#endif // SIMULATIONCORE_H
