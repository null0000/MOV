#ifndef SCWORLD_H
#define SCWORLD_H

typedef float delta_t;

class scObject_d;
class scObject;
class scUseRegister;
class scSimulatable;

#include <QVector>
#include <QSharedPointer>
#include <vector>

#include "sckeyboardcontrolledobj.h"
#include "scTaskIterator.h"
#include <deque>
#include "scObjDesc.h"
#include "scTask.h"
#include "simulationcore_ie.h"
#include "scMovementDesc.h"
#include "scSimulationStep.h"
#include "scWorldDesc.h"
#include "scChunkManager.h"
#include "scDefinitions.h"

#include <glbDefinitions.h>
#include <ErrorCore.h>


/*******************/
/****FILE NOTES****/
/*******************/

/*
 * This file is organized primarily around making
 * everything work. As a result, look for the tag marking
 * scWorld's public interface to figure out what's up.
 *
 * Everything else should be considered "incidental" and shouln't
 * be leveraged by anything outside of the scWorld sphere of influence.
 */

class scKeyboardControlledObj;
class scTask;
class scChunkManager;

class SIM_IE scBaseWorld {
public:
    typedef size_t t_tag;
    point lookup(t_tag) const;
};


template <typename planType>
class scSubWorld : public scBaseWorld{
public:
    typedef scObjDesc obj_type;
    typedef obj_type::resource_type resource_type;

    t_tag addObject(const planType &insertedPlan);
    point lookup(t_tag tag) const;
    const scObjDesc &objInfo(t_tag tag) const;
    void simulate(delta_t timeDelta);

    void removeResources(t_tag obj, resource_type amount);

    t_tag maxTag() const;

    //inserts point type.
    template<typename insert_iterator>
    insert_iterator gatherUsingList(insert_iterator iItr) const;

private:
    typedef std::pair<scObjDesc, planType> fullobj_t;
    typedef std::vector<fullobj_t> objlist_t;
    objlist_t objList;
};

/**
 * @brief The scWorld class
 *
 *  This holds the entirety of all worlds possible.
 *
 *  It works by holding a number of specializations of
 *scSubWorld, which do all the actual calculations and
 *updates. It's organized this way because std::vector
 *has provenly good performance when operating linearily
 *on vectors (due to caching) and it allows for me to
 *remove ALL THE VIRTUAL FUNCTIONS.
 */
class SIM_IE scWorld {
public:
    /*
     *This is used to track the different types.
     *
     *Note: NEVER EVER use a default statement
     *when dealing with these. ALWAYS ENUMERATE
     *EVERY SINGLE ITEM. The compiler
     *will tell you when you fuck up and forget
     *to update a function if you do that.
    */
    //! differentiates between the different objects the scWorld class supports
    typedef enum {
        KeyboardTag, /*!< Keyboard controlled objects tag*/
        TaskTag      /*!< Task controlled objects tag*/
    } TypeTag;
    static const unsigned int TypeTagCountS = 2; //UPDATE THIS WITH NEW TYPETAG INFO. SHOULD EQUAL ENUM ENTRY COUNT


    typedef std::pair<TypeTag, scBaseWorld::t_tag> t_tag; //! used as a pointer for objects
    typedef std::vector<t_tag> t_tagList; //! list of object pointers
    typedef scObjDesc obj_type;
    typedef obj_type::resource_type resource_type;
    typedef scSubWorld<scKeyboardControlledObj> keyboard_world;
    typedef scSubWorld<scTaskIterator> task_world;
    typedef scChunkManager::chunk_description chunk_description;
    typedef scChunkManager::const_chunk_description const_chunk_description;

    static const t_tag NULL_TAG;
private:


    keyboard_world keyboardWorld;
    task_world taskWorld;

    template<typename insert_iterator>
    class AdjacencyAccumulator {
    public:
        AdjacencyAccumulator operator()(scWorld::t_tag tag) const {
            point objLoc(world->lookupObject(tag));
            AdjacencyAccumulator newAA(*this);
            if (objLoc.distanceToPoint(p) < maxDist) {
               *(newAA.itr) = tag;
                newAA.itr++;
            }
            return newAA;
        }

        AdjacencyAccumulator(const scWorld &world, point p,
                             size_t dist, insert_iterator itr) :
            world(&world), p(p), maxDist(dist), itr(itr){}

        insert_iterator getItr() const {return itr;}

    private:
        const scWorld *world;
        point p;
        size_t maxDist;
        insert_iterator itr;
    };

public:
    /*******************************/
    /****MAIN SCWORLD INTERFACE*****/
    /*******************************/

    template<typename insert_iterator>
    insert_iterator gatherUsingList(insert_iterator iItr) const;

    t_tag addObject(const scKeyboardControlledObj &obj);
    t_tag addObject(const scTaskIterator &obj);

    template<typename insert_iterator>
    insert_iterator getAdjacentObjects(point Point, size_t maxDist, insert_iterator iItr) const;

    const scObjDesc &objInfo(t_tag tag) const;
    point lookupObject(t_tag tag) const;

    void simulate(delta_t timeDelta);

    void removeResources(t_tag obj, resource_type amount);
    void addResources(t_tag obj, resource_type amount);

    void genChunks(point Location, measure_type radius);

    template <typename callback_type>
    void chunkCallback(point location, measure_type radius, callback_type &cb) const;

    template <typename Callback>
    Callback forEachTag(Callback func) const;

    void registerSimulationStep(scSimulationStep_p newStep);

