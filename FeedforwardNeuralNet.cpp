//
// Created by tarak on 12/27/2019.
//

#include <iostream>
#include "FeedforwardNeuralNet.h"
#include "Neuron.h"

FeedforwardNeuralNet::FeedforwardNeuralNet(int *layerHeights, int numLayers) {

    for (int i = 1; i < numLayers; i++) {
        // passing in the arguments of the constructor of the object we want to make is enough
        layers.emplace_back(layerHeights[i - 1], layerHeights[i]);
    }
}

double FeedforwardNeuralNet::costFunction(Matrix diff) { // do I need this?

    double cost = 0;

    for (int r = 0; r < diff.height(); r++) {

        double val = diff(r, 0);
        cost += (val * val) / 2.0;
    }

    return cost;
}

Matrix FeedforwardNeuralNet::getSolution(int i) {

    Matrix ans(1, 10);
    ans(i, 0) = 1;
    return ans;
}

Matrix FeedforwardNeuralNet::runNetwork(MNISTPicture picture) {

    activations.clear();
    smoothActivations.clear();

    Matrix picMat = picture.getData();

    activations.push_back(picMat);
    smoothActivations.push_back(picMat);

    for (int i = 0; i < layers.size(); i++) {

        Matrix newCurr = layers[i].feedforward(smoothActivations.back());
        activations.push_back(newCurr);
        Matrix smoothedCurr = Neuron::tanhFunction(newCurr);
        smoothActivations.push_back(smoothedCurr);
    }

    return smoothActivations.back();
}

int FeedforwardNeuralNet::predict(const MNISTPicture &picture) {
    return getMaxPos(runNetwork(picture));
}

// pre: mat is a column vector
int FeedforwardNeuralNet::getMaxPos(Matrix mat) {

//    cout << mat << endl;
    int maxPos = -1;
    double maxVal = DBL_MIN;
    for (int r = 0; r < mat.height(); r++) {
        double matVal = mat(r, 0);
        if (matVal >= maxVal) {
            maxVal = matVal;
            maxPos = r;
        }
    }

    return maxPos;
}

double FeedforwardNeuralNet::learn(const vector<MNISTPicture> &miniBatch) {

    double totCost = 0;
    vector<Matrix> weightGradient;
    vector<Matrix> biasGradient;

    int numRight = 0;

    for (int i = 0; i < miniBatch.size(); i++) {

        MNISTPicture pic = miniBatch[i];
        Matrix res = runNetwork(pic);

        Matrix ans = getSolution(pic.getClass());
        Matrix diff = res - ans;

        int resDig = getMaxPos(res);
        if (pic.getClass() == resDig) {
            numRight++;
        }

//        cout << "got " <<

        double cost = costFunction(diff);
        totCost += cost;

        vector<Matrix> errors = getErrors(diff);
        sumVectors(weightGradient, getWeightGradient(errors));
        sumVectors(biasGradient, getBiasGradient(errors));
    }

    averageGradient(weightGradient);
    averageGradient(biasGradient);

    applyWeightGradients(weightGradient);
    applyBiasGradients(biasGradient);

//    cout << "finished learning" << endl;
    cout << ((double) numRight / miniBatch.size()) * 100.0 << "% correct" << endl;

    return totCost / miniBatch.size();
}

void FeedforwardNeuralNet::averageGradient(vector<Matrix> &gradient) {
    for (int i = 0; i < gradient.size(); i++) {
        gradient[i] /= gradient.size();
    }
}

vector<Matrix> FeedforwardNeuralNet::getErrors(const Matrix &diff) {

    Matrix activationDelta = Neuron::tanhDerivFunction(activations.back());
    Matrix error = Matrix::scalarMult(diff, activationDelta);

    vector<Matrix> errors;
    errors.push_back(error);

    for (int l = layers.size() - 2; l >= 0; l--) {

        // beware of scope problems?
        Matrix activationDeriv = Neuron::tanhDerivFunction(activations[l + 1]);
        Matrix newError = Matrix::scalarMult(layers[l + 1].weights.transpose() * errors[0], activationDeriv)
                          * activationDeriv; // errors[0] is always the error of the layer in front
        errors.insert(errors.begin(), newError);
    }

    return errors;
}

// pre: a and b have same size
void FeedforwardNeuralNet::sumVectors(vector<Matrix> &a, vector<Matrix> b) {

    for (int i = 0; i < b.size(); i++) {
        if (i >= a.size()) {
            a.push_back(b[i]);
        } else {
            a[i] += b[i];
        }
    }
}

vector<Matrix> FeedforwardNeuralNet::getWeightGradient(vector<Matrix> errors) {

    vector<Matrix> gradients;

    gradients.reserve(layers.size());
    for (int l = 0; l < layers.size(); l++) {

        // note: activations is already index shifted by one to left
        gradients.push_back(errors[l] * smoothActivations[l].transpose());
    }

    return gradients;
}

vector<Matrix> FeedforwardNeuralNet::getBiasGradient(vector<Matrix> errors) {
    vector<Matrix> gradients;

    gradients.reserve(layers.size());
    for (int l = 0; l < layers.size(); l++) {

        // note: activations is already index shifted by one to left
        gradients.push_back(errors[l]); // fixme literally dont need this method
    }

    return gradients;
}

void FeedforwardNeuralNet::applyWeightGradients(vector<Matrix> gradients) {

    for (int l = 0; l < layers.size(); l++) {
        layers[l].weights -= gradients[l];
    }
}

void FeedforwardNeuralNet::applyBiasGradients(vector<Matrix> gradients) {

    for (int l = 0; l < layers.size(); l++) {
        layers[l].biases -= gradients[l];
    }
}
