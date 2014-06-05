#ifndef ERRORCORE_IE_H
#define ERRORCORE_IE_H


#include <QtCore/QtGlobal>

#if defined(ERRORCORE_LIBRARY)
#  define ERR_IE Q_DECL_EXPORT
#else
#  define ERR_IE Q_DECL_IMPORT
#endif


#endif // ERRORCORE_IE_H
