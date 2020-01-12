//
// Created by tarak on 12/28/2019.
//

#include <iostream>
#include <ctime>
#include "Layer.h"

// w is size of this layer, h is size of next layer?
Layer::Layer(int width, int height, bool rand = true)
        : weights(width, height),
          biases(1, height) {

    int seed = time(nullptr);
    srand(seed);

    randomizeMatrix(weights, SPREAD); // todo move this to matrix class
    if (rand) {
        randomizeMatrix(biases, SPREAD);
    }
}

Matrix Layer::feedforward(const Matrix &activations) {

    return (weights * activations) + biases;
}

void Layer::randomizeMatrix(Matrix &mat, double spread) {
    for (int r = 0; r < mat.height(); r++) {
        for (int c = 0; c < mat.width(); c++) {
            mat(r, c) = (((((double) rand()) / RAND_MAX) * 2) - 1) * spread;
        }
    }
}

ostream &operator<<(ostream &os, const Layer &other) {

    os << "layer stats:" << endl;
    os << "weights " << other.weights.width() << "x" << other.weights.height() << endl;
    os << "weights " << other.biases.width() << "x" << other.biases.height() << endl;

    return os;
}
