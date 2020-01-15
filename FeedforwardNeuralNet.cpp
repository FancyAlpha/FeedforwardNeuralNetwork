//
// Created by tarak on 12/27/2019.
//

#include <iostream>
#include "FeedforwardNeuralNet.h"
#include "Neuron.h"


FeedforwardNeuralNet::FeedforwardNeuralNet(const int *layerHeights, int numLayers, Neuron *hidden, Neuron *fin) {

    hiddenLayerNeuron = hidden;
    finalLayerNeuron = fin;

    for (int i = 1; i < numLayers; i++) {
        // passing in the arguments of the constructor of the object we want to make is enough
        layers.emplace_back(layerHeights[i - 1], layerHeights[i], i != 1);
    }
}


int FeedforwardNeuralNet::predict(const MNISTPicture &picture) {

    return getMaxPos(runNetwork(picture));
}


void FeedforwardNeuralNet::learn(const vector<MNISTPicture> &miniBatch, double learningRate) {

    vector<Matrix> weightGradient;
    vector<Matrix> biasGradient;

    createZeroGradients(weightGradient, biasGradient);

    for (int i = 0; i < miniBatch.size(); i++) {

        MNISTPicture pic = miniBatch[i];
        Matrix res = runNetwork(pic);
        Matrix ans = getSolution(pic.getClass());

        vector<Matrix> errors = getErrors(res, ans);

        vector<Matrix> newWeightGradient = getWeightGradient(errors);
        vector<Matrix> newBiasGradient = getBiasGradient(errors);

        sumVectors(weightGradient, newWeightGradient);
        sumVectors(biasGradient, newBiasGradient);
    }

    applyScaleFactor(weightGradient, learningRate / miniBatch.size());
    applyScaleFactor(biasGradient, learningRate / miniBatch.size());

    applyWeightGradients(weightGradient);
    applyBiasGradients(biasGradient);
}


Matrix FeedforwardNeuralNet::runNetwork(MNISTPicture picture) {

    activations.clear();
    smoothActivations.clear();

    Matrix picMat = picture.getData();
    smoothActivations.push_back(picMat);

    for (int i = 0; i < layers.size(); i++) {

        Matrix newCurr = layers[i].feedforward(smoothActivations.back());
        activations.push_back(newCurr);

        Neuron *activeNeuron = i < layers.size() - 1 ? hiddenLayerNeuron : finalLayerNeuron;

        Matrix smoothedCurr = activeNeuron->activation(newCurr);
        smoothActivations.push_back(smoothedCurr);
    }


    return smoothActivations.back();
}


void FeedforwardNeuralNet::createZeroGradients(vector<Matrix> &weightGradient,
                                               vector<Matrix> &biasGradient) const {// initialize deltas to zero first
    for (int i = 0; i < this->layers.size(); i++) {
        weightGradient.emplace_back(this->layers[i].weights.width(), this->layers[i].weights.height());
        biasGradient.emplace_back(this->layers[i].biases.width(), this->layers[i].biases.height());
    }
}


// pre: mat is a column vector
int FeedforwardNeuralNet::getMaxPos(Matrix mat) {

    int maxPos = -1;
    double maxVal = DBL_MIN;
    for (int r = 0; r < mat.height(); r++) {
        double matVal = mat(r, 0);
        if (matVal > maxVal) {
            maxVal = matVal;
            maxPos = r;
        }
    }

    return maxPos;
}


Matrix FeedforwardNeuralNet::getSolution(int i) {

    Matrix ans(1, 10);
    ans(i, 0) = 1;
    return ans;
}


double FeedforwardNeuralNet::costFunction(Matrix &res, Matrix &ans) {

    Matrix diff = res - ans;
    double cost = 0;

    for (int r = 0; r < diff.height(); r++) {

        double val = diff(r, 0);
        cost += val * val;
    }

    return cost / 2.0;
}


vector<Matrix> FeedforwardNeuralNet::getErrors(Matrix &res, Matrix &ans) {

    Matrix activationDelta = hiddenLayerNeuron->activationPrime(activations.back());

    Matrix error = Matrix::scalarMult(res - ans, activationDelta);


    vector<Matrix> errors;
    errors.push_back(error);

    for (int l = layers.size() - 2; l >= 0; l--) {

        Matrix activationDeriv = hiddenLayerNeuron->activationPrime(activations[l]);

        // errors[0] is always the error of the layer in front
        Matrix newError = Matrix::scalarMult(layers[l + 1].weights.transpose() * errors.front(), activationDeriv);
        errors.insert(errors.begin(), newError);
    }

    return errors;
}


vector<Matrix> FeedforwardNeuralNet::getWeightGradient(vector<Matrix> &errors) {

    vector<Matrix> gradients;

    gradients.reserve(layers.size());
    for (int l = 0; l < layers.size(); l++) {

        // note: activations is already index shifted by one to left
        gradients.push_back(errors[l] * smoothActivations[l].transpose());
    }

    return gradients;
}


vector<Matrix> FeedforwardNeuralNet::getBiasGradient(vector<Matrix> errors) {

    return errors;
}


// pre: a and b have same size
void FeedforwardNeuralNet::sumVectors(vector<Matrix> &a, vector<Matrix> &b) {

    if (a.size() != b.size()) {
        cout << "cannot sum gradients of size " << a.size() << " and  " << b.size() << endl;
    }

    for (int i = 0; i < b.size(); i++) {
        a[i] += b[i];
    }
}


void FeedforwardNeuralNet::applyScaleFactor(vector<Matrix> &gradient, double scale) {

    for (int i = 0; i < gradient.size(); i++) {
        gradient[i] *= scale;
    }
}


void FeedforwardNeuralNet::applyWeightGradients(vector<Matrix> gradients) {

    if (gradients.size() != layers.size()) {
        cout << "cannot apply weight gradient of size " << gradients.size() << " and  " << layers.size() << endl;
    }

    for (int l = 0; l < layers.size(); l++) {
        layers[l].weights -= gradients[l];
    }
}


void FeedforwardNeuralNet::applyBiasGradients(vector<Matrix> gradients) {

    if (gradients.size() != layers.size()) {
        cout << "cannot apply bias gradient of size " << layers.size() << " and  " << layers.size() << endl;
    }

    for (int l = 0; l < layers.size(); l++) {
        layers[l].biases -= gradients[l];
    }
}
