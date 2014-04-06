#include "netprocessor.h"

namespace NetManagers {

NetProcessor *NetProcessor::self = NULL;
//-------------------------------------------------------------------------------------------------
NetProcessor::NetProcessor()
    :   gui(new NeuNetUI), imgs(new ImageStorage)
{
    gui->show();
}

NetProcessor::~NetProcessor() {
    delete gui;
    delete imgs;
}
//-------------------------------------------------------------------------------------------------
NetProcessor * NetProcessor::get_self() {
    if (! self) {
        self = new NetProcessor;
    }
    return self;
}

bool NetProcessor::del_self() {
    if (! self) {
        delete self;
        return true;
    }
    return false;
}
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
