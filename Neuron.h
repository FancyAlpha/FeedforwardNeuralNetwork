//
// Created by tarak on 12/28/2019.
//

#ifndef NEURALNETWORK_NEURON_H
#define NEURALNETWORK_NEURON_H


#include <cmath>
#include <regex>
#include "Matrix.h"


class Neuron {

private:
    virtual double activation(double) = 0;
    virtual double activationPrime(double) = 0;
public:

    virtual Matrix activation(Matrix &);
    virtual Matrix activationPrime(Matrix &);
};


class SigmoidNeuron : public Neuron {

private:
    double activation(double) override;
    double activationPrime(double) override;
};


class TanhNeuron : public Neuron {

private:
    double activation(double) override;
    double activationPrime(double) override;
};


class SoftmaxNeuron : public Neuron {

private:
    double total = 1;


    double activation(double) override { return 0; }


    double activationPrime(double) override { return 0; };

public:
    Matrix activation(Matrix &) override;

    Matrix activationPrime(Matrix &) override;
};


#endif //NEURALNETWORK_NEURON_H
