//
// Created by tarak on 12/27/2019.
//

#ifndef NEURALNETWORK_MNISTPICTURE_H
#define NEURALNETWORK_MNISTPICTURE_H


#include "Matrix.h"

class MNISTPicture {
public:
    MNISTPicture(int, int, int);

    friend ostream &operator<<(ostream &, const MNISTPicture &);

    int height();

    int width();

    void setPixel(int i, unsigned char val);

    int getClass();

    ~MNISTPicture();

private:
    double *data; // will be given as chars, needs to be converted?
    int w;
    int h;

    int classification;
};


#endif //NEURALNETWORK_MNISTPICTURE_H
