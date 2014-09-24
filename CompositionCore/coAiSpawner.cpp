
#include "coAiSpawner.h"
#include "CompositionCore.h"


#include <scTaskIterator.h>
#include <scSingleTask.h>
#include <scWorld.h>
#include <gcImage.h>
#include <QVector2D>

void coAiSpawner::runStep(scWorld &world, delta_t /*time*/) {
    typedef std::vector<QVector2D> vecList_t;
    vecList_t objVec;
    std::insert_iterator<vecList_t> vecItr (objVec, objVec.begin());
    world.gatherUsingList(vecItr);

    if (objVec.size() == 1) {
        scTaskIterator tItr (scSingleTask(QVector2D(50, 50)));
        gcImage image(imageName);
    }

    Q_ASSERT(objVec.size() <= 1);

}





coAiSpawner::coAiSpawner(gcRenderList_p renderList, QString imageName,
            QSharedPointer<scWorld> worldPtr) :
    renderList(renderList), imageName(imageName), worldPtr(worldPtr){}
