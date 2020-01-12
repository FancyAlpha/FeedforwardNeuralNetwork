//
// Created by tarak on 12/28/2019.
//

#include <iostream>
#include <time.h>
#include "Layer.h"

// w is size of this layer, h is size of next layer?
Layer::Layer(int width, int height)
        : weights(width, height),
          biases(1, height) {
    randomize(SPREAD, time(nullptr));
}

Matrix Layer::feedforward(const Matrix &activations) {

    return (weights * activations) + biases;
}

// note: only randomizing weights here for simplification
void Layer::randomize(double spread, unsigned int seed) {
    srand(seed);

    randomizeMatrix(weights, spread); // todo move this to matrix class
    randomizeMatrix(biases, spread);
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