    /************************************/
    /****END SCWORLD PUBLIC INTERFACE****/
    /************************************/

private:
    scChunkManager chunkManager;
    template <typename Callback, typename SubWorldType>
    Callback forEachIndividualTag(Callback input, TypeTag type, SubWorldType subworld) const {
        t_tag itrTag (type, 0);
        for (size_t idx = 0; idx < subworld.maxTag(); idx++) {
            itrTag.second = idx;
            input = input(itrTag);
        }
        return input;
    }

    typedef std::vector<scSimulationStep_p> stepList_t;
    stepList_t simulationSteps;
};

typedef QSharedPointer<scWorld> scWorld_p;
typedef QSharedPointer<const scWorld> scWorld_cp;

template<typename planType>
typename scSubWorld<planType>::t_tag scSubWorld<planType>::addObject(const planType &newObj) {
    objList.push_back(typename objlist_t::value_type(scObjDesc(), newObj));
    return objList.size() - 1;
}

class badTagError : public ecError {
public:
    QString message() const {return "Bad tag used to lookup object";}
};

template <typename planType>
point scSubWorld<planType>::lookup(t_tag tag) const {
    if (objList.size() > tag)
        return objList[tag].first.location();

    throw badTagError();
}

template<typename planType>
void scSubWorld<planType>::simulate(delta_t timeDelta) {
    for (typename objlist_t::iterator itr = objList.begin(); itr != objList.end(); itr++) {
        scMovementDesc moveDesc = itr->second.getMovement(itr->first);
        moveDesc = moveDesc.addMaxDelta(timeDelta);
        itr->first.moveAmount(moveDesc.maxMovement());
        itr->second.updateStrategy(itr->first, scWorldDesc());
    }
}

template <typename planType>
void scSubWorld<planType>::removeResources(t_tag obj, resource_type amount) {
    objList[obj].first.removeResources(amount);
}

template<typename planType>
typename scSubWorld<planType>::t_tag scSubWorld<planType>::maxTag() const {
    return objList.size();
}


template<typename planType>
const scObjDesc &scSubWorld<planType>::objInfo(t_tag tag) const {
    if (tag < objList.size())
        return objList[tag].first;
    Q_ASSERT(false);
    return scObjDesc::NULL_DESC;
}

template<typename planType>
template<typename insert_iterator>
insert_iterator scSubWorld<planType>::gatherUsingList(insert_iterator iItr) const {
    for (typename objlist_t::const_iterator cItr = objList.begin(); cItr != objList.end(); cItr++) {
        if (cItr->second.isUsing()) {
            *iItr = std::distance(objList.begin(), cItr);
            iItr++;
        }
    }
    return iItr;
}

template <scWorld::TypeTag TagPrefix>
struct scTagCollator {
    template <typename TagType>
    scWorld::t_tag operator()(TagType tag) {return scWorld::t_tag(TagPrefix, tag);}
};

template<typename insert_iterator>
insert_iterator scWorld::gatherUsingList(insert_iterator iItr) const {
    typedef keyboard_world::t_tag keyboard_tag;
    typedef std::vector<keyboard_tag> keyboard_tag_list;

    typedef task_world::t_tag task_tag;
    typedef std::vector<task_tag> task_tag_list;

    typedef std::vector<t_tag> tag_list;

    keyboard_tag_list klist;
    std::insert_iterator<keyboard_tag_list> ktItr (klist, klist.begin());
    keyboardWorld.gatherUsingList(ktItr);

    task_tag_list tlist;
    std::insert_iterator<task_tag_list> ttItr (tlist, tlist.begin());
    taskWorld.gatherUsingList(ttItr);

    tag_list rlist (klist.size() + tlist.size());
    std::insert_iterator<tag_list> rlistIItr (rlist, rlist.begin());
    rlistIItr = std::transform(klist.begin(), klist.end(), rlistIItr, scTagCollator<KeyboardTag>());
    std::transform(tlist.begin(), tlist.end(), rlistIItr, scTagCollator<TaskTag>());
    for (auto tag : rlist) {
        *iItr = tag;
        iItr++;
    }
    return iItr;
}

/**
 * function: forEachTag
 *  Template argument: Callback
 *  Template contract: Functor which implements the function:
 *      Callback operator()(scWorld::t_tag tag) const;
 *
 *      In return, the functor will be called with each
 *      t_tag that is valid for this scWorld object.
 */
template <typename Callback>
Callback scWorld::forEachTag(Callback func) const {
    func = forEachIndividualTag(func, KeyboardTag, keyboardWorld);
    func = forEachIndividualTag(func, TaskTag, taskWorld);
    Q_STATIC_ASSERT(TypeTagCountS == 2);
    return func;
}


template <typename callback_type>
/**
 * @brief scWorld::chunkCallback
 * @param location
 * @param radius
 * @param cb
 *
 * Calls cb with the argument "const scChunkDescription" for all chunks within
 * "radius" units of "location"
 */
void scWorld::chunkCallback(point location, measure_type radius, callback_type &cb) const {
    chunkManager.chunkCallback(location, radius, cb);
}


template<typename insert_iterator>
insert_iterator scWorld::getAdjacentObjects(point Point, size_t maxDist,
                                            insert_iterator iItr) const {
    AdjacencyAccumulator<insert_iterator> aa (*this, Point, maxDist, iItr);
    aa = forEachTag(aa);
    return aa.getItr();
}


#endif // SCWORLD_H
