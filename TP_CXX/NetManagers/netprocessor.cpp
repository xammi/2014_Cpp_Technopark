#include "netprocessor.h"

namespace NetManagers {

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
const NetProcessor & NetProcessor::get_self() {
    static NetProcessor self;
    return self;
}
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
