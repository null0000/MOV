#ifndef SCUSEREGISTER_H
#define SCUSEREGISTER_H


class scObject;
class scWorld;
class scUseRegister {
public:
    virtual void registerUse(const scObject &source) = 0;
    virtual ~scUseRegister(){};

};

#endif // SCUSEREGISTER_H
