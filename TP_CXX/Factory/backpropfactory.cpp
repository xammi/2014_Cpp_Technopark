#include "backpropfactory.h"

namespace Factory{


AbstractNet *BackPropFactory::createNet(FILE *file)  {
    // set nnInfo
    parseFile(file);

    // get momory for bpNewNet
    allocMemory();

    // connect neurons
    assembly();

    return bpNewNet;
}

void BackPropFactory::parseFile(FILE *file) {
    int magicNumber;
    fscanf(file, "%d", &magicNumber);

    return 0;
}

void BackPropFactory::allocMemory() {
    uint i, j;
    bpNewNet = new BackPropNet();
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
    return 0;
}
void BackPropFactory::assembly()  {
    for(uint i = 0; i < nnInfo.layersCount; i++){

    }
    return 0;
}
} // namespace Factory
