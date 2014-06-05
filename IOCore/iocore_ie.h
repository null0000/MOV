#ifndef IOCORE_IE_H
#define IOCORE_IE_H


#if defined(IOCORE_LIBRARY)
#  define IO_IE Q_DECL_EXPORT
#else
#  define IO_IE Q_DECL_IMPORT
#endif

#endif // IOCORE_IE_H
