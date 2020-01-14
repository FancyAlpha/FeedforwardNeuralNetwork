//
// Created by tarak on 12/28/2019.
//

#ifndef NEURALNETWORK_LAYER_H
#define NEURALNETWORK_LAYER_H


#include "Matrix.h"

struct Layer {

public:
    Matrix weights;
    Matrix biases;

    Layer(int, int, bool= true, bool= true, double= -0.5, double= 0.5);

    Matrix feedforward(const Matrix &);

    friend ostream &operator<<(ostream &, const Layer &);
};


#endif //NEURALNETWORK_LAYER_H
