//
// Created by tarak on 12/28/2019.
//

#include "Neuron.h"

double Neuron::sigmoidFunction(double x) {
    double ex = exp(x);
    return ex / (ex + 1);
}

double Neuron::tanhFunction(double x) {
    return tanh(x);
}

Matrix Neuron::sigmoidFunction(Matrix m) {
    Matrix res(m);

//    for(int r = res.)

    return res;
}
