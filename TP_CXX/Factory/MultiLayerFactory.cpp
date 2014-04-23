#include "MultiLayerFactory.h"
#include <QFile>
#include <time.h>
#include <stdlib.h>


// Jawdropping randomness
//---------------------------------
const int MAX_SYNAPSE_VAL = 1;
const int MIN_SYNAPSE_VAL = -1;

double rand(double left, double right) {
    return ((double) qrand() / (double) RAND_MAX * (right - left) + left);
}

double get_random(void) {
    return abs(qrand()) % ((int)(MAX_SYNAPSE_VAL-MIN_SYNAPSE_VAL + 1)) + MIN_SYNAPSE_VAL + (abs(qrand()) % 1000000) / 1000000.0;
}
//---------------------------------

namespace Factory{

MultiLayerFactory::MultiLayerFactory(bool flag) {
    //---------------
    // Seed the timer (seed or not to seed!)
    if (flag)
        qsrand( time(NULL) );
}

MultiLayerFactory::~MultiLayerFactory() {}

void MultiLayerFactory::writeFile(const QString &filename)
{

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

    // Проверка на правильность входных данных??

    stream >> nnInfo.neuronsPerLayer[0];
    for(uint i = 1; i < nnInfo.layersCount; ++i){
        stream >> nnInfo.neuronsPerLayer[i];
        //
        int cur = nnInfo.neuronsPerLayer[i];
        int prev = nnInfo.neuronsPerLayer[i - 1];
        weights[i] = new int[cur * prev];
        for(int j = 0; j < cur * prev; j++){
            stream >> weights[i][j];
        }
    }
}

// INFO
/*
 * Вектор весов начинаю не с 0, а с 1. Соответственно есть некоторые коррекции в местах с LABEL1
 *
 *
 *
 */



void MultiLayerFactory::allocMemory() {

    Layer *prevLayer;
    Layer *curLayer;

    uint i, j;

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

        assembly(*prevLayer, *curLayer, i);
        prevLayer = curLayer;
    }
}


void MultiLayerFactory::assembly(Layer &prevLayer, Layer &curLayer, int layerPos)  {
    for(uint i = 0; i < prevLayer.neuroCount; ++i){
        for(uint j = 0; j < curLayer.neuroCount; ++j){

            NeuNets::Synaps *bufSynaps = new NeuNets::Synaps;
            bufSynaps->from = prevLayer.neuron[i];
            bufSynaps->to = curLayer.neuron[j];

            if(currentMode)
                bufSynaps->weight = get_random();
            else{
                bufSynaps->weight = weights[layerPos][i + j - 1]; // LABEL1
            }
            prevLayer.synaps.append(bufSynaps);
        }
    }
}

NeuNets::AbstractNet *MultiLayerFactory::createFromFile(const QString &filename) {
    currentMode = 0;
    parseFile(filename);
    allocMemory();
    return bpNewNet;
}

NeuNets::AbstractNet *MultiLayerFactory::createFromInfo(BuildInfo newInfo) {
    currentMode = 1;


    nnInfo = newInfo;
    allocMemory();
    return bpNewNet;
}

} // namespace Factory
