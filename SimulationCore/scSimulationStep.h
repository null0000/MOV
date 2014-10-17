#ifndef SCSIMULATIONSTEP_H
#define SCSIMULATIONSTEP_H

#include "simulationcore_ie.h"
#include "scDefinitions.h"
#include <memory>

class scChunkManager;
class scWorld;

class SIM_IE scSimulationStep {
public:
    virtual ~scSimulationStep(){}
    virtual void runStep(scWorld &world, scChunkManager &manager, delta_t time) = 0;

};

typedef std::shared_ptr<scSimulationStep> scSimulationStep_p;



#endif // SCSIMULATIONSTEP_H
