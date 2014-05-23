#include "MultiLayerFactory.h"
#include <QFile>
#include <time.h>
#include <stdlib.h>

namespace Factory{

//const qint32 fileId = 0xA1B1C1D1;
const qint32 fileId = 10;

// Jawdropping randomness
//---------------------------------
const int MAX_SYNAPSE_VAL = 1;
const int MIN_SYNAPSE_VAL = 0;

double get_random(double left, double right) {
    return ((double) qrand() / (double) RAND_MAX * (right - left) + left);// Rand Max is very small, so хаполняются не все значащик юиты мантиссы числа, маленькая точность
}

//double get_random(void) {
//    return abs(qrand()) % ((int)(MAX_SYNAPSE_VAL-MIN_SYNAPSE_VAL + 1)) + MIN_SYNAPSE_VAL + (abs(qrand()) % 1000000) / 1000000.0;
//}
//---------------------------------

MultiLayerFactory::MultiLayerFactory(bool flag) {
    if (flag)
        qsrand( time(NULL) );
}

MultiLayerFactory::~MultiLayerFactory() {}


//---------------------------------------------
// Формат входного файла.
/* Строка 0: Магическое число
 * Строка 1: Функция активации

 * Строка 2: Количество слоев сети
 * Строка 3: Количество нейронов на 0 слое. Set i = 1;
 * Строка 4: Количество нейронов на i'ом слое
 * Строка 5: Веса между i и i-1 слоем:
 *   Веса нейрона 1
 *   Веса нейрона 2
 *   и т.д.
 */
//---------------------------------------------


void MultiLayerFactory::parseFile(const QString &filename) {
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
        throw ReadFileNotFound();

    QTextStream stream(&file);
    quint32 magicNumber;

    stream >> magicNumber;
    if(magicNumber != fileId)
        throw WrongFileFormat();

    nnInfo.clear();

    stream >> nnInfo.funcName;
    stream >> nnInfo.layersCount;

    // Проверка на правильность входных данных??


    uint bufIntVar; // Количество в слое

    stream >> bufIntVar;
    if(!(bufIntVar > 0))
        throw WrongFileFormat();
    nnInfo.neuronsPerLayer.append(bufIntVar);

    for(uint i = 1; i < nnInfo.layersCount; ++i){
        stream >> bufIntVar;
        if(!(bufIntVar > 0))
            throw WrongFileFormat();
        nnInfo.neuronsPerLayer.append(bufIntVar);
        //
        int cur = nnInfo.neuronsPerLayer[i];
        int prev = nnInfo.neuronsPerLayer[i - 1];

        double *bufArr = new double[cur * prev];


        for(int j = 0; j < cur * prev; ++j){
            stream >> bufArr[j];
            if((bufArr[j] > MAX_SYNAPSE_VAL) || (bufArr[j] < MIN_SYNAPSE_VAL))
                throw WrongData();
        }
        weights.append(bufArr);
    }

    nnInfo.netName = filename;
    nnInfo.netName.remove(".net");
}


MultiLayerNet *MultiLayerFactory::allocMemory(MultiLayerNet *bpNewNet) {

    NeuVec *prevLayer;
    NeuVec *curLayer;
//    Layer *prevLayer;
//    Layer *curLayer;

    uint i, j;

    //---------------
    // Creating first Layer
    //---------------
    NeuVec *firstLayer = new NeuVec();
    uint firstNeuroCount = nnInfo.neuronsPerLayer[0];


    for(j = 0; j < firstNeuroCount; ++j)
        firstLayer->append(new Neuron);

    prevLayer = firstLayer;
    //---------------
    NeuVec inToSend = *firstLayer;

    for(i = 1; i < nnInfo.layersCount; ++i){
        curLayer = new NeuNets::NeuVec();
        uint neuroCount = nnInfo.neuronsPerLayer[i];


        for(j = 0; j < neuroCount; ++j)
            curLayer->append(new Neuron);

        assembly(*prevLayer, *curLayer, i);
        prevLayer = curLayer;
    }
    NeuVec outToSend = *curLayer;
    bpNewNet = new MultiLayerNet(FuncDisp::func(nnInfo.funcName) , inToSend, outToSend, nnInfo.layersCount);
    bpNewNet->setName(nnInfo.netName);
    return bpNewNet;
}


void MultiLayerFactory::assembly(NeuVec &prevLayer, NeuVec &curLayer, int layerPos)  {
    uint offset = 0;

    uint prevNeuCount = prevLayer.size(), curNeuCount = curLayer.size();
    for(uint i = 0; i < prevNeuCount; ++i){
        int curWeight = 0;
        for(uint j = 0; j < curNeuCount; ++j){

            double weight;
            if(currentMode)
                weight = get_random(MIN_SYNAPSE_VAL, MAX_SYNAPSE_VAL);
            else{
//                weight = weights[layerPos - 1][i + j + offset]; //
                weight = weights[layerPos - 1][j + i + curWeight]; //
            }

            Synapse *bufSynapse = new Synapse(prevLayer[i], curLayer[j], weight);
            prevLayer[i]->setSynapse(bufSynapse);
            curLayer[j]->setSynapse(bufSynapse);
            curWeight += (prevNeuCount - 1);
        }

        offset++;
    }
}

MultiLayerNet *MultiLayerFactory::createFromFile(const QString &filename) {
    currentMode = 0;
    MultiLayerNet *bpNewNet = 0;
    parseFile(filename);
    bpNewNet = allocMemory(bpNewNet);
    return bpNewNet;
}

MultiLayerNet *MultiLayerFactory::createFromInfo(const BuildInfo &newInfo) {
    currentMode = 1;
    MultiLayerNet *bpNewNet = 0;
    nnInfo = newInfo;
    bpNewNet = allocMemory(bpNewNet);
    return bpNewNet;
}

//-------------------------------------------------------------------------------------------------
void MultiLayerFactory::createFromInfo(const QString &name, const QString &funcName, const NCounts &cnts, QVector<AbstractNet *> &nets) {
    BuildInfo nnInfo(name, funcName, cnts.size());
    int I = 0;
    createFromInfoRec(cnts, I, nnInfo, nets);
}

void MultiLayerFactory::createFromInfoRec(const NCounts &cnts, int I,
                                          BuildInfo &nnInfo,
                                          QVector<AbstractNet *> &nets) {
    if ((uint)nnInfo.layersCount == I) {
        nets.append(createFromInfo(nnInfo));
        return;
    }

    for (int J = cnts[I].from; J <= cnts[I].to; ++J) {
        nnInfo.neuronsPerLayer[I] = J;
        createFromInfoRec(cnts, I + 1, nnInfo, nets);
    }
}

} // namespace Factory
