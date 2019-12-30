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

Matrix Neuron::sigmoidFunction(const Matrix &m) {
    Matrix res(m);

    for (int r = 0; r < res.height(); r++) {
        for (int c = 0; c < res.width(); c++) {
            res.set(r, c, sigmoidFunction(res.get(r, c)));
        }
    }

    return res;
}

Matrix Neuron::tanhFunction(const Matrix &m) {
    Matrix res(m);

    for (int r = 0; r < res.height(); r++) {
        for (int c = 0; c < res.width(); c++) {
            res.set(r, c, tanhFunction(res.get(r, c)));
        }
    }

    return res;
}
