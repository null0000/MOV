#ifndef SCAISPAWNER_H
#define SCAISPAWNER_H


#include <scUseRegister.h>
#include <scWorld.h>
#include <scObject.h>
#include <GraphicsCore.h>

class ccAISpawner : public scUseRegister {
public:
    virtual void registerUse(const scObject &source);
    ccAISpawner(scWorld_p world, gcRenderList_p list, scAIObject_d objectDesc);

    virtual ~ccAISpawner(){}
private:
    scAIObject_d obj;
    scWorld_p world;
    gcRenderList_p list;
};



#endif // SCAISPAWNER_H
