#ifndef BUILDINFO_H
#define BUILDINFO_H

#include <QVector>
#include <QString>

namespace BuildData {

struct NeuronsCount {
    NeuronsCount() {}
    NeuronsCount(const int);
    NeuronsCount(const int, const int);

    int from;
    int to;
};

typedef QVector<NeuronsCount> NCounts;
//-------------------------------------------------------------------------------------------------
struct BuildInfo {
    BuildInfo() {}
    BuildInfo(const QString &, const QString &);
    BuildInfo(const QString &, const QString &, const int);
    void clear(){
        layersCount = 0;
        neuronsPerLayer.clear();
        funcName.clear();
        netName.clear();
    }

    uint layersCount;
    QVector<uint> neuronsPerLayer;

    QString funcName;
    QString netName;
};
//-------------------------------------------------------------------------------------------------
} // namespace Factory
#endif // BUILDINFO_H
