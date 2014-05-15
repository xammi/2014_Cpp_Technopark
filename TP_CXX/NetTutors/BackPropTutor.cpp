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


bool BackPropTutor::isMinError(DataProcess::OutputData *currentErrors, long double err){
    for(int i = 0; i < currentErrors->values.size(); ++i){
        if(currentErrors->values[i] > err)
            return 0;
    }
    return 1;
}

void BackPropTutor::changeWeights(NeuNets::Neuron neuron, double error){
}

CurLayerErr BackPropTutor::getMidError(CurLayerErr *curErr, NeuNets::Iterator cur, NeuNets::Iterator prev){
    CurLayerErr newErr;
    return newErr;
}

bool BackPropTutor::start(const TuteData &data){
    long int curIter = 0;
        long double curErr = 1;
        uint curImageNumber = 0;
        uint curErrLayer = 0;

        PackedData curImage;


        CurLayerErr bufLayerErr;

        CurImageErr bufImageErr;

        TotalErr runErr;


        // Нужно проставить начальные значения ошибок
        for(int j = 0; j < data.ImageData.size(); ++j){
            CurImageErr bufImageErr;
            CurLayerErr bufLayerErr;
            curImage = data.ImageData[j];

            for(int k = 0; k < curImage.outputs.size(); ++k){
                bufLayerErr.values.append(1);
            }

            bufImageErr.append(bufLayerErr);
            runErr.append(bufImageErr);
            bufImageErr.clear();
            bufLayerErr.values.clear();
        }

        while(curErr > data.minErr){
            ++curIter;



            // Тут можно поймать какое-нибудь стандартное исключение, если размера остальных образов не такие, как у первого

            curImage = data.ImageData[curImageNumber];
            bufImageErr = runErr[curImageNumber];
            bufLayerErr = bufImageErr[curErrLayer];
            // Main Cycle
            do{

                NeuNets::Iterator to = currentNet->getInLayer();
                NeuNets::Iterator from = currentNet->getOutLayer();
                NeuNets::Iterator mid = from;

                // Тестер взял картинку текущего образа, его идеальный выход и записал результат в текущие ошибки
//                currentTester->process(&curImage.inputs, &curImage.outputs, &bufLayerErr);
                while (from != to) {
                    bufImageErr[curErrLayer++] = bufLayerErr;
                    // Сменить веса для слоя
                    for(int j = 0; j < from.count(); ++j){
                        //функция меняет значения синапсов по одной формуле
                        changeWeights(from[j], bufLayerErr.values[j]);
                    }


                    from.nextLayer();
                    bufLayerErr = getMidError(&bufLayerErr, from, mid);

                }
                curErrLayer = 0;
            }
            while(! isMinError(&bufImageErr[curErrLayer], data.minErr));
        }


    return true;
}

//-------------------------------------------------------------------------------------------------
} // namespace Tutor
