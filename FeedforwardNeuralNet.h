//
// Created by tarak on 12/27/2019.
//

#ifndef NEURALNETWORK_FEEDFORWARDNEURALNET_H
#define NEURALNETWORK_FEEDFORWARDNEURALNET_H


#include <vector>
#include "Layer.h"
#include "MNISTPicture.h"

class FeedforwardNeuralNet {

public:
    FeedforwardNeuralNet(int *, int);

    int predict(const MNISTPicture &);

    double learn(const vector<MNISTPicture> &, double);

private:
    vector<Layer> layers;
    vector<Matrix> activations; // without sigmoid applied
    vector<Matrix> smoothActivations; // with sigmoid applied
    Matrix runNetwork(MNISTPicture);

    static int getMaxPos(Matrix);

    static double costFunction(Matrix);

    static Matrix getSolution(int);

    vector<Matrix> getErrors(const Matrix &);

    vector<Matrix> getWeightGradient(vector<Matrix> errors);

    vector<Matrix> getBiasGradient(vector<Matrix> errors);

    void applyWeightGradients(vector<Matrix>);

    void applyBiasGradients(vector<Matrix>);

    static void sumVectors(vector<Matrix> &, vector<Matrix>);

    static void applyScaleFactor(vector<Matrix> &, double);
};


#endif //NEURALNETWORK_FEEDFORWARDNEURALNET_H
