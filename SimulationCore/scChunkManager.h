#ifndef SCCHUNKMANAGER_H
#define SCCHUNKMANAGER_H

#include "simulationcore_ie.h"
#include "scResourceDeposit.h"

#include <QVector2D>
#include <random>
#include <cmath>
#include <algorithm>

class SIM_IE scChunkAttributes {
public:
    typedef size_t size_type;
    typedef QVector2D location;
    typedef long long resource_type;
    typedef float measure_type;

    typedef std::uniform_int_distribution<> location_generator;
    typedef std::normal_distribution<> count_generator;
    typedef std::normal_distribution<measure_type> radius_generator;
    typedef std::normal_distribution<delta_t> time_generator;
    typedef std::uniform_int_distribution<resource_type> resource_generator;

    static const size_type DEFAULT_COUNT_MEAN = 15;
    static const size_type DEFAULT_COUNT_SD = 2;

    static const constexpr measure_type DEFAULT_MAX_RADIUS = 50;
    static const constexpr measure_type DEFAULT_MIN_RADIUS = 10;

    static const constexpr  delta_t MINE_TIME_MEAN = 100;
    static const constexpr  delta_t MINE_TIME_SD = 10;

    static const resource_type DEPOSIT_VALUE_MEAN = 50;
    static const resource_type DEPOSIT_VALUE_SD = 50;


    template <typename random_device>
    location genLocation(random_device &rd) {return location(genLoc(rd), genLoc((rd)));}

    template <typename random_device>
    size_type genDepositCount(random_device &rd) {return (size_type) std::max(0,(int)genCount(rd));}

    template <typename random_device>
    float genRadius(random_device &rd) {return genRad(rd);}

    template <typename random_device>
    delta_t genMiningDuration(random_device &rd) {return genTime(rd);}

    template <typename random_device>
    resource_type genResourceValue(random_device &rd) {return genResource(rd);}



    scChunkAttributes(size_type size = 0, size_type countMean = DEFAULT_COUNT_MEAN, size_type countSd = DEFAULT_COUNT_SD,
                      float maxRadius = DEFAULT_MAX_RADIUS, float minRadius = DEFAULT_MIN_RADIUS,
                      delta_t meanMineTime = MINE_TIME_MEAN, delta_t sdMineTime = MINE_TIME_SD,
                      resource_type meanDepositValue = DEPOSIT_VALUE_MEAN, resource_type sdDepositValue = DEPOSIT_VALUE_SD) :
        genLoc(0, size), genCount (countMean, countSd), genRad(minRadius, maxRadius),
        genTime(meanMineTime, sdMineTime), genResource(meanDepositValue, sdDepositValue){}

private:
    location_generator genLoc;
    count_generator genCount;
    radius_generator genRad;
    time_generator genTime;
    resource_generator genResource;
};

class SIM_IE scChunkManager {
public:
    typedef size_t size_type;
    typedef QVector2D point;
    typedef float measure_type; //!measuring distance in the world
    typedef float coord_type; //!measuring an offset from origin in 1D in the world

    static const size_type DEFAULT_CHUNK_WIDTH = 50;



    scChunkManager();
    scChunkManager(measure_type width);
    scChunkManager(measure_type width, scChunkAttributes attrib);

    //!gen chunks for chunks that would fall within horz/vert distance of radius
    void genChunks(QVector2D point, float radius);




    /*!
     * Implement interface:
     *   template <typename itr_type>
     *   void cb(QRect bounds, itr_type resource_begin, itr_type resource_end)
     * where itr_type is an iterator for type "scResourceDeposit-- *" or
     * "const scResourceDeposit *" depending on constness of callback function used.
     *
     */
    template <typename callback_type>
    void chunkCallback(point p, measure_type radius, callback_type &cb){
        QRect br (boundingRect(p, radius));
        for (measure_type x = br.topLeft().x(); x < br.topRight().x(); x++) {
            for (measure_type y = br.bottomLeft().y(); y < br.topLeft().y(); y++) {
                point searchPoint (x, y);
                chunk_iterator f (find(chunkList, searchPoint));
                doCallbackIfValid(cb, f, searchPoint);
            }
        }
    }


    template <typename callback_type>
    void chunkCallback(point p, measure_type radius, callback_type &cb) const {
        QRect br (boundingRect(p, radius));
        for (measure_type x = br.topLeft().x(); x < br.topRight().x(); x++) {
            for (measure_type y = br.bottomLeft().y(); y < br.topLeft().y(); y++) {
                point searchPoint (x, y);
                const_chunk_iterator f (find(chunkList, searchPoint));
                doCallbackIfValid(cb, f, searchPoint);

            }
        }
    }

private:

    template<typename callback_type, typename iterator_type>
    void doCallbackIfValid(callback_type &cb, iterator_type it, point p);

    class ChunkPointCompare;
    struct ChunkGenerator;

    class Chunk {
    public:
        typedef scResourceDeposit deposit_type;
        typedef std::vector<deposit_type> deposit_list;
        typedef deposit_list::iterator deposit_iterator;
        typedef deposit_list::const_iterator const_deposit_iterator;
        typedef QVector2D point;
        typedef float coord_type;

        coord_type x() const{return loc.x();}
        coord_type y() const{return loc.y();}

        point location() const{return loc;}

        template<typename deposit_iterator_type>
        Chunk(point loc, deposit_iterator_type depositsBegin, deposit_iterator_type depositsEnd) :
            loc(loc), deposits(depositsBegin, depositsEnd){}

        Chunk(){}

        const_deposit_iterator begin() const {return deposits.begin();}
        deposit_iterator begin() {return deposits.begin();}

        const_deposit_iterator end() const {return deposits.end();}
        deposit_iterator end(){return deposits.end();}

    private:
        QVector2D loc;
        deposit_list deposits;

    };

    QRect boundingRect(point Center, measure_type width) const;

    typedef std::vector<Chunk> sorted_chunk_list; //you have to sort it yourself
    typedef std::vector<Chunk>::iterator chunk_iterator;
    typedef std::vector<Chunk>::const_iterator const_chunk_iterator;

    void unique_insert(sorted_chunk_list &list, Chunk c) const;
    void unique_insert(sorted_chunk_list &list, chunk_iterator loc, Chunk c) const;

    chunk_iterator find(sorted_chunk_list &list, point p) const; //returns list.end() if bad
    const_chunk_iterator find(const sorted_chunk_list &list, point p) const;

    static QRect tileIndexToBounds(point loc, measure_type chunkWidth);

    scChunkAttributes attributes;
    measure_type chunkWidth;
    sorted_chunk_list chunkList;
};


template<typename callback_type, typename iterator_type>
void scChunkManager::doCallbackIfValid(callback_type &cb, iterator_type it, point p) {
    if (it != chunkList.end() && it->location() == p)
    {
        cb(tileIndexToBounds(it->location(), chunkWidth), it->begin(), it->end());
    }

}

#endif // SCCHUNKMANAGER_H


