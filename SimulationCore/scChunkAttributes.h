#ifndef SCCHUNKATTRIBUTES_H
#define SCCHUNKATTRIBUTES_H

#include <glbDefinitions.h>
#include <random>

#include "scDefinitions.h"
#include "simulationcore_ie.h"

/**
 * @brief The scChunkAttributes class
 *
 * This holds attributes for each chunk, such as
 * it's radius, the mean/median number of resource deposits per chunk,
 * and so on.
 */
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

    static const size_type DEFAULT_COUNT_MEAN = 5;
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

#endif // SCCHUNKATTRIBUTES_H
