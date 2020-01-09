//
// Created by tarak on 12/28/2019.
//

#ifndef NEURALNETWORK_NEURON_H
#define NEURALNETWORK_NEURON_H


#include <cmath>
#include <regex>
#include "Matrix.h"

class Neuron {
    static double sigmoidFunction(double);

    static double sigmoidDerivFunction(double);

    static double tanhFunction(double);

    static double tanhDerivFunction(double);

public:
    static Matrix sigmoidFunction(const Matrix &);

    static Matrix sigmoidDerivFunction(const Matrix &);

    static Matrix tanhFunction(const Matrix &);

    static Matrix tanhDerivFunction(const Matrix &);
};


#endif //NEURALNETWORK_NEURON_H
