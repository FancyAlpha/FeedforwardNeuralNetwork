//
// Created by tarak on 12/28/2019.
//

#include <iostream>
#include "Neuron.h"


Matrix Neuron::activation(const Matrix &m) {

    Matrix res(m);

    for (int r = 0; r < res.height(); r++) {
        for (int c = 0; c < res.width(); c++) {
            res(r, c) = activation(res(r, c));
        }
    }

    return res;
}


Matrix Neuron::activationPrime(const Matrix &m) {

    Matrix res(m);

    for (int r = 0; r < res.height(); r++) {
        for (int c = 0; c < res.width(); c++) {
            res(r, c) = activationPrime(res(r, c));
        }
    }

    return res;
}


double SigmoidNeuron::activation(double x) {

    return (double) 1 / ((double) 1 + exp(double(-x)));
}


double SigmoidNeuron::activationPrime(double x) {

    double sig = activation(x);
    return sig * (1 - sig);
}


double TanhNeuron::activation(double x) {

    return tanh(x);
}


double TanhNeuron::activationPrime(double x) {

    double tanx = activation(x);
    return 1 - (tanx * tanx);
}
