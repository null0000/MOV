
#include <QFile>
#include <QPixmap>
#include <GlobalCore.h>
#include <QDir>
#include "GraphicsCore.h"
#include "gcImage.h"
#include "gcDrawingImpl.h"


#include <ErrorCore.h>


const QString gcImage::IMAGE_FILE_TYPE = ".gif";


class ecImageLoadError : public ecError {
public:
    ecImageLoadError(QString fileName) : fileName(fileName){}

    virtual QString message() const {return "Failed to load file: " + fileName + "\nIn: " + QDir::currentPath();}
    virtual ~ecImageLoadError() throw(){}
private:
    QString fileName;
};




void gcImage::Load(QString ImageName) {
    glbGlobals::PushDir();
    glbGlobals::MoveToGraphicsDir();
    bool loaded = map.load(ImageName + IMAGE_FILE_TYPE);


    if (!loaded)
        throw ecImageLoadError(ImageName + IMAGE_FILE_TYPE);

    glbGlobals::RevertDir();
}


bool gcImage::IsLoaded() {
    return !map.isNull();
}

QPixmap gcImage::ToPixmap() const {
        return map;
}

gcImage::gcImage(QString ImageName) :
    map()
{
    Load(ImageName);
}


gcImage::gcImage()  :
    map((QPlatformPixmap *)nullptr){}


void gcImage::draw(gcDrawingImpl &impl) const{
    impl.Draw(*this);
}
