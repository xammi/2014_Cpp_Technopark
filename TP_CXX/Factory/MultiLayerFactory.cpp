#include "MultiLayerFactory.h"
#include <QFile>
#include <time.h>
#include <stdlib.h>


const int MAX_SYNAPSE_VAL = 1;
const int MIN_SYNAPSE_VAL = -1;

//LOOKS AWFUL!

double get_random(void) {
    return abs(qrand()) % ((int)(MAX_SYNAPSE_VAL-MIN_SYNAPSE_VAL + 1)) + MIN_SYNAPSE_VAL + (abs(qrand()) % 1000000) / 1000000.0;
}

namespace Factory{

NeuNets::AbstractNet *MultiLayerFactory::createNet(const QString &filename)  {
    // set nnInfo
    parseFile(filename);

    // get memory for bpNewNet
    allocMemory();


//    return bpNewNet;
}

void MultiLayerFactory::parseFile(const QString &filename) {

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
        throw FileNotFound();

    QTextStream stream(&file);
    quint32 magicNumber;
    stream >> magicNumber;

    // How to Hardcode this?
    if(magicNumber != 0xA1B1C1D1)
        throw WrongFileFormat();

    stream >> nnInfo.layersCount;

    // HOW TO MAKE IT PRETTIER?
    for(uint i = 0; i < nnInfo.layersCount; ++i){
        stream >> nnInfo.neuronsPerLayer[i];
    }
}



void MultiLayerFactory::allocMemory() {

    Layer *prevLayer;
    Layer *curLayer;

    uint i, j;

    //---------------
    // Seed the timer (seed or not to seed!)
    qsrand( time(NULL) );

    //---------------
    // Creating first Layer(looks bad)
    //---------------
    Layer *firstLayer = new Layer();
    firstLayer->neuroCount = nnInfo.neuronsPerLayer[0];
    for(j = 0; j < firstLayer->neuroCount; ++j)
        firstLayer->neuron.append(new NeuNets::Neuron);
    prevLayer = firstLayer;
    //---------------

    for(i = 1; i < nnInfo.layersCount; ++i){
        curLayer = new Layer();
        curLayer->neuroCount = nnInfo.neuronsPerLayer[i];
        for(j = 0; j < curLayer->neuroCount; ++j)
            curLayer->neuron.append(new NeuNets::Neuron);
        assembly(*prevLayer, *curLayer);
        prevLayer = curLayer;
    }
    prevLayer->isLast = 1;

//    bpNewNet = new NeuNets::MultiLayerNet();  С передачей слокв
    // bpNewNet.append;
}


void MultiLayerFactory::assembly(Layer &prevLayer, Layer &curLayer)  {
    for(uint i = 0; i < prevLayer.neuroCount; ++i){
        for(uint j = 0; j < curLayer.neuroCount; ++j){

            NeuNets::Synaps *bufSynaps = new NeuNets::Synaps;
            bufSynaps->from = prevLayer.neuron[i];
            bufSynaps->to = curLayer.neuron[j];

            // Задание случайного веса???
            bufSynaps->weight = get_random();
            prevLayer.synaps.append(bufSynaps);
        }
    }
}

} // namespace Factory
