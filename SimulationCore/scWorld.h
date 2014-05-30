#ifndef SCWORLD_H
#define SCWORLD_H

typedef float delta_t;

class scObject_d;
class scObject;
class scUseRegister;
class scSimulatable;

#include <QVector>
#include <QSharedPointer>
#include "sckeyboardcontrolledobj.h"
#include <deque>
#include "scObjDesc.h"
#include "scTask.h"

class scKeyboardControlledObj;
class scTask;


class scBaseWorld {
public:
    typedef unsigned int t_tag;
    QVector2D lookup(t_tag) const;
};


template <typename planType>
class scSubWorld : public scBaseWorld{
public:
    t_tag addObject(const planType &insertedPlan);
    QVector2D lookup(t_tag tag) const;
    void simulate(delta_t timeDelta);

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
class scWorld {
    scSubWorld<scKeyboardControlledObj> keyboardWorld;
    scSubWorld<scTask> taskWorld;

    /*
     *This is used to track the different types.
     *
     *Note: NEVER EVER use a default statement
     *when dealing with these. ALWAYS ENUMERATE
     *EVERY SINGLE ITEM. The compiler
     *will tell you when you fuck up and forget
     *to update a function if you do that.
    */
    typedef enum {KeyboardTag, TaskTag} TypeTag;
    const unsigned int TypeTagCountS = 2; //UPDATE THIS WITH NEW TYPETAG INFO. SHOULD EQUAL ENUM ENTRY COUNT

public:

    typedef std::pair<TypeTag, scBaseWorld::t_tag> t_tag;

    template<typename planType>
    t_tag addObject(const planType &type);
    QVector2D lookupObject(t_tag tag) const;
    void simulate(delta_t timeDelta);
};

typedef const QSharedPointer<scWorld> scWorld_p;

template<typename planType>
typename scSubWorld<planType>::t_tag scSubWorld<planType>::addObject(const planType &newObj) {
    objList.push_back(typename objlist_t::value_type(scObjDesc(), newObj));
    return objList.size() - 1;
}


#endif // SCWORLD_H
