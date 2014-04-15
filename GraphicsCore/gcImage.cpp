
#include <QFile>
#include <QPixmap>
#include <GlobalCore.h>
#include <QDir>
#include "GraphicsCore.h"

#include "../ErrorCore/ErrorCore.h"


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
    QString path1 = QDir::currentPath();
    glbGlobals::MoveToGraphicsDir();
    bool loaded = map.load(ImageName + IMAGE_FILE_TYPE);

    QString path2 = QDir::currentPath();
    printf((path1 + "second Path: " + path2 + "\n").toStdString().c_str());

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
    map(){}


gcImageRenderable gcImage::toRenderable() const {
    return gcImageRenderable(*this);
}

void gcImageRenderable::draw(gcDrawingImpl &impl) const{
    impl.Draw(image);
}
