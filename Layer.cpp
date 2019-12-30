//
// Created by tarak on 12/28/2019.
//

#include "Layer.h"

// width is size of this layer, height is size of next layer?
Layer::Layer(int width, int height)
        : weights(width, height),
          biases(1, width) {
    randomize();
}

Matrix Layer::feedforward(const Matrix &activations) {

    return weights * activations + biases;
}

// note: only randomizing weights here for simplification
void Layer::randomize() {
    for (int r = 0; r < weights.height(); r++) {
        for (int c = 0; c < weights.width(); c++) {
            weights.set(r, c, ((double) rand()) / RAND_MAX);
        }
    }
}
