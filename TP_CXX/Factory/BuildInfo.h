#ifndef BUILDINFO_H
#define BUILDINFO_H
#include <QVector>

namespace Factory{

typedef struct {
    unsigned int layersCount;
    QVector <unsigned int> neuronsPerLayer;
}buildInfo;

} // namespace Factory
#endif // BUILDINFO_H
