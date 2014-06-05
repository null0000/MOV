#ifndef GLOBALCORE_IE_H
#define GLOBALCORE_IE_H

#include <QtCore/QtGlobal>

#if defined(GLOBALCORE_LIBRARY)
#  define GLB_IE Q_DECL_EXPORT
#else
#  define GLB_IE Q_DECL_IMPORT
#endif

#endif // GLOBALCORE_IE_H
