#ifndef GCIMAGE_H
#define GCIMAGE_H

#include "gcRenderable.h"

class QString;
class QPixmap;
class gcRenderable;
class gcDrawingImpl;
class gcImageRenderable;
class gcImage{
public:
    gcImage(QString InputFile);
    gcImage();

    void Load(QString inputFile);

    QPixmap ToPixmap() const;
    bool IsLoaded();

    gcImageRenderable toRenderable() const;

private:
    QPixmap map;
    static const QString IMAGE_FILE_TYPE;
};



class gcImageRenderable: public gcRenderable {
public:
   gcImageRenderable(gcImage image) : image(image){}
   void draw(gcDrawingImpl &impl) const;


private:
   gcImage image;
};

#endif // GCIMAGE_H
