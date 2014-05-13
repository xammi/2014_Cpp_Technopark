#ifndef BUILDINFO_H
#define BUILDINFO_H

#include <QVector>
#include <QString>

namespace BuildData {

enum NumOrRange { NUM, RANGE };

struct NCount {
    NCount() {}
    NCount(const int);
    NCount(const int, const int);

    union {
        int cnt;
        struct {
            int from;
            int to;
        };
    };
    NumOrRange type;
};

typedef QVector<NCount> NCounts;
//-------------------------------------------------------------------------------------------------
struct BuildInfo {
    // BuildInfo() {}
    // BuildInfo(uint, const NCounts &) {}

    uint layersCount;
    QVector<uint> neuronsPerLayer;
    // NCounts cnts;
    QString funcName;
};
//-------------------------------------------------------------------------------------------------
} // namespace Factory
#endif // BUILDINFO_H
