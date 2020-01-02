//
// Created by tarak on 12/28/2019.
//

#ifndef NEURALNETWORK_LAYER_H
#define NEURALNETWORK_LAYER_H


#include "Matrix.h"

struct Layer {

public:
    Layer(int, int);

    Matrix weights;
    Matrix biases;

    Matrix feedforward(const Matrix &);

    friend ostream &operator<<(ostream &, const Layer &);

private:

    void randomize(double, unsigned int);
};


#endif //NEURALNETWORK_LAYER_H
