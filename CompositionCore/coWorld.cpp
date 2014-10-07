


#include "coWorld.h"

const coWorld::t_dbgStrTag &coWorld::NULL_DBGSTR_TAG = gcTextList::NULL_TAG;
const coWorld::t_simtag &coWorld::NULL_SIM_TAG = scWorld::NULL_TAG;

void coWorld::registerSimulationStep(scSimulationStep_p newStep) {
    world->registerSimulationStep(newStep);
}

void coWorld::simulate(delta_t time) {
    camera.update(time);
    world->simulate(time);
}


void coWorld::draw (gcDrawingImpl &impl) {
    drawUntracked(impl);
    camera.draw(impl);
#ifdef QT_DEBUG
    debugText.draw(impl);
#endif
}

void coWorld::cameraBounds(QRect bounds) {
    camera.bounds(bounds);
}

void coWorld::setTarget(t_simtag target) {
    Q_ASSERT(target != NULL_SIM_TAG);
    if (target == NULL_SIM_TAG)
        return;
    camera.setTarget(world, target);
}

#ifdef QT_DEBUG
coWorld::t_dbgStrTag coWorld::addDebugText(glbStringCallback_p Callback) {
    return debugText.pushText(Callback);
}

void coWorld::removeDebugText(t_dbgStrTag rmTag) {
    Q_ASSERT(rmTag != NULL_DBGSTR_TAG);
    if (rmTag != NULL_DBGSTR_TAG)
        debugText.removeText(rmTag);
}

void coWorld::clearDebugText() {
    debugText.clearText();
}
#else

coWorld::t_dbgStrTag coWorld::addDebugText(glbStringCallback_p Callback){return t_dbgStrTag();}
void coWorld::removeDebugText(t_dbgStrTag rmTag){}
void coWorld::clearDebugText(){}
#endif




scWorld_cp coWorld::getWorld() const {
    return scWorld_cp(world);
}

QVector2D coWorld::lookupLoc(t_simtag tag) const{
    Q_ASSERT(tag != NULL_SIM_TAG); //don't die during sim time.
    if (tag == NULL_SIM_TAG)
        return QVector2D(0, 0);
    return world->lookupObject(tag);
}

QVector2D coWorld::cameraOffset() const {
    return camera.curOffset();
}

void coWorld::drawUntracked (gcDrawingImpl &impl) const {
    for (auto renderable : untrackedList)
        renderable->draw(impl);
}
