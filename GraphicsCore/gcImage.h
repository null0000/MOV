#ifndef GCIMAGE_H
#define GCIMAGE_H

class QString;
class QPixmap;
class gcRenderable;

class gcImage{
public:
    gcImage(QString InputFile);
    gcImage();

    void Load(QString inputFile);

    QPixmap ToPixmap() const;
    bool IsLoaded();

    gcRenderable *toRenderable() const;

private:
    QPixmap map;
    static const QString IMAGE_FILE_TYPE;
    class gcImageRenderable;
};

#endif // GCIMAGE_H
