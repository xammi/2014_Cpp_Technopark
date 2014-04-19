#include "MultiLayerFactory.h"
#include <QFile>

namespace Factory{



NeuNets::AbstrNet *BackPropFactory::createNet(QString filename)  {
    // set nnInfo
    parseFile(filename);

    // get momory for bpNewNet
    allocMemory();


//    return bpNewNet;
}

void BackPropFactory::parseFile(QString filename) {


    // WTF??
    QFile file(filename);

    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    quint32 magicNumber;
    stream >> magicNumber;

    // How to Hardcode this?
    if(magic != 0xA1B1C1D1)
        ; // BAD FILE FORMAT

    stream >> nnInfo.layersCount;

    // HOW TO MAKE IT PRETTIER?
    for(int i = 0; i < nnInfo.layersCount; ++i){
        stream >> nnInfo.neuronsPerLayer[i];
    }
}



void BackPropFactory::allocMemory() {

    bpNewNet = new NeuNets::MultiLayerNet();


    uint i, j;

    prevLayer = 0;
    for(i = 0; i < nnInfo.layersCount; ++i){
        curLayer = new Layer();
        for(j = 0; j < nnInfo.neuronsPerLayer[i]; ++j)
            curLayer->neuron.append(new NeuNets::Neuron);
        assembly(prevLayer, curLayer);
        prevLayer = curLayer;
    }
    prevLayer->isLast = 1;




    // bpNewNet.append;
}
void BackPropFactory::assembly(Layer *prevLayer, Layer *curLayer)  {
    if((prevLayer) && (curLayer)){
        for(uint i = 0; i < prevLayer->neuroCount; ++i){
            for(uint j = 0; j < curLayer->neuroCount; ++j){

                NeuNets::Synaps *bufSynaps = new NeuNets::Synaps;
                bufSynaps->from = prevLayer->neuron[i];
                bufSynaps->to = curLayer->neuron[j];

                prevLayer->synaps.append(bufSynaps);

                // Задание случайного веса???
            }
        }
    }
    else{
        // Если первый слой
    }
}

} // namespace Factory
