#ifndef SCUNITUTIL_H
#define SCUNITUTIL_H

#include <random>

#include <algorithm>
#include <vector>
#include <QtTest>
#include <QVector2D>
#include <scWorld.h>
#include <scSingleTask.h>
#include <glbDefinitions.h>

typedef std::vector<scSingleTask> task_list;

float tst_maxUpdateOrTen(const scSubWorld<scTaskIterator> &world, const task_list &taskList);
float tst_maxUpdateOrTen(const scSubWorld<scTaskIterator> &taskWorld, std::vector<scTaskIterator> &itrVec);

void tst_updateList(std::vector<scTaskIterator> &itrVec, const scSubWorld<scTaskIterator> &taskWorld);
scObjDesc tst_createObjDesc(size_t idx, const scSubWorld<scTaskIterator> &taskWorld);
QVector2D tst_genRandomVec(number_type maxX, number_type maxY, number_type minX = 0, number_type minY = 0);
number_type tst_genRandomInt(number_type min, number_type max);


template <typename insert_iterator>
insert_iterator tst_insertRaggedTasks(insert_iterator insertLoc, int numTasks, int numJobs,
                                  const QVector2D &startDelta, const QVector2D secondaryDelta);


extern std::mt19937_64 rnum;
template <typename insert_iterator>
insert_iterator tst_insertRaggedTasks(insert_iterator insertLoc, int numTasks, int numJobs,
                                  const QVector2D &startDelta, const QVector2D secondaryDelta)
{
    static std::minstd_rand rnum (22132);

    typedef std::vector<QVector2D> vecList_t;
    for (int i = 0; i < numTasks; i++) {
        vecList_t newTaskList;

        newTaskList.push_back(tst_genRandomVec(startDelta.x(), startDelta.y()));
        int lastIdx = 0;
        int thisJobCount = rnum() % numJobs;

        for (int j = 0; j < thisJobCount - 1; j++) {
            QVector2D deltaVec = tst_genRandomVec(secondaryDelta.x(), secondaryDelta.y());
            QVector2D finalVec = deltaVec + newTaskList[lastIdx];
            newTaskList.push_back(finalVec);
        }

        *insertLoc = newTaskList;
        insertLoc++;
    }
    return insertLoc;
}


/*
 * Thank you internet!
 * (09/OCT/2014)
 * from: www.dreamincode.net/forumss/topic/322182-how-to-find-standard-deviation/
 * http://www.johndcook.com/standard_deviation.html
 *
 * Not mine, but posted without any obvious license attached, and implied to be
 * shared.
*/
#include <iostream>
#include <vector>
#include <cmath> // re. sqrt ...
using namespace std;

class r_stats
{
public:
r_stats() : num(0) {}

void clear() { num = 0; }
void push( double x )
{
    ++num;

    // See Knuth TAOCP vol 2, 3rd edition, page 232
    if( num != 1 )
    {
        newM = oldM + (x - oldM)/num;
        newS = oldS + (x - oldM)*(x - newM);

        oldM = newM; // set up for next iteration
        oldS = newS;
    }
    else
    {
        oldM = newM = x;
        oldS = 0.0;
    }
}
long long size() const { return num; }
double mean() const { return (num > 0) ? newM : 0.0; }
double variance() const { return ( (num > 1) ? newS/(num - 1) : 0.0 ); }
double sd() const { return sqrt( variance() ); }

private:
long long num;
double oldM, newM, oldS, newS;
} ;
//end internet code

#endif // SCUNITUTIL_H
