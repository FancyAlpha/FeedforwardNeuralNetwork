//
// Created by tarak on 12/28/2019.
//

#include <iostream>
#include <time.h>
#include "Layer.h"

// width is size of this layer, height is size of next layer?
Layer::Layer(int width, int height)
        : weights(width, height),
          biases(1, height) {
    randomize(10, time(nullptr));
}

Matrix Layer::feedforward(const Matrix &activations) {

    return (weights * activations) + biases;
}

// note: only randomizing weights here for simplification
void Layer::randomize(double spread, unsigned int seed) {
    srand(seed);

    for (int r = 0; r < weights.height(); r++) {
        for (int c = 0; c < weights.width(); c++) {
            weights.set(r, c, (((double) rand()) / RAND_MAX) * 2 * spread - spread);
        }
    }
}

ostream &operator<<(ostream &os, const Layer &other) {

    os << "layer stats:" << endl;
    os << "weights " << other.weights.width() << "x" << other.weights.height() << endl;
    os << "weights " << other.biases.width() << "x" << other.biases.height() << endl;

    return os;
}
