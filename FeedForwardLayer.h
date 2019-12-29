//
// Created by tarak on 12/28/2019.
//

#ifndef NEURALNETWORK_FEEDFORWARDLAYER_H
#define NEURALNETWORK_FEEDFORWARDLAYER_H


#include "Matrix.h"

struct FeedForwardLayer {

    FeedForwardLayer(int, int);
    Matrix weights;
    Matrix biases;
};


#endif //NEURALNETWORK_FEEDFORWARDLAYER_H
