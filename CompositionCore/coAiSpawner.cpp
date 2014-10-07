
#include "coAiSpawner.h"
#include "CompositionCore.h"


#include <scTaskIterator.h>
#include <scSingleTask.h>
#include <scWorld.h>
#include <gcImage.h>
#include <QVector2D>

void coAiSpawner::runStep(scWorld &scWorld, delta_t /*time*/) {
    typedef std::vector<QVector2D> vecList_t;
    vecList_t objVec;
    std::insert_iterator<vecList_t> vecItr (objVec, objVec.begin());
    scWorld.gatherUsingList(vecItr);

    if (objVec.size() == 1) {
        scTaskIterator tItr (scSingleTask(QVector2D(50, 50)));
        gcImage image(imageName);
        world->addObject(image, tItr);
    }

    Q_ASSERT(objVec.size() <= 1);


}





coAiSpawner::coAiSpawner(QString imageName, coWorld_p worldPtr) :
    imageName(imageName), world(worldPtr){}
