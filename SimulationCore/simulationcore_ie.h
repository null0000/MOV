#ifndef SIMULATIONCORE_IE_H
#define SIMULATIONCORE_IE_H

#include <QtCore/QtGlobal>

#if defined(SIMULATIONCORE_LIBRARY)
#  define SIM_IE Q_DECL_EXPORT
#else
#  define SIM_IE Q_DECL_IMPORT
#endif


#endif // SIMULATIONCORE_IE_H
