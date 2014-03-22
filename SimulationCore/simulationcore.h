#ifndef SIMULATIONCORE_H
#define SIMULATIONCORE_H

#include <QtGlobal>
#include <utility>
#include <QWindow>



/**
 * @brief The scInputDevice class
 *
 * This class acts as an input device which
 *  Operates in the language of the simulation
 *  core. In other words, This is expected
 *  to be passed to anything which deals with
 *  user input.
 *
 *
 */
class scInputDevice : public QObject
{
    Q_OBJECT

public:
    scInputDevice(const QWindow &Parent) :
        QObject()
    {
        connect(&Parent, SIGNAL(QWindow::keyPressEvent()), this, SIGNAL(KeyPressEvent));
        connect(&Parent, SIGNAL(QWindow::keyReleaseEvent()), this, SIGNAL(KeyReleaseEvent()));
    }

signals:
    void KeyPressEvent(QKeyEvent *KeyPress);
    void KeyReleaseEvent(QKeyEvent *KeyRelease);

};



class vec2D_t {
    float x, y;

public:
    float X() const {return x;}
    float Y() const {return y;}

    vec2D_t(float x, float y) : x(x), y(y){}

    vec2D_t scale(float factor)const{return vec2D_t(x * factor, y * factor);}
    vec2D_t scale(vec2D_t other)const{return vec2D_t(x * other.X(), y * other.Y());}

};


class pos_t {
    float x;
    float y;

public:
    float X() const {return x;}
    float Y() const {return y;}
    pos_t(float x, float y) : x(x), y(y){}

    pos_t operator +(const vec2D_t &other){return pos_t(x + other.X(), y + other.Y());}
    pos_t &operator +=(const vec2D_t &other){*this = *this + other; return *this;}

};

typedef float delta_t;

class scControlScheme {
    virtual pos_t position() const = 0;
    virtual void spawn(pos_t StartPos) const = 0;
};


class scSimulationObject {

    const static float TIME_CONVERSION_DIVISOR = 1000;
public:
    virtual void Simulate(delta_t timeDelta) = 0;

    static delta_t timeDeltaFromMilli(int milliseconds) {return ((float)(milliseconds))/TIME_CONVERSION_DIVISOR;}
};

class scWorld {
public:

private:

};


#endif // SIMULATIONCORE_H
