#ifndef GRAPHICSCORE_IE_H
#define GRAPHICSCORE_IE_H

#include <QtCore/QtGlobal>

#if defined(GRAPHICSCORE_LIBRARY)
#  define GFX_IE Q_DECL_EXPORT
#else
#  define GFX_IE Q_DECL_IMPORT
#endif

#endif // GRAPHICSCORE_IE_H
