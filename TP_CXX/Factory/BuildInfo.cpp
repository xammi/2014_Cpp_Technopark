#include "BuildInfo.h"

namespace BuildData {

NCount::NCount(const int _cnt)
    :   cnt(_cnt), type(NUM) {}

NCount::NCount(const int range_from, const int range_to)
    :   from(range_from), to(range_to), type(RANGE) {}

}
