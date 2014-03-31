#ifndef GCIMAGEDESCRIPTION_H
#define GCIMAGEDESCRIPTION_H

#include <QRect>
#include <QVector>
#include <QMap>


/**
 * gcStrTag
 *
 * This is a template class which allows the lookup and reverse
 * lookup of an object so that it can be carried around in a "light"
 * fashion, compared quickly, etc. Kinda like a pointer, but duplicate
 * objects are automatically combined.
 *
 * This will be sped up later, theoretically.
 */
template<typename storeType>
class gcGenericLocker
{
public:
    typedef int t_tag;
public:
    static t_tag toTag(storeType origObj)
    {
        if (reverseMap.find(origObj) != reverseMap.end())
            return reverseMap[origObj];
        t_tag tag = count++;
        reverseMap[origObj] = tag;
        tagMap[tag] = origObj; return count++;
    }
    static storeType lookup(t_tag member){return tagMap[member];}

private:
    static QMap<t_tag, storeType> tagMap; //someday, this will be faster..... you know, if necessary.
    static QMap<storeType, t_tag> reverseMap;
    static t_tag count;
};

typedef gcGenericLocker<QString> gcStringLocker;

/*
 * The "d" in "dt" stands for "description".
 *
 * Can you guess what the "t" stands for?
 *
 * ....(tits.)
 */

class gcImage;
typedef QVector<QRect> gcAnimation_dt; //a description of a bunch of frames
typedef QMap<gcStringLocker::t_tag, gcAnimation_dt> gcSpriteSheet_dt; //Give an animation a name
typedef QMap<gcStringLocker::t_tag, QVector<gcImage> > gcAnimation_t; //instantiation of an animation. Heavier weight (theoretically) than it's description.

class gcImage_d
{
public:
    gcImage_d(gcStringLocker::t_tag name): //assumes the image name and the gif name are the same thing.
        imageSheetName(gcStringLocker::lookup(name)), sheet() {sheet[name] = gcAnimation_dt(); sheet[name].push_back(QRect());}

    gcImage_d(gcAnimation_dt animation, gcStringLocker::t_tag name) : //builds a single animation
        imageSheetName(gcStringLocker::lookup(name)), sheet() {sheet[name] = animation;}

    gcImage_d(gcSpriteSheet_dt animationSheet, gcStringLocker::t_tag name) :
        imageSheetName(gcStringLocker::lookup(name)), sheet(animationSheet){}

     gcAnimation_t toAnimationSet() const;

private:
    QString imageSheetName;
    gcSpriteSheet_dt sheet;

};

#endif // GCIMAGEDESCRIPTION_H
