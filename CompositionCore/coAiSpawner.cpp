
#include "coAiSpawner.h"
#include "CompositionCore.h"


#include <scTaskIterator.h>
#include <scSingleTask.h>
#include <scWorld.h>
#include <gcImage.h>
#include <QVector2D>

void coAiSpawner::spawnAI(QVector2D iVec) {
    scSingleTask st(iVec);
    scTaskIterator tItr (st);
    gcImage image(imageName);
    world->addObject(image, tItr);
}





coAiSpawner::coAiSpawner(QString imageName, coWorld_p worldPtr) :
    imageName(imageName), world(worldPtr){}
