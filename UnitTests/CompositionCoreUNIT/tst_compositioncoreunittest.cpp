#include <QString>
#include <QtTest>

#include "tst_UnitHeader.h"

#include <scTaskList.h>
#include <scChunkGenerator.h>

#include <tstDrawRegistry.h>
#include <tst_unitUtil.h>
#include <tstNullRenderable.h>

#include <coTagLocFunctor.h>
#include <coWorld.h>
#include <coChunkRenderer.h>

#include <GlobalCore.h>

CompositionCoreUNITTest::CompositionCoreUNITTest(){
    glbGlobals::LogAppDirForUnit();
}

measure_type maxLateralRenderDist(QRect geometry) {
    return std::max(geometry.width(), geometry.height()) /2;
}

/**
 * @brief CompositionCoreUNITTest::chunkTest
 *
 * Checks the world chunk drawing stuff (i.e. the
 * things that keeps track of resources/other static
 * shit in the world)
 */
void CompositionCoreUNITTest::chunkTest()
{
    tst_drawRegistry registry;
    QRect screenbounds(registry.screenGeometry());

    /*these aren't working correctly. Someone smarter than I will have to figure them out later...*/
//    QTest::ignoreMessage(QtWarningMsg, "QPaintDevice::metrics: Device has no metric information");
//    QTest::ignoreMessage(QtWarningMsg, "Unrecognised metric 1!");
//    QTest::ignoreMessage(QtWarningMsg, "Unrecognised metric 2!");

    coWorld_p world (new coWorld(screenbounds, screenbounds));
    coWorld::t_simtag t = world->addObject(tstNullRenderable(), scTaskIterator(point(0,0)));

    coTagLocFunctor tagFunc (world, t);
    coChunkRenderer<coTagLocFunctor> cr(world, gcImage("face"), tagFunc);
    world->addObject(cr);

    measure_type r = maxLateralRenderDist(screenbounds);

    //create a generator to create chunks at the location given by the tag.
    scSimulationStep *cgen = new scChunkGenerator<coTagLocFunctor>(tagFunc, r);
    scSimulationStep_p sstep (cgen);

    world->registerSimulationStep(sstep);
    world->simulate(10);\
    world->draw(registry);


    auto resourceDrawn = [&] (scResourceDeposit rd) {
        QVERIFY(registry.hasDrawn(rd.location()));
    };

    auto comparePoints = [&] (scChunkManager::const_chunk_description cd) {
        std::for_each(cd.beginDeposits(), cd.endDeposits(), resourceDrawn);
    };


    world->chunkCallback(tagFunc(), r, comparePoints);
}

QTEST_MAIN(CompositionCoreUNITTest)
