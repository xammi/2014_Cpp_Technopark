#include "BackPropTutor.h"

namespace NetTutors {

//-------------------------------------------------------------------------------------------------
BackPropTutor::BackPropTutor()
{}

void BackPropTutor::setNet(NeuNets::MultiLayerNet *net){ // TODO: not NULL
    if((!net) && (currentNet))
        throw NetNotFound();
    currentNet = net;
}

void BackPropTutor::setTester(NetManagers::Tester *test){
    if((!test) && (currentTester))
        currentTester = test;
}

void BackPropTutor::getMidLayerErrors(DataProcess::OutputData &oldErrors, DataProcess::OutputData &newErrors, NeuNets::Iterator &it)
{
    for(int i = 0; i < it.count(); ++i){
        QVector<NeuNets::Synapse *> synVec = it[i].getOutSyn();
        double synapseSum = 0;
        for(int j = 0; j < synVec.size(); ++j){
            synapseSum += synVec[i]->weight * oldErrors.values[j];
        }
        double neuVal = it[i].getVal();
        newErrors.values[i] = neuVal * (1 - neuVal) * synapseSum;
    }
}

void BackPropTutor::processImage(const PackedData &image)
{
    for(int i = 0; i < image.inputs.size(); ++i){
        DataProcess::InputData input = *image.inputs[i];
        DataProcess::OutputData output = *image.outputs[i];
        DataProcess::OutputData curErrVec;
        curErrVec.values.resize(output.values.size());

        // Получили ощибки очередного Input'a
        currentTester->test(input, output, curErrVec);

        NeuNets::Iterator from = currentNet->getOutLayer();
        NeuNets::Iterator to = currentNet->getInLayer();


        while(from != to){

            processLayer(from, curErrVec);
            from.nextLayer();

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

void BackPropTutor::processLayer(NeuNets::Iterator &it, DataProcess::OutputData &error)
{
//    const double speed = 1.0;
    if(it.count() != error.values.count())
        throw NetResponseErrorsCountMismatch();

    for(int i = 0; i < it.count(); ++i){
        double neuronError = error.values[i];
        NeuNets::SynapseAct action = [ neuronError ] (NeuNets::Synapse &synapse) {
            double newWeight = synapse.weight + 1 * neuronError * synapse.to->getVal(); // Instead of 1 here needs to be speed
            synapse.changeWeight(newWeight);
        };


        it[i].apply(action, NeuNets::IN);
    }
}

// e-learning,bmstu.ru/IU7


bool BackPropTutor::start(const TuteData &data){

    for(int i = 0; i < data.RunData.size(); ++i){
        if(data.RunData[i].inputs.size() != data.RunData[i].outputs.size())
            throw InputsOutputsCountMismatch();

        processImage(data.RunData[i]);
    }


//    long int curIter = 0;
//        long double curErr = 1;
//        uint curImageNumber = 0;
//        uint curErrLayer = 0;

//        PackedData curImage;


//        CurLayerErr bufLayerErr;

//        CurImageErr bufImageErr;

//        TotalErr runErr;


//        // Нужно проставить начальные значения ошибок
//        for(int j = 0; j < data.ImageData.size(); ++j){
//            CurImageErr bufImageErr;
//            CurLayerErr bufLayerErr;
//            curImage = data.ImageData[j];

//            bufLayerErr.values.resize(curImage.outputs.size());
//            bufLayerErr.values.fill(1);


//            bufImageErr.append(bufLayerErr);
//            runErr.append(bufImageErr);
//            bufImageErr.clear();
//            bufLayerErr.values.clear();
//        }




//        while(curErr > data.minErr){
//            ++curIter;



//            // Тут можно поймать какое-нибудь стандартное исключение, если размера остальных образов не такие, как у первого

//            curImage = data.ImageData[curImageNumber];
//            bufImageErr = runErr[curImageNumber];
//            bufLayerErr = bufImageErr[curErrLayer];
//            // Main Cycle
//            do{

//                NeuNets::Iterator to = currentNet->getInLayer();
//                NeuNets::Iterator from = currentNet->getOutLayer();
//                NeuNets::Iterator mid = from;

//                // Тестер взял картинку текущего образа, его идеальный выход и записал результат в текущие ошибки
//                currentTester->process(&curImage.inputs, &curImage.outputs, &bufLayerErr, currentNet);
//                while (from != to) {
//                    bufImageErr[curErrLayer++] = bufLayerErr;
//                    // Сменить веса для слоя
//                    for(int j = 0; j < from.count(); ++j){
//                        //функция меняет значения синапсов по одной формуле
//                        changeWeights(from[j], bufLayerErr.values[j]);
//                    }


//                    from.nextLayer();
//                    bufLayerErr = getMidError(&bufLayerErr, from, mid);

//                }
//                curErrLayer = 0;
//            }
//            while(! isMinError(&bufImageErr[curErrLayer], data.minErr));
//        }


//    return true;
    return true;
}

//-------------------------------------------------------------------------------------------------
} // namespace Tutor
