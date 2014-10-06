

#include "coCameraManager.h"
#include "scWorld.h"
#include "gcRenderList.h"

coCameraManager::coCameraManager(scWorld_p world) :
    camera(coCameraBox<scLocationFunctor>(scLocationFunctor(world)))
{}

coCameraManager::coCameraManager(scWorld_p world, scWorld::t_tag Target) :
    camera(coCameraBox<scLocationFunctor>(scLocationFunctor(Target, world))){}

void coCameraManager::setTarget(scWorld_p world, scWorld::t_tag targetTag) {
    getConfigurableLocation().setObject(world, targetTag);
}

void coCameraManager::setTarget(scWorld::t_tag targetTag) {
    getConfigurableLocation().setObject(targetTag);
}

void coCameraManager::draw(gcDrawingImpl &impl) const {
    camera.draw(impl);
}


void coCameraManager::pushRenderable(const gcRenderable *newRenderable) {
    camera.pushRenderable(newRenderable);
}


void coCameraManager::bounds(QRect bounds) {
    camera.offsetFunctor().bounds(bounds);
}



void coCameraManager::update(delta_t ) {
    camera.offsetFunctor().update();
}

QVector2D coCameraManager::curOffset () const {
    return camera.offsetFunctor()();
}
