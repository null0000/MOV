#ifndef IOCORE_H
#define IOCORE_H

#include <QXmlStreamWriter>
#include "iocore_ie.h"

class IO_IE icXMLObject {
public:
    void WriteToFile(QXmlStreamWriter &writer);

};

#endif // IOCORE_H
