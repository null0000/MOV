#ifndef SCWORLD_H
#define SCWORLD_H

typedef float delta_t;

class scObject_d;
class scObject;
class scUseRegister;
class scSimulatable;

#include <QVector>
#include <QSharedPointer>
#include <deque>

class scWorld {
public:
    typedef int t_tag;

    t_tag addObject(const scObject_d &newObj);
    const scObject *lookup(t_tag tag) const;
    void simulate(delta_t timeDelta);

    void registerUse(const scObject &source);


    //todo: Add same pattern for descriptions
    //to avoid required instantiation periods.
    //
    //Also, add in some bounds restraint system
    //because this shit will get wrecked otherwise.
    void addUseRegister(scUseRegister &reg);


private:
    typedef std::deque<scObject *> object_list;
     object_list simVec;

    typedef QVector<scUseRegister *> useRegister_list;
    useRegister_list regObjVec;
};

typedef const QSharedPointer<scWorld> scWorld_p;



#endif // SCWORLD_H
