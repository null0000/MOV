#ifndef SCCHUNKGENERATOR_H
#define SCCHUNKGENERATOR_H

#include "scSimulationStep.h"
#include "scDefinitions.h"
#include "scChunkManager.h"

#include "simulationcore_ie.h"

#include <glbDefinitions.h>



template <typename location_f>
class scChunkGenerator : public scSimulationStep {
public:
    void runStep(scWorld &, scChunkManager &manager, delta_t) {
        manager.genChunks(loc(), r);
    }


    scChunkGenerator(location_f loc, measure_type r):
        loc(loc), r(r){}

private:
    location_f loc;
    measure_type r;
};

#endif // SCCHUNKGENERATOR_H
