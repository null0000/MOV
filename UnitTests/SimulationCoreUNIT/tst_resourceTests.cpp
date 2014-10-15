
#include "tst_simulationCoreUnit.h"
#include "tst_unitUtil.h"

#include <glbDefinitions.h>
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

    typedef scChunkManager::chunk_description chunk_description;

    void operator()(chunk_description cd){
        typedef chunk_description::deposit_iterator itr_type;

        QRect bounds (cd.bounds());

        std::stringstream ss;
        ss << "bounds " << dump(bounds) << " Not inside: " << dump(totalBounds);

        QVERIFY2(totalBounds.contains(bounds, false) || totalBounds.intersects(bounds), ss.str().c_str());

        r_stats xstats;
        r_stats ystats;

        for (itr_type rItr = cd.beginDeposits(); rItr != cd.endDeposits(); rItr++) {
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
                   " With " << std::distance(cd.beginDeposits(), cd.endDeposits()) << " resources total";
        QVERIFY2(abs(xstats.mean() - bounds.center().x()) < TOLERANCE, distErr.str().c_str());
        QVERIFY2(abs(ystats.mean() - bounds.center().y()) < TOLERANCE, distErr.str().c_str());

        xDistSd.push(xstats.sd());
        yDistSd.push(ystats.sd());
        resourceCountStats.push(std::distance(cd.beginDeposits(), cd.endDeposits()));
        count++;
    }

    r_stats resourceCountStats;
    r_stats xDistSd;
    r_stats yDistSd;
    size_type count;
private:
    QRect totalBounds;
};

void SimulationCoreUNITTest::testResourceCounting() {
    static const coord_type MAX_X = 2000, MAX_Y = 2000;
    static const coord_type MIN_X = -2000, MIN_Y = -2000;
    static const number_type MAX_RADIUS = 1000;
    static const number_type MIN_RADIUS = 100;
    static const measure_type CHUNK_WIDTH = 50;

    static const number_type MIN_POINTS = 20;
    static const number_type MAX_POINTS = 50;

    static const float RESOURCE_MEAN = 80.0;
    static const float STD_DEVIATION = 5.0;

    typedef std::vector<QVector2D> vector_list;

    scChunkAttributes ab (CHUNK_WIDTH, RESOURCE_MEAN, STD_DEVIATION);
    scChunkManager manager(CHUNK_WIDTH, ab);

    vector_list origins (tst_genRandomInt(MIN_POINTS, MAX_POINTS));

    for (size_type count = 0; count < origins.size(); count++)
        origins[count] = tst_genRandomVec(MAX_X, MAX_Y, MIN_X, MIN_Y);

    for (auto p : origins) {
        manager.genChunks(p, tst_genRandomInt(MIN_RADIUS * 2, MAX_RADIUS));
    }

    QVector2D center(origins[tst_genRandomInt(0, origins.size())]);

    QRect bounds (center.x() - MIN_RADIUS, center.y() - MIN_RADIUS, MIN_RADIUS * 2, MIN_RADIUS * 2);

    testResourceLoc loc (bounds);
    manager.chunkCallback(center, MIN_RADIUS, loc);

    coord_type xTileMin = std::floor((center.x() - MIN_RADIUS) / CHUNK_WIDTH);
    coord_type xTileMax = std::ceil((center.x() + MIN_RADIUS) / CHUNK_WIDTH);
    coord_type yTileMin = std::floor((center.y() - MIN_RADIUS) / CHUNK_WIDTH);
    coord_type yTileMax = std::ceil((center.y() + MIN_RADIUS) / CHUNK_WIDTH);

    QRect intBounds (xTileMin, yTileMax, xTileMax - xTileMin, yTileMax - yTileMin);

    QVERIFY((number_type)loc.count == intBounds.width() * intBounds.height());
}


