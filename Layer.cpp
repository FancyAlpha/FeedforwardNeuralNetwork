//
// Created by tarak on 12/28/2019.
//

#include <iostream>
#include <ctime>
#include "Layer.h"

// w is size of this layer, h is size of next layer?
Layer::Layer(int width, int height, bool randWeight, bool randBias, double start, double end)
        : weights(width, height),
          biases(1, height) {

    if (randWeight) biases.randomize(start, end);
    if (randBias) biases.randomize(start, end);
}

Matrix Layer::feedforward(const Matrix &activations) {
    return (weights * activations) + biases;
}

ostream &operator<<(ostream &os, const Layer &other) {

    os << "layer stats:" << endl;
    os << "weights " << other.weights.width() << "x" << other.weights.height() << endl;
    os << "weights " << other.biases.width() << "x" << other.biases.height() << endl;

    return os;
}
