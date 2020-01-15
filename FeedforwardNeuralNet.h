//
// Created by tarak on 12/27/2019.
//

#ifndef NEURALNETWORK_FEEDFORWARDNEURALNET_H
#define NEURALNETWORK_FEEDFORWARDNEURALNET_H


#include <vector>
#include "Layer.h"
#include "MNISTPicture.h"
#include "Neuron.h"


class FeedforwardNeuralNet {

public:
    FeedforwardNeuralNet(const int *, int, Neuron *, Neuron *);

    int predict(const MNISTPicture &);

    void learn(const vector<MNISTPicture> &, double);

private:
    Neuron *hiddenLayerNeuron;
    Neuron *finalLayerNeuron;
    vector<Layer> layers;
    vector<Matrix> activations; // without sigmoid applied
    vector<Matrix> smoothActivations; // with sigmoid applied

    Matrix runNetwork(MNISTPicture);

    void createZeroGradients(vector<Matrix> &weightGradient, vector<Matrix> &biasGradient) const;

    static int getMaxPos(Matrix);

    static Matrix getSolution(int);

    static double costFunction(Matrix &, Matrix &);

    vector<Matrix> getErrors(Matrix &, Matrix &);

    vector<Matrix> getWeightGradient(vector<Matrix> &errors);

    vector<Matrix> getBiasGradient(vector<Matrix> errors);

    static void sumVectors(vector<Matrix> &, vector<Matrix> &);

    static void applyScaleFactor(vector<Matrix> &, double);

    void applyWeightGradients(vector<Matrix>);

    void applyBiasGradients(vector<Matrix>);
};


#endif //NEURALNETWORK_FEEDFORWARDNEURALNET_H
