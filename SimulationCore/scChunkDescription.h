#ifndef SCCHUNKDESCRIPTION_H
#define SCCHUNKDESCRIPTION_H

#include <QRect>

template <typename deposit_iterator_type, typename chunk_tag_type>
struct scChunkDescription {
    typedef deposit_iterator_type deposit_iterator;
    typedef chunk_tag_type chunk_tag;

    deposit_iterator beginDeposits() const {return begin;}
    deposit_iterator endDeposits() const {return end;}

    QRect bounds() const {return b;}

    chunk_tag tag() const {return t;}

    scChunkDescription(chunk_tag t, QRect rect, deposit_iterator begin, deposit_iterator end);
private:
    chunk_tag t;
    QRect b;
    deposit_iterator begin;
    deposit_iterator end;
};

template <typename deposit_iterator_type, typename chunk_tag_type>
scChunkDescription<deposit_iterator_type, chunk_tag_type>::scChunkDescription(chunk_tag t, QRect rect, deposit_iterator_type begin, deposit_iterator_type end) :
    t(t), b(rect), begin(begin), end(end){}

#endif // SCCHUNKDESCRIPTION_H
