#include "simulationcore.h"

void scKeyboardControlledObj::Simulate(delta_t timeDelta) {
    QVector2D inputScale (lrScale(), udScale());
    QVector2D timeScaledPosDelta = inputScale * timeDelta;
    pos += timeScaledPosDelta;
}
