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

    int width() const;

    int height() const;

    double &operator()(int, int);

    Matrix transpose();

    double getSum();

    static Matrix scalarMult(const Matrix &, const Matrix &); // also called the hardamard product

    void randomize(double, double);

    friend ostream &operator<<(ostream &, const Matrix &);

    Matrix operator+(const Matrix &);

    void operator+=(const Matrix &);

    void operator+=(double);

    Matrix operator-(const Matrix &);

    void operator-=(const Matrix &);

    void operator-=(double);

    Matrix operator*(const Matrix &);

    Matrix operator*(double);

    void operator*=(double);

    void operator/=(double);

    ~Matrix();

private:
    double **data;
    int w;
    int h;
};


#endif //NEURALNETWORK_MATRIX_H
