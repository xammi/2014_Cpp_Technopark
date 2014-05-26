#include "Tester.h"

namespace NetManagers {

//-------------------------------------------------------------------------------------------------
Tester::Tester()
    :   target(NULL)
{}

Tester::Tester(AbstractNet * _target)
    :   target(_target)
{}

CompResult Tester::test(const InputData & in_data, const OutputData & expect, OutputData &errors) {
    if (target == NULL)
        throw TargetNotFound();

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

int Tester::findMax(const OutputData &out)
{
    if(out.values.isEmpty())
        throw OutputDataIsEmpty();
    double max = out.values[0];
    int maxPos = 0;
    for(int i = 1; i < out.values.size(); ++i)
        if(max < out.values[i]){
            max = out.values[i];
            maxPos = i;
        }
    return maxPos;
}

QString Tester::test(const InputDataSet &dataSet) {
    if (target->getRecArea()[0] == '&')
        throw NetNotTuted();

    QString answer("Ответы для образов: ");
    for(int i = 0; i < dataSet.size(); ++i) {
        InputData in = *dataSet[i];
        if(dataSet[i]->values.size() != target->getInSize())
            throw InputsNeuNetInLayerSizeMismatch();
        OutputData out = target->getResponse(in);

        int maxPos = findMax(out);
        answer.append(target->getRecArea()[maxPos]);
        answer.append(' ');
    }
    return answer;
}

//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
