#ifndef BUILDINFO_H
#define BUILDINFO_H
#include <QVector>

namespace Factory{

struct BuildInfo {
    unsigned int layersCount;
    QVector <unsigned int> neuronsPerLayer;
    QString funcName;
};

} // namespace Factory
#endif // BUILDINFO_H
