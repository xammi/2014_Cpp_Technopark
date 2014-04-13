#include "MultiLayerFactory.h"

namespace Factory{



NeuNets::AbstrNet *BackPropFactory::createNet(QDataStream stream)  {
    // set nnInfo
//    parseFile(stream);

    // get momory for bpNewNet
    allocMemory();

    // connect neurons
    assembly();

//    return bpNewNet;
}

void BackPropFactory::parseFile(QDataStream stream) {
    int magicNumber;
//    fscanf(file, "%d", &magicNumber);

}

void BackPropFactory::allocMemory() {
    uint i, j;
//    bpNewNet = new BackPropNet();
    for(i = 0; i < nnInfo.layersCount; i++){
        bpLayers.append(new Layer);
        for(j = 0; j < nnInfo.neuronsPerLayer[i] - 1; j++){
            bpLayers[i]->neuron.append(new Neuron);
            bpLayers[i]->synaps.append(new Synaps);
        }
    }

    bpLayers[i]->neuron.append(new Neuron);
    bpLayers[i]->is_last = true;

    // bpNewNet.append;
}
void BackPropFactory::assembly()  {
    for(uint i = 0; i < nnInfo.layersCount; i++){

    }
}

} // namespace Factory
