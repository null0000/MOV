#ifndef SIMULATIONCORE_H
#define SIMULATIONCORE_H

#include <QtGlobal>
#include <utility>
#include <QWindow>
#include <qvector2d.h>
#include <simulationcore.h>
#include "scObject.h"
#include "scKeyboardInput.h"
#include "sckeyboardcontrolledobj.h"




class scWorld {
public:
    typedef int t_tag;

    t_tag addObject(scObject_d newObj);
    const scObject &lookup(t_tag tag) const {return *simVec[tag];}
    void simulate(delta_t timeDelta);

private:
    QVector<scObject *> simVec;
};

typedef const QSharedPointer<scWorld> scWorld_p;


#endif // SIMULATIONCORE_H
