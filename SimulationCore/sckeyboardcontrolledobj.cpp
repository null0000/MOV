#include "simulationcore.h"
#include "scUseListener.h"

void scKeyboardControlledObj::Simulate(delta_t timeDelta) {
    QVector2D inputScale (lrScale(), udScale());
    QVector2D timeScaledPosDelta = inputScale * timeDelta;
    pos += timeScaledPosDelta;
    if (isUsing() && !useLatch) {
        useLatch = true;
        listener.registerUse(*this);
    }
    else if (!isUsing()) useLatch = false;
}

bool scKeyboardControlledObj::isUsing() const {
    return ks->isDown(kMap->Use());
}
