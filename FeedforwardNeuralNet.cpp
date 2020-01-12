//
// Created by tarak on 12/27/2019.
//

#include <iostream>
#include "FeedforwardNeuralNet.h"
#include "Neuron.h"

FeedforwardNeuralNet::FeedforwardNeuralNet(int *layerHeights, int numLayers) {

    for (int i = 1; i < numLayers; i++) {
        // passing in the arguments of the constructor of the object we want to make is enough
        layers.emplace_back(layerHeights[i - 1], layerHeights[i], i != 1);
    }
}

double FeedforwardNeuralNet::costFunction(Matrix diff) { // do I need this?

    double cost = 0;

    for (int r = 0; r < diff.height(); r++) {

        double val = diff(r, 0);
        cost += val * val;
    }

    return cost / 2.0;
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

//    activations.push_back(picMat);
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

double FeedforwardNeuralNet::learn(const vector<MNISTPicture> &miniBatch, double learningRate) {

    double totCost = 0;
    vector<Matrix> weightGradient;
    vector<Matrix> biasGradient;

    // initialize deltas to zero first
    for (int i = 0; i < layers.size(); i++) {
        weightGradient.emplace_back(layers[i].weights.width(), layers[i].weights.height());
        biasGradient.emplace_back(layers[i].biases.width(), layers[i].biases.height());
    }

    int numRight = 0;

    for (int i = 0; i < miniBatch.size(); i++) {

        MNISTPicture pic = miniBatch[i];
        Matrix res = runNetwork(pic);

        int resDig = getMaxPos(res);
        if (pic.getClass() == resDig)
            numRight++;

        Matrix ans = getSolution(pic.getClass());

        // fixme these two lines should be in one function (in case cost function changes later)
        Matrix diff = res - ans;
        double cost = costFunction(diff);

        totCost += cost;

//        cout << "i: " << i << ", " << diff.getSum() << endl;


        vector<Matrix> errors = getErrors(diff);

        if (errors.size() != layers.size()) {
            cout << "errors size is not same as number of layers : " << errors.size() << " vs  " << layers.size()
                 << endl;
        }

        vector<Matrix> newWeightGradient = getWeightGradient(errors);
        vector<Matrix> newBiasGradient = getBiasGradient(errors);


//        for (int i = 0; i < weightGradient.size(); i++) {
////            cout << "er: " << errors[i].getSum() << endl;
//            cout << "wb: " << weightGradient[i].getSum() << endl;
//        }

        sumVectors(weightGradient, newWeightGradient);
        sumVectors(biasGradient, newBiasGradient);

//        for (int i = 0; i < weightGradient.size(); i++) {
//            cout << "wa: " << weightGradient[i].getSum() << endl;
//        }
    }

//    for (int i = 0; i < weightGradient.size(); i++) {
//        cout << "wb: " << weightGradient[i].getSum() << endl;
//    }

    applyScaleFactor(weightGradient, learningRate / miniBatch.size());
    applyScaleFactor(biasGradient, learningRate / miniBatch.size());

//    for (int i = 0; i < weightGradient.size(); i++) {
//        cout << "wa: " << weightGradient[i].getSum() << endl;
//    }

    applyWeightGradients(weightGradient);
    applyBiasGradients(biasGradient);

//    cout << (((double) numRight) / miniBatch.size()) * 100.0 << "% correct" << endl;

    return totCost / miniBatch.size();
}

void FeedforwardNeuralNet::applyScaleFactor(vector<Matrix> &gradient, double scale) {
    for (int i = 0; i < gradient.size(); i++) {
        gradient[i] *= scale;
    }
}

vector<Matrix> FeedforwardNeuralNet::getErrors(const Matrix &diff) {

    Matrix activationDelta = Neuron::tanhDerivFunction(activations.back());
//    cout << activationDelta.getSum() << endl;
    Matrix error = Matrix::scalarMult(diff, activationDelta);

//    cout << "new err: " << error.getSum() << endl;

    vector<Matrix> errors;
    errors.push_back(error);

    for (int l = layers.size() - 2; l >= 0; l--) {

        // beware of scope problems?
//        cout << "z: " << l << endl << activations[l + 1] << endl;

        Matrix activationDeriv = Neuron::tanhDerivFunction(activations[l]);

//        cout << "dz: " << l << endl << activationDeriv << endl;
//        cout << "ly: " << l + 1 << endl << (layers[l + 1].weights.transpose() * errors[0]) << endl;

        // errors[0] is always the error of the layer in front
        Matrix newError = Matrix::scalarMult(layers[l + 1].weights.transpose() * errors.front(), activationDeriv);

//        cout << "NEW ERR: " << endl
//             << newError
//             << endl << newError.getSum() << endl;
        errors.insert(errors.begin(), newError);
    }

    return errors;
}

// pre: a and b have same size
void FeedforwardNeuralNet::sumVectors(vector<Matrix> &a, vector<Matrix> b) {

    if (a.size() != b.size()) {
        cout << "cannot sum gradients of size " << a.size() << " and  " << b.size() << endl;
    }

    for (int i = 0; i < b.size(); i++) {
        a[i] += b[i];
    }
}

vector<Matrix> FeedforwardNeuralNet::getWeightGradient(vector<Matrix> errors) {

    vector<Matrix> gradients;

    gradients.reserve(layers.size());
    for (int l = 0; l < layers.size(); l++) {

        // note: activations is already index shifted by one to left
        gradients.push_back(errors[l] * smoothActivations[l].transpose()); // fixme this must be wrong
//        cout << "er: " << errors[l].getSum() << endl;
//        cout << "sa: " << smoothActivations[l].getSum() << endl;
//        cout << "at: " << smoothActivations[l].transpose().getSum() << endl;
//        cout << "ng: " << gradients.back().getSum() << endl;
//        cout << "---" << endl;
    }

    return gradients;
}

vector<Matrix> FeedforwardNeuralNet::getBiasGradient(vector<Matrix> errors) {
    vector<Matrix> gradients;

    gradients.reserve(layers.size());
    for (int l = 0; l < layers.size(); l++) {

        // note: activations is already index shifted by one to left
        gradients.push_back(errors[l]); // fixme literally dont need this method?
    }

    return gradients;
}

void FeedforwardNeuralNet::applyWeightGradients(vector<Matrix> gradients) {

    if (gradients.size() != layers.size()) {
        cout << "cannot apply weight gradient of size " << gradients.size() << " and  " << layers.size() << endl;
    }

    for (int l = 0; l < layers.size(); l++) {
//        double b4 = layers[l].weights.getSum();
        layers[l].weights -= gradients[l];
//        double a5 = layers[l].weights.getSum();

//        cout << "dw" << l << ": " << b4 - a5 << endl;
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
