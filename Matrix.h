//
// Created by tarak on 12/26/2019.
//

#ifndef NEURALNETWORK_MATRIX_H
#define NEURALNETWORK_MATRIX_H

#include <ostream>

using namespace std;

class Matrix {
public:
    Matrix(int width, int height);

    Matrix(const Matrix &);

    int height();

    int width();

    void set(int r, int c, char v);

    Matrix operator+(const Matrix&);

    Matrix operator*(const Matrix&);

    friend ostream &operator<<(ostream &, const Matrix &);

    ~Matrix();

private:
    double **data;
    int w;
    int h;
};


#endif //NEURALNETWORK_MATRIX_H
