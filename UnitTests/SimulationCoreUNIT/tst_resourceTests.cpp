
#include "tst_simulationCoreUnit.h"
#include "tst_unitUtil.h"

#include <scChunkManager.h>
#include <string>
#include <sstream>


struct testResourceLoc
{
    typedef size_t size_type;
    typedef float coord_type;
    typedef std::vector<size_type> size_list;
    typedef std::vector<coord_type> coord_list;

    static const size_type TOLERANCE = 5;

    testResourceLoc(QRect bounds) :  count(0), totalBounds(bounds){}

    std::string dump(QRect rect) {
        std::stringstream ss;
        ss << dump(rect.topLeft()) <<  "->" << dump(rect.bottomRight());
        return ss.str();
    }
    std::string dump(QPoint p) {
        std::stringstream ss;
        ss << "[" << p.x() << ":" << p.y() << "]";
        return ss.str().c_str();
    }

    template<typename itr_type>
    void operator()(QRect bounds, itr_type resource_begin, itr_type resource_end){
        std::stringstream ss;
        ss << "bounds " << dump(bounds) << " Not inside: " << dump(totalBounds);

        QVERIFY2(totalBounds.contains(bounds, false) || totalBounds.intersects(bounds), ss.str().c_str());

        r_stats xstats;
        r_stats ystats;

        for (itr_type rItr = resource_begin; rItr != resource_end; rItr++) {
            QPoint rLoc (rItr->location().x(), rItr->location().y());
            QPoint adjustedLoc (rLoc.x() + bounds.topLeft().x(), rLoc.y() + bounds.topLeft().y());

            std::stringstream ss;
            ss << "Point " << dump(adjustedLoc) << " Not in bounds of " <<
                  dump(bounds);

            QVERIFY2(bounds.contains(adjustedLoc), ss.str().c_str());
            xstats.push(adjustedLoc.x());
            ystats.push(adjustedLoc.y());
        }
        std::stringstream distErr;
        distErr << "Mean: "  << dump(QPoint(xstats.mean(), ystats.mean())) << " Is too far away from: " << dump(bounds.center()) <<
                   " With " << std::distance(resource_begin, resource_end) << " resources total";
        QVERIFY2(abs(xstats.mean() - bounds.center().x()) < TOLERANCE, distErr.str().c_str());
        QVERIFY2(abs(ystats.mean() - bounds.center().y()) < TOLERANCE, distErr.str().c_str());

        xDistSd.push(xstats.sd());
        yDistSd.push(ystats.sd());
        resourceCountStats.push(std::distance(resource_begin, resource_end));
        count++;
    }

    r_stats resourceCountStats;
    r_stats xDistSd;
    r_stats yDistSd;
    size_type count;
private:
    QRect totalBounds;
};

void SimulationCoreUNITTest::testResourceChunking() {
    typedef float measure_type;
    typedef float coord_type;

    static const coord_type MAX_X = 2000, MAX_Y = 2000;
    static const coord_type MIN_X = -2000, MIN_Y = -2000;
    static const measure_type RADIUS = 1000.0;
    static const measure_type CHUNK_WIDTH = 50;

    static const float RESOURCE_MEAN = 300.0;
    static const float STD_DEVIATION = 5.0;
    static const float TOLERANCE = 1;

    scChunkAttributes ab (CHUNK_WIDTH, RESOURCE_MEAN, STD_DEVIATION);
    scChunkManager manager(CHUNK_WIDTH, ab);

    QVector2D origin(tst_genRandomVec(MAX_X, MAX_Y, MIN_X, MIN_Y));
    QRect rect(0, 0, RADIUS*2, RADIUS*2);
    rect.moveCenter(QPoint(origin.x(), origin.y()));

    manager.genChunks(origin, RADIUS);
    testResourceLoc cb (rect);
    manager.chunkCallback(origin, RADIUS, cb);

    QVERIFY(abs(cb.resourceCountStats.sd() - STD_DEVIATION) < TOLERANCE);

    std::stringstream badMeanMsg;
    badMeanMsg << "Bad mean: " << cb.resourceCountStats.mean() << " Is too far away from desired mean " << RESOURCE_MEAN;

    QVERIFY2(abs(cb.resourceCountStats.mean() - RESOURCE_MEAN) < TOLERANCE, badMeanMsg.str().c_str());

    QVERIFY(cb.xDistSd.sd() < TOLERANCE);
    QVERIFY(cb.yDistSd.sd() < TOLERANCE);
}

void SimulationCoreUNITTest::testResourceGathering() {
}

void SimulationCoreUNITTest::testResourceQueries() {

}
