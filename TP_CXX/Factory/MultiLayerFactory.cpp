#include "MultiLayerFactory.h"
#include <QFile>
#include <time.h>
#include <stdlib.h>


//const qint32 fileId = 0xA1B1C1D1;
const qint32 fileId = 10;

/* Summary
 * Файл практически готов. Нужно разобраться с чтением - не нравится массив weights (почему?)
 * Можно навести косметику. Можно выкинуть это в долг
 *
 * Предложение - вынести nnInfo на уровень процессора. Тогда можно будет получать инфу оттуда
 *
 * Долг - обработать какое-нибудь стандартное исключение, которое выбрасывается, когда я хочу считать число
 * А получаю EOF
 */



// Jawdropping randomness
//---------------------------------
const int MAX_SYNAPSE_VAL = 1;
const int MIN_SYNAPSE_VAL = -1;

double get_random(double left, double right) {
    return ((double) qrand() / (double) RAND_MAX * (right - left) + left);// Rand Max is very small, so хаполняются не все значащик юиты мантиссы числа, маленькая точность
}

//double get_random(void) {
//    return abs(qrand()) % ((int)(MAX_SYNAPSE_VAL-MIN_SYNAPSE_VAL + 1)) + MIN_SYNAPSE_VAL + (abs(qrand()) % 1000000) / 1000000.0;
//}
//---------------------------------

namespace Factory{

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

    // filename.remove(".net");

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
        throw ReadFileNotFound();

    QTextStream stream(&file);
    quint32 magicNumber;
    stream >> magicNumber;

    if(magicNumber != fileId)
        throw WrongFileFormat();
    stream >> nnInfo.funcName;
    stream >> nnInfo.layersCount;

    // Проверка на правильность входных данных??


    unsigned int bufIntVar; // Нельзя напрямую читать в вектор

    stream >> bufIntVar;
    nnInfo.neuronsPerLayer.append(bufIntVar);

    for(uint i = 1; i < nnInfo.layersCount; ++i){
        stream >> bufIntVar;
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
}


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
    NeuNets::NeuVec inToSend = firstLayer->neuron;

    for(i = 1; i < nnInfo.layersCount; ++i){
        curLayer = new Layer();
        curLayer->neuroCount = nnInfo.neuronsPerLayer[i];

        for(j = 0; j < curLayer->neuroCount; ++j)
            curLayer->neuron.append(new NeuNets::Neuron);

        assembly(*prevLayer, *curLayer, i);
        prevLayer = curLayer;
    }
    NeuNets::NeuVec outToSend = curLayer->neuron;
    bpNewNet = new NeuNets::MultiLayerNet(FuncDisp::func(nnInfo.funcName) , inToSend, outToSend, nnInfo.layersCount);
    bpNewNet->setName(nnInfo.netName);
}


void MultiLayerFactory::assembly(Layer &prevLayer, Layer &curLayer, int layerPos)  {
    uint offset = 0;
    for(uint i = 0; i < prevLayer.neuroCount; ++i){
        for(uint j = 0; j < curLayer.neuroCount; ++j){

            double weight;
            if(currentMode)
                weight = get_random(MIN_SYNAPSE_VAL, MAX_SYNAPSE_VAL);
            else{
                weight = weights[layerPos - 1][i + j + offset]; //
            }

            NeuNets::Synaps *bufSynapse = new NeuNets::Synaps(prevLayer.neuron[i], curLayer.neuron[j], weight);
            prevLayer.neuron[i]->setSynapse(bufSynapse);
            curLayer.neuron[i]->setSynapse(bufSynapse);
        }
        offset++;
    }
}

NeuNets::MultiLayerNet *MultiLayerFactory::createFromFile(const QString &filename) {
    currentMode = 0;
    parseFile(filename);
    allocMemory();
    return bpNewNet;
}

NeuNets::MultiLayerNet *MultiLayerFactory::createFromInfo(const BuildInfo &newInfo) {
    currentMode = 1;
    nnInfo = newInfo;
    allocMemory();
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
    if (nnInfo.layersCount == I) {
        nets.append(createFromInfo(nnInfo));
        return;
    }

    for (int J = cnts[I].from; J <= cnts[I].to; ++J) {
        nnInfo.neuronsPerLayer[I] = J;
        createFromInfoRec(cnts, I + 1, nnInfo, nets);
    }
}

} // namespace Factory
