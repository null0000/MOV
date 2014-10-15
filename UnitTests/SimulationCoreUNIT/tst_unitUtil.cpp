

#include "tst_unitUtil.h"

#include <scTask.h>
#include <scWorldDesc.h>

#include <QVector2D>
#include <random>

std::mt19937_64 rnum = std::mt19937_64(std::random_device()());

/**
 * @brief GetLargestOrTen Returns the largest update needed, or ten if that works.
 * @param world
 * @param taskList
 * @return
 *
 *returns the largest update needed to complete all tasks in the task list, or
 *10 if that number is over 10. 10 is chosen as a magic number - probably should
 *be parameterized, but oh well.
 */
float tst_maxUpdateOrTen(const scSubWorld<scTaskIterator> &world, const task_list &taskList) {
    float curMax = 0;
    for (unsigned int i = 0; i < taskList.size(); i++) {
        const scSingleTask &tsk = taskList[i];
        float ticks = tsk.numTicksToLocation(world.lookup(i));
        if (ticks > 10)
            return 10;
        curMax = std::max(curMax, ticks);
    }
    return curMax;

}

number_type tst_genRandomInt(number_type min, number_type max) {
    std::uniform_int_distribution<> gen (min, max);
    return gen(rnum);
}

QVector2D tst_genRandomVec(long long maxX, long long maxY, long long minX, long long minY) {
    std::uniform_int_distribution<> xgen (minX, maxX);
    std::uniform_int_distribution<> ygen (minY, maxY);
    float x = xgen(rnum);
    float y = ygen(rnum);
    return QVector2D(x, y);
}

scObjDesc tst_createObjDesc(size_t idx, const scSubWorld<scTaskIterator> &taskWorld) {
    QVector2D loc (taskWorld.lookup(idx));
    return scObjDesc(loc, QVector2D(1, 1));
}

/**
 * @brief updateList Updates itrVec to match what's shown in scSubWorld
 * @param itrVec
 * @param taskWorld
 *
 *This updates itrVec to match what's in the input subworld. This is used because
 *it's difficult to track needed updates otherwise.
 */
void tst_updateList(std::vector<scTaskIterator> &itrVec, const scSubWorld<scTaskIterator> &taskWorld) {
    QVERIFY(itrVec.size() == taskWorld.maxTag());
    for (size_t i = 0; i < itrVec.size(); i++) {
        scObjDesc od (tst_createObjDesc(i, taskWorld));
        itrVec[i].updateStrategy(od, scWorldDesc());
    }
}


/**
 * @brief maxUpdateOrTen
 *        Returns the maxiumum update needed, or 10 if it's over 10
 * @param itrVec
 * @param taskWorld
 * @return a float
 *
 *Returns the maxiumum update needed to complete all tasks in itrVec, according
 *to the subworld. Alternatively, it returns 10 if the number is above 10.
 *
 *10 is a magic number, but unit test, so oh well.
 */
float tst_maxUpdateOrTen(const scSubWorld<scTaskIterator> &taskWorld, std::vector<scTaskIterator> &itrVec) {
    float curMax = 0;
    Q_ASSERT(itrVec.size() == taskWorld.maxTag());
    for (size_t i = 0; i < itrVec.size(); i++) {
        scObjDesc od (tst_createObjDesc(i, taskWorld));
        scMovementDesc md (itrVec[i].getMovement(od));
        float length = md.maxMovement().length();
        if (length > 10)
            return 10;
        curMax = std::max(curMax, length);
    }
    return curMax;
}
