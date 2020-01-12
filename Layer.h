//
// Created by tarak on 12/28/2019.
//

#ifndef NEURALNETWORK_LAYER_H
#define NEURALNETWORK_LAYER_H


#include "Matrix.h"

struct Layer {

public:
    Layer(int, int, bool);

    Matrix weights;
    Matrix biases;

    Matrix feedforward(const Matrix &);

    friend ostream &operator<<(ostream &, const Layer &);

private:

    const double SPREAD = 1;

    static void randomizeMatrix(Matrix &, double spread);
};


#endif //NEURALNETWORK_LAYER_H
