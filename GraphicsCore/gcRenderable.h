#ifndef GCRENDERABLE_H
#define GCRENDERABLE_H


class gcDrawingImpl;

class gcRenderable{
public:
    virtual void draw(gcDrawingImpl &impl) const = 0;
    virtual ~gcRenderable(){}
};

#endif // GCRENDERABLE_H
