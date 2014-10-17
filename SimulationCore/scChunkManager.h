#ifndef SCCHUNKMANAGER_H
#define SCCHUNKMANAGER_H

#include "simulationcore_ie.h"

#include "scChunkAttributes.h"
#include "scChunk.h"
#include "scChunkDescription.h"

#include <QVector2D>
#include <random>
#include <cmath>
#include <algorithm>


class scChunk;
class scChunkAttributes;

class scResourceDeposit;

class SIM_IE scChunkManager {
    typedef std::vector<scChunk> sorted_chunk_list; //you have to sort it yourself
    typedef std::vector<scChunk>::iterator chunk_iterator;
    typedef std::vector<scChunk>::const_iterator const_chunk_iterator;
public:
    typedef size_t size_type;
    typedef QVector2D point;
    typedef float measure_type; //!measuring distance in the world
    typedef float coord_type; //!measuring an offset from origin in 1D in the world

    typedef chunk_iterator chunk_tag; //don't abuse this.
    typedef const_chunk_iterator const_chunk_tag; //don't abuse this.

    typedef scChunkDescription<scChunk::const_deposit_iterator, const_chunk_tag> const_chunk_description;
    typedef scChunkDescription<scChunk::deposit_iterator, chunk_tag> chunk_description;


    static const size_type DEFAULT_CHUNK_WIDTH = 50;



    scChunkManager();
    scChunkManager(measure_type width);
    scChunkManager(measure_type width, scChunkAttributes attrib);

    //!gen chunks for chunks that would fall within horz/vert distance of radius
    void genChunks(QVector2D point, float radius);




    /*!
     * Implement interface:
     *   template <typename itr_type>
     *   void cb(chunk_tag t, QRect bounds, itr_type resource_begin, itr_type resource_end)
     * where itr_type is an iterator for type "scResourceDeposit-- *" or
     * "const scResourceDeposit *" depending on constness of callback function used.
     *
     */
    template <typename callback_type>
    void chunkCallback(point p, measure_type radius, callback_type &cb){
        QRect br (boundingRect(p, radius));
        for (measure_type x = br.topLeft().x(); x < br.topRight().x(); x++) {
            for (measure_type y = br.bottomLeft().y(); y < br.topLeft().y(); y++) {
                point searchPoint (x, y);
                chunk_iterator f (find(chunkList, searchPoint));
                doCallbackIfValid(cb, f, searchPoint);
            }
        }
    }


    template <typename callback_type>
    void chunkCallback(point p, measure_type radius, callback_type &cb) const {
        QRect br (boundingRect(p, radius));
        for (measure_type x = br.topLeft().x(); x < br.topRight().x(); x++) {
            for (measure_type y = br.bottomLeft().y(); y < br.topLeft().y(); y++) {
                point searchPoint (x, y);
                const_chunk_iterator f (find(chunkList, searchPoint));
                doCallbackIfValid(cb, f, searchPoint);

            }
        }
    }

    template <typename deposit_iterator>
    void removeDeposit(chunk_tag ctag, deposit_iterator dtag) {
        ctag->removeDeposit(dtag);
    }

private:

    template<typename callback_type>
    void doCallbackIfValid(callback_type &cb, chunk_iterator it, point p);
    template<typename callback_type>
    void doCallbackIfValid(callback_type &cb, const_chunk_iterator it, point p) const;

    class ChunkPointCompare;
    struct ChunkGenerator;

    QRect boundingRect(point Center, measure_type width) const;

    void unique_insert(sorted_chunk_list &list, scChunk c) const;
    void unique_insert(sorted_chunk_list &list, chunk_iterator loc, scChunk c) const;

    chunk_iterator find(sorted_chunk_list &list, point p) const; //returns list.end() if bad
    const_chunk_iterator find(const sorted_chunk_list &list, point p) const;

    static QRect tileIndexToBounds(point loc, measure_type chunkWidth);

    scChunkAttributes attributes;
    measure_type chunkWidth;
    sorted_chunk_list chunkList;
};


template<typename callback_type>
void scChunkManager::doCallbackIfValid(callback_type &cb, chunk_iterator it, point p) {
    if (it != chunkList.end() && it->location() == p)
    {
        cb(chunk_description(it, tileIndexToBounds(it->location(), chunkWidth),
                                  it->begin(), it->end()));
    }

}

template<typename callback_type>
void scChunkManager::doCallbackIfValid(callback_type &cb, const_chunk_iterator it, point p) const{
    if (it != chunkList.end() && it->location() == p)
    {
        cb(const_chunk_description(it, tileIndexToBounds(it->location(), chunkWidth),
                                  it->begin(), it->end()));
    }

}
#endif // SCCHUNKMANAGER_H


