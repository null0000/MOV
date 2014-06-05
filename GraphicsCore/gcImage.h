#ifndef GCIMAGE_H
#define GCIMAGE_H

#include "graphicscore_ie.h"
#include "gcRenderable.h"

class QString;
class QPixmap;
class gcRenderable;
class gcDrawingImpl;
class gcImageRenderable;


class GFX_IE gcImage : gcRenderable{
public:
    gcImage(QString InputFile);
    gcImage();

    void Load(QString inputFile);

    QPixmap ToPixmap() const;
    bool IsLoaded();

    void draw(gcDrawingImpl &impl) const;

private:
    QPixmap map;
    static const QString IMAGE_FILE_TYPE;
};


#endif // GCIMAGE_H
