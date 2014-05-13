#include "BuildInfo.h"

namespace BuildData {

NeuronsCount::NeuronsCount(const int _cnt)
    :   from(_cnt), to(_cnt) {}

NeuronsCount::NeuronsCount(const int range_from, const int range_to)
    :   from(range_from), to(range_to) {}

//-------------------------------------------------------------------------------------------------
BuildInfo::BuildInfo(const QString &name, const QString &func) : netName(name), funcName(func) {}
BuildInfo::BuildInfo(const QString &name, const QString &func, const int lcnt)
    :   netName(name), funcName(func), layersCount(lcnt)
{
    neuronsPerLayer.fill(0, layersCount);
}

}
