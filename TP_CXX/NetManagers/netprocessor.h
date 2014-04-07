#ifndef NETPROCESSOR_H
#define NETPROCESSOR_H

#include "neunetui.h"
#include "imagestorage.h"

namespace NetManagers {
//-------------------------------------------------------------------------------------------------
class NetProcessor
{
public:
    static const NetProcessor & get_self();

protected:
    NetProcessor();
    virtual ~NetProcessor();

    NeuNetUI *gui;
    ImageStorage *imgs;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
#endif // NETPROCESSOR_H
