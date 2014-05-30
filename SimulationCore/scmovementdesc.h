#ifndef SCMOVEMENTDESC_H
#define SCMOVEMENTDESC_H

#include <QVector2D>

class scMovementDesc
{
public:
    scMovementDesc(const QVector2D &dir, float maxMag);

    void applyScale(float timeDelta);
    QVector2D maxMovement() const;
private:
    float maxMagnitude;
    QVector2D dir;
};

#endif // SCMOVEMENTDESC_H
