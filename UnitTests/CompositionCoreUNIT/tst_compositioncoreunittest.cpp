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
    glbGlobals::LogAppDir();
}

measure_type maxLateralRenderDist(QRect geometry) {
    return std::max(geometry.width(), geometry.height()) /2;
}

void CompositionCoreUNITTest::chunkTest()
{
    QVERIFY2(true, "Failure");

    tst_drawRegistry registry;
    QRect screenbounds(registry.screenGeometry());

    coWorld_p world (new coWorld(screenbounds, screenbounds));
    coWorld::t_simtag t = world->addObject(tstNullRenderable(), scTaskIterator(point(0,0)));

    coTagLocFunctor tagFunc (world, t);
    coChunkRenderer<coTagLocFunctor> cr(world, gcImage("face"), tagFunc);
    world->addObject(cr);

    measure_type r = maxLateralRenderDist(screenbounds);
    scSimulationStep *cgen = new scChunkGenerator<coTagLocFunctor>(tagFunc, r);
    scSimulationStep_p sstep (cgen);

    world->registerSimulationStep(sstep);

    world->draw(registry);
    world->simulate(10);


    auto resourceDrawn = [&] (scResourceDeposit rd) {
        QVERIFY(registry.hasDrawn(rd.location()));
    };

    auto comparePoints = [&] (scChunkManager::const_chunk_description cd) {
        std::for_each(cd.beginDeposits(), cd.endDeposits(), resourceDrawn);
    };


    world->chunkCallback(tagFunc(), r, comparePoints);
}

QTEST_MAIN(CompositionCoreUNITTest)