void SimulationCoreUNITTest::testResourceChunking() {
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

struct removeZero {
    typedef scChunkManager::chunk_description chunk_description;
    void operator()(chunk_description cd) {
        auto i = cd.beginDeposits();
        while (i != cd.endDeposits()) {
            auto dp = i;
            i++;
            if (!dp->remainingValue()) {
                manager.removeDeposit(cd.tag(), dp);
                count++;
            }
        }
    }

    size_type getCount() const {return count;}
    removeZero(scChunkManager &manager) :
        manager(manager), count(0){}

private:
    scChunkManager &manager;
    size_type count;
};

struct doDelta {
    typedef scChunkManager::chunk_description chunk;
    typedef scResourceDeposit::gathered_remaining_pair grp_type;
    typedef scResourceDeposit::resource_type resource_type;

    void operator()(chunk cd) {
        for (auto i = cd.beginDeposits(); i != cd.endDeposits(); i++) {

            resource_type start = i->remainingValue();
            total += start;
            grp_type grp(i->mine(delta));
            gatheredCount += grp.first;
            remainingCount += grp.second;
            QVERIFY(grp.first > 0);
            QVERIFY(grp.second >= 0);
            QVERIFY(grp.first + grp.second == start);
            QVERIFY(grp.second == i->remainingValue());
            if (grp.second) nonzeroCount++;
            else zeroCount++;
            count++;
            QVERIFY(delta != 0 || gatheredCount == 0);
        }
        QVERIFY(gatheredCount > 0);
        QVERIFY(gatheredCount + remainingCount == total);
        QVERIFY(count == nonzeroCount + zeroCount);
    }

    doDelta(delta_t delta) : delta(delta),
        gatheredCount(0), remainingCount(0), total(0), count (0), zeroCount(0), nonzeroCount(0){}

    delta_t delta;
    resource_type gatheredCount;
    resource_type remainingCount;
    resource_type total;
    size_type count;
    size_type zeroCount;
    size_type nonzeroCount;

};

struct chunkCount {
    template <typename input_type>
    void operator()(input_type chunkType){count += std::distance(chunkType.beginDeposits(), chunkType.endDeposits());}

    chunkCount() : count(0){}
    size_type count;
};

size_type remainingChunks(const scChunkManager &man, QVector2D point, measure_type dist) {
    chunkCount c;
    man.chunkCallback(point, dist, c);
    return c.count;
}

void SimulationCoreUNITTest::testResourceGathering() {
    static const coord_type MAX_X = 2000, MAX_Y = 2000;
    static const coord_type MIN_X = -2000, MIN_Y = -2000;
    static const number_type MAX_RADIUS = 1000;
    static const number_type MIN_RADIUS = 100;
    static const measure_type CHUNK_WIDTH = 50;

    static const number_type MIN_POINTS = 20;
    static const number_type MAX_POINTS = 50;

    typedef scResourceDeposit::resource_type resource_type;

    static const float RESOURCE_MEAN = 80.0;
    static const float STD_DEVIATION = 5.0;

    static const resource_type MINE_MIN = 0;
    static const resource_type MINE_MAX = 1000;

    typedef QVector2D point;

    typedef std::vector<point> vector_list;

    scChunkAttributes ab (CHUNK_WIDTH, RESOURCE_MEAN, STD_DEVIATION);
    scChunkManager manager(CHUNK_WIDTH, ab);

    vector_list origins (tst_genRandomInt(MIN_POINTS, MAX_POINTS));

    for (size_type count = 0; count < origins.size(); count++)
        origins[count] = tst_genRandomVec(MAX_X, MAX_Y, MIN_X, MIN_Y);

    for (auto p : origins) {
        manager.genChunks(p, tst_genRandomInt(MIN_RADIUS * 2, MAX_RADIUS));
    }

    point origin(origins.back());

    size_type remaining = 0;
    while ((remaining = remainingChunks(manager, origin, MIN_RADIUS))) {
        doDelta d (tst_genRandomInt(MINE_MIN, MINE_MAX));
        manager.chunkCallback(origin, MIN_RADIUS, d);

        removeZero rz (manager);
        manager.chunkCallback(origin, MIN_RADIUS, rz);
        QVERIFY(rz.getCount() == d.zeroCount);
        QVERIFY(d.count - rz.getCount() == remainingChunks(manager, origin, MIN_RADIUS));
    }
}
