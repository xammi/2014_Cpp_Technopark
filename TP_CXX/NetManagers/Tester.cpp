#include "Tester.h"

namespace NetManagers {

//-------------------------------------------------------------------------------------------------
Tester::Tester()
{}

Tester::Tester(AbstractNet * _target)
    :   target(_target)
{}

CompResult Tester::test(const InputData & in_data, const OutputData & expect) {
    OutputData test_data = target->getResponse(in_data);
    return test_data == expect;
}

void Tester::setTarget(AbstractNet *new_target) {
    this->target = new_target;
}

//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
