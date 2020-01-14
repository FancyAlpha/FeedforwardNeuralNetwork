//
// Created by tarak on 12/28/2019.
//

#include <iostream>
#include "Neuron.h"

double Neuron::sigmoidFunction(double x) {

    return (double) 1 / ((double) 1 + exp(double(-x)));
}

double Neuron::tanhFunction(double x) {
    return tanh(x);
}


double Neuron::sigmoidDerivFunction(double x) {

    double sig = sigmoidFunction(x);
    return sig * (1 - sig);
}

double Neuron::tanhDerivFunction(double x) {
    double tanx = tanhFunction(x);
    return 1 - (tanx * tanx);
}


Matrix Neuron::sigmoidFunction(const Matrix &m) {

    Matrix res(m);

    for (int r = 0; r < res.height(); r++) {
        for (int c = 0; c < res.width(); c++) {
            res(r, c) = sigmoidFunction(res(r, c));
        }
    }

    return res;
}

Matrix Neuron::tanhFunction(const Matrix &m) {
    Matrix res(m);

    for (int r = 0; r < res.height(); r++) {
        for (int c = 0; c < res.width(); c++) {
            res(r, c) = tanhFunction(res(r, c));
        }
    }

    return res;
}


Matrix Neuron::sigmoidDerivFunction(const Matrix &m) {

    Matrix res(m);

    for (int r = 0; r < res.height(); r++) {
        for (int c = 0; c < res.width(); c++) {
            res(r, c) = sigmoidDerivFunction(res(r, c));
        }
    }

    return res;
}

Matrix Neuron::tanhDerivFunction(const Matrix &m) {
    Matrix res(m);

    for (int r = 0; r < res.height(); r++) {
        for (int c = 0; c < res.width(); c++) {
            res(r, c) = tanhDerivFunction(res(r, c));
        }
    }

    return res;
}
