//
// Created by tarak on 12/27/2019.
//

#include "FeedforwardNeuralNet.h"

FeedforwardNeuralNet::FeedforwardNeuralNet(int *layerHeights, int numLayers) {

    for (int i = 1; i < numLayers; i++) {
        // passing in the arguments of the constructor of the object we want to make is enough
        layers.emplace_back(layerHeights[i-1], layerHeights[i]);
    }
}
