#ifndef NEUNET_GLOBAL_H
#define NEUNET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NEUNET_LIBRARY)
#  define NEUNETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NEUNETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NEUNET_GLOBAL_H
