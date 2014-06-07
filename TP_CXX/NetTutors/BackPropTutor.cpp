#include "BackPropTutor.h"

namespace NetTutors {

//-------------------------------------------------------------------------------------------------


void BackPropTutor::setNet(AbstractNet *aNet) {
    NeuNets::MultiLayerNet *nNet;
    try {
        nNet = dynamic_cast<MultiLayerNet *>(aNet);
    } catch (std::bad_cast) {
        throw WrongKindOfNet();
    }

    if(! nNet){
        aNet->setRecArea("");
        throw NetNotFound();
    }
    currentNet = nNet;
}

void BackPropTutor::setTester(Tester *test){
    if (test == NULL)
        throw TesterNotFound();

    currentTester = test;
}

void BackPropTutor::setLimits(const TuteBoundaries &limits)
{
    tuteLimits = limits;
}

//-------------------------------------------------------------------------------------------------

void BackPropTutor::getMidLayerErrors(DataProcess::OutputData &oldErrors, DataProcess::OutputData &newErrors, NeuNets::Iterator &it)
{
    for(int i = 0; i < it.count(); ++i){
        NeuNets::Neuron bufNeuron = it[i];

        QVector<NeuNets::Synapse *> synVec = bufNeuron.getOutSyn();
        double synapseSum = 0;
        for(int j = 0; j < synVec.size(); ++j){
            synapseSum += synVec[j]->weight * oldErrors.values[j];
        }
        double neuVal = it[i].getVal();
        newErrors.values[i] = neuVal * (1 - neuVal) * synapseSum;
    }
}

void BackPropTutor::processImage(const InputDataSet &inputs, const OutputDataSet &outputs, int curImageIndex)
{
    int iter = 0;
    int maxIter = tuteLimits.maxLayerIter;
    DataProcess::OutputData curErrVec, neuResponseVec;

    for(int i = 0; i < inputs.size(); ++i){
        DataProcess::InputData input = *inputs[i];
        DataProcess::OutputData output = *outputs[i];
        neuResponseVec.clearAndFill();

        if( (input.values.size() != currentNet->getInSize()) ||
                (output.values.size() != currentNet->getOutSize()) )
        {
            throw InputOutputNeuNetCountMismatch();
        }

        while(( !isNormalyzed(neuResponseVec) ) && (iter < maxIter)) {
            ++iter;
            if(iter == maxIter)
                emit toDebug("Количество итераций для одного из образов оказалось равно макcимальному");
            

            // Получили ощибки очередного Input'a
            curErrVec.values.resize(output.values.size());
            currentTester->test(input, output, curErrVec);
            neuResponseVec.values = curErrVec.values;

            if(iter == 1){
                addEveryImageError(curErrVec);
            }
            if((iter % 500) == 0){
                QString firstInput;
                firstInput.sprintf("Вывод ошибок на итерации %d \n для образа %d", iter, curImageIndex);
                emit toDebug(firstInput);
                for(double error: curErrVec.values){
                    firstInput.sprintf("%lf ", error);
                }
                emit toDebug(firstInput);
            }

            NeuNets::Iterator from = currentNet->getOutLayer();
            NeuNets::Iterator to = currentNet->getInLayer();

            while(from != to){
                // изменение весов слоя
                processLayer(from, curErrVec);
                from.prevLayer();

                // Получить ошибки среднего слоя
                DataProcess::OutputData bufErrVec(from.count());
                getMidLayerErrors(curErrVec, bufErrVec, from);
                curErrVec.swapVecs(bufErrVec);
            }
        }
    }
}

bool BackPropTutor::checkEveryImageError() {
    for(int i = 0; i < everyImageErrors.size(); ++i){
        if(!everyImageErrors.isEmpty()){
            OutputData curErrVec = everyImageErrors.takeFirst();
            for(double error: curErrVec.values){
                if(error > tuteLimits.maxNetErr) {
                    everyImageErrors.clear();
                    return 0;
                }
            }
        }
    }
    everyImageErrors.clear();
    return 1;
}

void BackPropTutor::addEveryImageError(OutputData &newError) {
    everyImageErrors.append(newError);
}

void BackPropTutor::processLayer(NeuNets::Iterator &it, DataProcess::OutputData &error)
{
    double speed = tuteLimits.speed;
    if(it.count() != error.values.count())
        throw NetResponseErrorsCountMismatch();

    for(int i = 0; i < it.count(); ++i){
        double neuronError = error.values[i];

        NeuNets::SynapseAct action = [ neuronError, speed ] (NeuNets::Synapse &synapse) {
            double newWeight = synapse.weight + speed * neuronError * synapse.from->getVal();
            synapse.changeWeight(newWeight);
        };

        it[i].apply(action, NeuNets::IN);
    }
}



bool BackPropTutor::isNormalyzed(DataProcess::OutputData &error)
{
    const double maxErr = tuteLimits.maxLayerErr;
    for(int i = 0; i < error.values.size(); ++i){
        if(fabs(error.values[i]) > maxErr)
            return false;
    }
    return true;
}

bool BackPropTutor::start(const TuteData &data){
    int maxIter = tuteLimits.maxNetIter;
    for(int k = 0; k < maxIter; ++k){
        for(int i = 0; i < data.inputs.size(); ++i){
            if(data.inputs[i].size() != data.outputs[i].size())
                throw InputsOutputsCountMismatch();
            processImage(data.inputs[i], data.outputs[i], i);
        }
        if( checkEveryImageError() == true ) // Если ошибки всех векторов сети - нормальные
            break;
        if( k == maxIter - 1)
            currentTester->toDebug("Количество итераций для сети - максимальное!");
    }
    return true;
}

//-------------------------------------------------------------------------------------------------
} // namespace Tutor
