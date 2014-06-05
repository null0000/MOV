#ifndef COMMCORE_IE_H
#define COMMCORE_IE_H


#if defined(COMMCORE_LIBRARY)
#  define COM_IE Q_DECL_EXPORT
#else
#  define COM_IE Q_DECL_IMPORT
#endif

#endif // COMMCORE_IE_H
