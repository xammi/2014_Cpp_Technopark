#ifndef NETPROCESSOR_H
#define NETPROCESSOR_H

#include "neunetui.h"
#include "imagestorage.h"

namespace NetManagers {
//-------------------------------------------------------------------------------------------------
class NetProcessor
{
public:
    static NetProcessor * get_self();
    static bool del_self();

protected:
    NetProcessor();
    virtual ~NetProcessor();

    static NetProcessor *self;

    NeuNetUI *gui;
    ImageStorage *imgs;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
#endif // NETPROCESSOR_H
