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

    if((!nNet) && (currentNet))
        throw NetNotFound();
    currentNet = nNet;
}

void BackPropTutor::setTester(Tester *test){
    if((!test) && (currentTester))
        currentTester = test;
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

void BackPropTutor::processImage(const InOutDataSet &image)
{
    int iter = 0;


    DataProcess::OutputData curErrVec, neuResponseVec;

        for(int i = 0; i < image.inputs.size(); ++i){

            DataProcess::InputData input = *image.inputs[i];
            DataProcess::OutputData output = *image.outputs[i];

            neuResponseVec.values.resize(1);
            neuResponseVec.values.fill(1);

            while(!isNormalyzed(neuResponseVec)){
                iter++;

                curErrVec.values.resize(output.values.size());

                //NB Веса сети не меняются??
                // Получили ощибки очередного Input'a
                currentTester->test(input, output, curErrVec);
                neuResponseVec.values = curErrVec.values;

                NeuNets::Iterator from = currentNet->getOutLayer();
                NeuNets::Iterator to = currentNet->getInLayer();

                while(from != to){
                    // изменение весов
                    processLayer(from, curErrVec);
                    // Forget-me-not
                    from.prevLayer();

//                    curErrVec = getMidLayerErrors(curErrVec, from);

                    // Middle layer errors
                    DataProcess::OutputData bufErrVec;
                    bufErrVec.values.resize(from.count());
                    getMidLayerErrors(curErrVec, bufErrVec, from);
                    // обычная замена одного вектора ошибок на другой
                    curErrVec.values.clear();
                    curErrVec.values.resize(bufErrVec.values.size());
                    curErrVec.values = bufErrVec.values;
                }

            }
        }
}

void BackPropTutor::processLayer(NeuNets::Iterator &it, DataProcess::OutputData &error)
{
//    const double speed = 1.0;
    if(it.count() != error.values.count())
        throw NetResponseErrorsCountMismatch();

    for(int i = 0; i < it.count(); ++i){
        double neuronError = error.values[i];
        NeuNets::SynapseAct action = [ neuronError ] (NeuNets::Synapse &synapse) {
            double newWeight = synapse.weight + 1 * neuronError * synapse.from->getVal(); // Instead of 1 here needs to be speed
            synapse.changeWeight(newWeight);
        };

        it[i].apply(action, NeuNets::IN);
    }
}

bool BackPropTutor::isNormalyzed(DataProcess::OutputData &error)
{
    const double maxErr = 0.005;  // must be somewhere
    for(int i = 0; i < error.values.size(); ++i){
        if(fabs(error.values[i]) > maxErr)
            return false;
    }
    return true;
}

// e-learning,bmstu.ru/IU7


bool BackPropTutor::start(const TuteData &data){

    // Нужно как-нибудь обрабатывать внешний цикл Сейчас стоит максимум итераций,
    // можно выводить первую ошибку каждого пуска и сравнивать с минимальной
    //
    // один RunData для одного образа
    int maxIter = 300;
    for(int k = 0; k < maxIter; ++k){
        for(int i = 0; i < data.runData.size(); ++i){
            if(data.runData[i].inputs.size() != data.runData[i].outputs.size())

                throw InputsOutputsCountMismatch();
            processImage(data.runData[i]);
        }
    }
    DataProcess::InputData checker;
    checker.values.resize(21);
    checker.values[0] = 0;
    checker.values[1] = 1;
    checker.values[2] = 1;
    checker.values[3] = 1;

    checker.values[4] = 0;
    checker.values[5] = 1;
    checker.values[6] = 0;
    checker.values[7] = 0;

    checker.values[8] = 0;
    checker.values[9] = 1;
    checker.values[10] = 1;
    checker.values[11] = 1;

    checker.values[12] = 0;
    checker.values[13] = 0;
    checker.values[14] = 0;
    checker.values[15] = 1;

    checker.values[16] = 0;
    checker.values[17] = 1;
    checker.values[18] = 1;
    checker.values[19] = 1;

    checker.values[20] = 1;

    DataProcess::OutputData checkerOut = currentNet->getResponse(checker);

    checker.values[0] = 1;
    checker.values[1] = 1;
    checker.values[2] = 1;
    checker.values[3] = 1;

    checker.values[4] = 1;
    checker.values[5] = 0;
    checker.values[6] = 0;
    checker.values[7] = 0;

    checker.values[8] = 1;
    checker.values[9] = 1;
    checker.values[10] = 1;
    checker.values[11] = 1;

    checker.values[12] = 0;
    checker.values[13] = 0;
    checker.values[14] = 0;
    checker.values[15] = 1;

    checker.values[16] = 1;
    checker.values[17] = 1;
    checker.values[18] = 1;
    checker.values[19] = 1;

    checker.values[20] = 1;

    checkerOut = currentNet->getResponse(checker);

    checker.values[0] = 1;
    checker.values[1] = 0;
    checker.values[2] = 0;
    checker.values[3] = 1;

    checker.values[4] = 1;
    checker.values[5] = 0;
    checker.values[6] = 0;
    checker.values[7] = 1;

    checker.values[8] = 1;
    checker.values[9] = 1;
    checker.values[10] = 1;
    checker.values[11] = 1;

    checker.values[12] = 0;
    checker.values[13] = 0;
    checker.values[14] = 0;
    checker.values[15] = 1;

    checker.values[16] = 1;
    checker.values[17] = 1;
    checker.values[18] = 1;
    checker.values[19] = 1;

    checker.values[20] = 1;

    checkerOut = currentNet->getResponse(checker);

    return true;
}

//-------------------------------------------------------------------------------------------------
} // namespace Tutor
