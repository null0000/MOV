
#include <QFile>
#include <QPixmap>
#include "GraphicsCore.h"

#include "../ErrorCore/ErrorCore.h"


void gcImage::Load(QString inputFile) {
    bool loaded = map.load(inputFile);
    if (!loaded)
        throw false;
}


bool gcImage::IsLoaded() {
    return !map.isNull();
}

QPixmap gcImage::ToPixmap() const {
        return map;
}


class ecImageLoadError : public ecError {
public:
    ecImageLoadError(QString fileName) : fileName(fileName){}

    virtual QString message() const {return "Failed to load file: " + fileName;}
    virtual ~ecImageLoadError() throw(){}
private:
    QString fileName;

};

gcImage::gcImage(QString InputFile) :
    map()
{
    bool loaded = map.load(InputFile);
    if (!loaded)
        throw ecImageLoadError(InputFile);
}


gcImage::gcImage()  :
    map(){}


class gcImage::gcImageRenderable: public gcRenderable {
public:
   gcImageRenderable(gcImage image) : image(image){}

   virtual void draw(gcDrawingImpl &impl) {impl.Draw(image);}

private:
   gcImage image;
};

gcRenderable *gcImage::toRenderable() const {
    return new gcImageRenderable(*this);
}
