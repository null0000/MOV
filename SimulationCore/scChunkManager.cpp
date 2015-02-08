
#include <random>
#include <cmath>
#include "scChunkManager.h"

scChunkManager::scChunkManager()  :
    chunkWidth(DEFAULT_CHUNK_WIDTH){}
scChunkManager::scChunkManager(measure_type Width) :
    attributes(Width), chunkWidth(Width){}
scChunkManager::scChunkManager(measure_type width, scChunkAttributes attrib) :
    attributes(attrib), chunkWidth(width){}


struct scChunkManager::ChunkGenerator {
    typedef size_t size_type;
    typedef std::mt19937_64 random_generator;
    typedef scChunkManager::measure_type measure_type;
    scChunk operator()(point loc) {
        size_type deposits = ab.genDepositCount(rd);
        scChunk::deposit_list dl = deposits ? scChunk::deposit_list(deposits) : scChunk::deposit_list();

        for_each(dl.begin(), dl.end(), oneDeposit{rd, ab});
        return scChunk(loc, dl.begin(), dl.end());
    }

    struct oneDeposit {
        random_generator &rd;
        scChunkAttributes &ab;
        void operator()(scResourceDeposit &deposit) {
            deposit = scResourceDeposit(ab.genLocation(rd), ab.genRadius(rd),
                                        ab.genMiningDuration(rd), ab.genResourceValue(rd));
        }};
    random_generator &rd;
    scChunkAttributes &ab;
};

void scChunkManager::genChunks(point p, measure_type radius) {
    std::random_device rd;
    std::mt19937_64 mt(rd()); //use the crappy random generator to make the seed for the good one
    ChunkGenerator cgen {mt, attributes};
    QRect allTileBounds (boundingRect(p, radius));

    //TODO: can totally vectorize this shit.
    for (measure_type x = allTileBounds.topLeft().x(); x < allTileBounds.topRight().x(); x++) {
        for (measure_type y = allTileBounds.bottomLeft().y(); y < allTileBounds.topLeft().y(); y++) {
            point searchPoint (x, y);
            chunk_iterator f (find(chunkList, searchPoint));
            unique_insert(chunkList, f, cgen(searchPoint));
        }
    }
}

struct scChunkManager::ChunkPointCompare{

    bool operator()(const scChunk &c1, const scChunk &c2) {
        return (*this)(c1.location(), c2.location());
    }
    bool operator()(const scChunk &c, point p) {return (*this)(c.location(), p);}
    bool operator()(point p, const scChunk &c){return (*this)(p, c.location());}


    bool operator()(const point &p1, const point &p2) {
        if (p1.x() < p2.x())
            return true;
        if (p1.x() != p2.x())
            return false;
        if (p1.y() < p2.y())
            return true;
        return false;
    }

};


void scChunkManager::unique_insert(sorted_chunk_list &list, chunk_iterator loc, scChunk c) const {
    if (loc != list.end() && list.size() != 0 && loc->location() == c.location()) {
        return;
    }
    list.insert(loc, c);
}
void scChunkManager::unique_insert(sorted_chunk_list &list, scChunk c) const {
    chunk_iterator cItr = std::lower_bound(list.begin(), list.end(), c, ChunkPointCompare());
    if (cItr != list.end())
        return;
    if (cItr->location() != c.location())
        list.insert(cItr, c);
}

scChunkManager::chunk_iterator scChunkManager::find(sorted_chunk_list &list, point p) const {
   return std::lower_bound(list.begin(), list.end(), p, ChunkPointCompare());
}

scChunkManager::const_chunk_iterator scChunkManager::find(const sorted_chunk_list &list, point p) const {
    return std::lower_bound(list.begin(), list.end(), p, ChunkPointCompare());
}

/**
 * @brief scChunkManager::boundingRect
 * @param Center
 * @param width
 * @return imaginary rectangle containing the set of chunks that matter
 *
 * Creates a rectangle whose attributes describe which chunks need to be
 * paid attention to (i.e. top left is the top left most chunk, bottom right
 * is the bottom right most chunk)
 */
QRect scChunkManager::boundingRect(point Center, measure_type width) const {
    coord_type xTileMin = std::floor((Center.x() - width) / chunkWidth);
    coord_type xTileMax = std::ceil((Center.x() + width) / chunkWidth);
    coord_type yTileMin = std::floor((Center.y() - width) / chunkWidth);
    coord_type yTileMax = std::ceil((Center.y() + width) / chunkWidth);

    return QRect(QPoint(xTileMin, yTileMax), QPoint(xTileMax, yTileMin));
}


QRect scChunkManager::tileIndexToBounds(point loc, measure_type chunkWidth) {
    coord_type left = loc.x() * chunkWidth;
    coord_type up = (loc.y()) * chunkWidth;

    //+1 is b/c QRect assums boundries don't overlap when they do. Causes issues w/
    //deposit placement.
    return QRect(left, up, chunkWidth + 1, chunkWidth + 1);
}
