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
#include <ErrorCore.h>
#include "scSimulationStep.h"
class scKeyboardControlledObj;
class scTask;


class SIM_IE scBaseWorld {
public:
    typedef size_t t_tag;
    QVector2D lookup(t_tag) const;
};

/**
 *
 */
template <typename planType>
class scSubWorld : public scBaseWorld{
public:
    t_tag addObject(const planType &insertedPlan);
    QVector2D lookup(t_tag tag) const;
    void simulate(delta_t timeDelta);

    t_tag maxTag() const;

    //inserts QVector2D type.
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
private:


    scSubWorld<scKeyboardControlledObj> keyboardWorld;
    scSubWorld<scTaskIterator> taskWorld;


    template<typename insert_iterator>
    class AdjacencyAccumulator {
    public:
        AdjacencyAccumulator operator()(scWorld::t_tag tag) const {
            QVector2D objLoc(world->lookupObject(tag));
            AdjacencyAccumulator newAA(*this);
            if (objLoc.distanceToPoint(point) < maxDist) {
               *(newAA.itr) = tag;
                newAA.itr++;
            }
            return newAA;
        }

        AdjacencyAccumulator(const scWorld &world, QVector2D Point,
                             size_t dist, insert_iterator itr) :
            world(&world), point(Point), maxDist(dist), itr(itr){}

        insert_iterator getItr() const {return itr;}

    private:
        const scWorld *world;
        QVector2D point;
        size_t maxDist;
        insert_iterator itr;
    };

public:


    template<typename insert_iterator>
    insert_iterator gatherUsingList(insert_iterator iItr) const;

    t_tag addObject(const scKeyboardControlledObj &obj);
    t_tag addObject(const scTaskIterator &obj);



    template<typename insert_iterator>
    insert_iterator getAdjacentObjects(QVector2D Point, size_t maxDist,
                                       insert_iterator iItr) const {
        AdjacencyAccumulator<insert_iterator> aa (*this, Point, maxDist, iItr);
        aa = forEachTag(aa);
        return aa.getItr();
    }


    QVector2D lookupObject(t_tag tag) const;
    void simulate(delta_t timeDelta);


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
    Callback forEachTag(Callback func) const {
        func = forEachIndividualTag(func, KeyboardTag, keyboardWorld);
        func = forEachIndividualTag(func, TaskTag, taskWorld);
        Q_STATIC_ASSERT(TypeTagCountS == 2);
        return func;
    }

    void registerSimulationStep(scSimulationStep_p newStep);

private:
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
QVector2D scSubWorld<planType>::lookup(t_tag tag) const {
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
template<typename planType>
typename scSubWorld<planType>::t_tag scSubWorld<planType>::maxTag() const {
    return objList.size();
}

template<typename planType>
template<typename insert_iterator>
insert_iterator scSubWorld<planType>::gatherUsingList(insert_iterator iItr) const {
    for (typename objlist_t::const_iterator cItr = objList.begin(); cItr != objList.end(); cItr++) {
        if (cItr->second.isUsing()) {
            *iItr = cItr->first.location();
            iItr++;
        }
    }
    return iItr;
}


template<typename insert_iterator>
insert_iterator scWorld::gatherUsingList(insert_iterator iItr) const {
    iItr = keyboardWorld.gatherUsingList(iItr);
    iItr = taskWorld.gatherUsingList(iItr);
    return iItr;
}

#endif // SCWORLD_H
