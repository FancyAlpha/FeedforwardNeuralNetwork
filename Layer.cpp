//
// Created by tarak on 12/28/2019.
//

#include <iostream>
#include "Layer.h"

// width is size of this layer, height is size of next layer?
Layer::Layer(int width, int height)
        : weights(width, height),
          biases(1, width) {
    randomize();
}

Matrix Layer::feedforward(const Matrix &activations) {

//    cout << "feeding forward" << endl;
    Matrix res = weights * activations;
//    cout << res << endl;
    return res;// + biases;
}

// note: only randomizing weights here for simplification
void Layer::randomize() {
    for (int r = 0; r < weights.height(); r++) {
        for (int c = 0; c < weights.width(); c++) {
            weights.set(r, c, ((double) rand()) / RAND_MAX);
        }
    }
}

ostream &operator<<(ostream &os, const Layer &other) {

    os << "layer stats:" << endl;
    os << "weights " << other.weights.width() << "x" << other.weights.height() << endl;
    os << "weights " << other.biases.width() << "x" << other.biases.height() << endl;

    return os;
}
