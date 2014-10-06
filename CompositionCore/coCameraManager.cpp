

#include "coCameraManager.h"
#include "scWorld.h"
#include "gcRenderList.h"

coCameraManager::coCameraManager(scWorld_p world, QRect CameraBounds, QRect WorldBounds) :
    camera(coCameraBox<scLocationFunctor>(scLocationFunctor(world), CameraBounds, WorldBounds))
{}

coCameraManager::coCameraManager(scWorld_p world, scWorld::t_tag Target, QRect CameraBounds, QRect WorldBounds) :
    camera(coCameraBox<scLocationFunctor>(scLocationFunctor(Target, world), CameraBounds, WorldBounds)){}

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
    camera.offsetFunctor().viewingWindowBounds(bounds);
}



void coCameraManager::update(delta_t ) {
    camera.offsetFunctor().update();
}

QVector2D coCameraManager::curOffset () const {
    return camera.offsetFunctor()();
}
