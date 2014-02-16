#ifndef IOCORE_H
#define IOCORE_H

#include <QString>
#include <QMap>
#include <QList>

class icAttrib
{
public:
    typedef enum {StrE, NumE, ListE, DictE, NullAttribE} AttribType;
    virtual AttribType Type() const = 0;
    virtual QString Name() const = 0;

    static icAttrib *ReadFile(QString fileName);
};

class icStrAttrib : public icAttrib {
private:
    QString name;
    QString str;

public:
    icStrAttrib(QString attribInfo, QString name) : name(name), str(attribInfo){}
    AttribType Type() const {return StrE;}
    QString Name() const {return name;}
    QString Entry() const {return str;}
};


class icNumAttrib : public icAttrib  {
private:
    QString name;
    int num;

public:
    icNumAttrib(int val, QString name) : name(name), num(val) {}
    AttribType Type() const {return NumE;}
    QString Name() const {return name;}
    int Entry() const {return num;}
};

class icListAttrib : public icAttrib {
private:
    QString name;
    QList<icAttrib *> attribMap;

public:
    icListAttrib(QList<icAttrib *> list, QString name) : name(name), attribMap(list) {}
    AttribType Type() const {return ListE;}
    QString Name() const {return name;}
    const QMap<icAttrib *> &Entry() const {return attribMap;}
};

class icDictAttrib : public icAttrib {
    typedef QMap<QString, QList<icAttrib>> AttribMap;
private:
    QString name;
    AttribMap attribs;

public:
    icDictAttrib(AttribMaps inputAttribs, QString name) :  name(name), attribs(inputAttribs){}
    AttribType Type() const {return DictE;}
    QString Name() const {return name;}



    const AttribMap &Entry() const {return AttribMap;}
};

class icNullAttrib : public icAttrib {
public:
    icNullAttrib(){}
    AttribType Type() const {return NullAttribE;}
    QString Name() const {return "";}
};

#endif // IOCORE_H
