//
// Created by tarak on 1/15/2020.
//

#ifndef NEURALNETWORK_RANDOMIZER_H
#define NEURALNETWORK_RANDOMIZER_H

# define M_PI           3.14159265358979323846
# define M_E            2.71828182845904523536


class Randomizer {

public:
    virtual double getRandom() = 0;
};


class RegularRandom : public Randomizer {

public:
    RegularRandom(int seed, double min, double max);
    double getRandom() override;
private:
    double min;
    double max;
};


class NormalRandom : public Randomizer {

public:
    explicit NormalRandom(int seed, double mean = 0, double trueVariance = 1);
    double getRandom() override;
private:
    double mean;
    double adjustedVariance;

    constexpr static const double STD_ADJUSTED_VARIANCE = 0.3989422804;
};


#endif //NEURALNETWORK_RANDOMIZER_H
