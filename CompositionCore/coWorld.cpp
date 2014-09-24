


#include "coWorld.h"


void coWorld::registerSimulationStep(scSimulationStep_p newStep) {
    world->registerSimulationStep(newStep);
}

void coWorld::simulate(delta_t time) {
    camera.update(time);
    world->simulate(time);
}


void coWorld::draw (gcDrawingImpl &impl) {
    camera.draw(impl);
}

void coWorld::cameraBounds(QRect bounds) {
    camera.bounds(bounds);
}

void coWorld::setTarget(t_simtag target) {
    camera.setTarget(world, target);
}
