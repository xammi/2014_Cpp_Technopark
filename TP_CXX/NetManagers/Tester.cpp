#include "Tester.h"

namespace NetManagers {

//-------------------------------------------------------------------------------------------------
Tester::Tester()
{}

Tester::Tester(AbstractNet * _target)
    :   target(_target)
{}

CompResult Tester::test(const InputData & in_data, const OutputData & expect, OutputData &errors) {
    OutputData test_data = target->getResponse(in_data);
    if(test_data.values.size() != errors.values.size())
        throw SizeMismatch();


    for(int j = 0; j < errors.values.size(); ++j){
        errors.values[j] = test_data.values[j] * (1 - test_data.values[j]) * (expect.values[j] - test_data.values[j]);
    }
    return true;
}

void Tester::setTarget(AbstractNet *new_target) {
    this->target = new_target;
}

void Tester::test(const InOutDataSet &) {

}

//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
