//
// Created by tarak on 1/15/2020.
//

#include <cstdlib>
#include "Randomizer.h"


RegularRandom::RegularRandom(int seed, double min, double max) {

    srand(seed);
    this->min = min;
    this->max = max;
}


double RegularRandom::getRandom() {

    return ((((double) rand()) / RAND_MAX) * (max - min)) - max;
}


NormalRandom::NormalRandom(int seed, double mean, double trueVariance) {

    srand(seed);
    this->mean = mean;
    this->adjustedVariance = 1.0 / sqrt(trueVariance);
}


double NormalRandom::getRandom() {

    double x = (double) rand() / RAND_MAX;
    double adjustedX = (x - mean) * adjustedVariance;
    return (STD_ADJUSTED_VARIANCE * adjustedVariance) * exp(-0.5 * adjustedX * adjustedX);
}
