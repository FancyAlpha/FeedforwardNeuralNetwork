//
// Created by tarak on 12/26/2019.
//

#include <iomanip>
#include <iostream>
#include "Matrix.h"
#include "Randomizer.h"


// pre: width_ > 0, height_ > 0
Matrix::Matrix(int width_, int height_) {

    if (width_ < 1 || height_ < 1) {
        cout << "Matrix cannot be initialized to dimensions: " << width_ << "x" << height_ << endl;
    }

    w = width_;
    h = height_;

    data = new double *[height_];
    data[0] = new double[width_ * height_]();

    for (int r = 0; r < height_; r++) {
        data[r] = data[0] + (r * w);
    }
}

Matrix::Matrix(const Matrix &other) {
    w = other.w;
    h = other.h;

    data = new double *[h];
    data[0] = new double[w * h]();

    for (int r = 0; r < h; r++) {
        data[r] = data[0] + r * w;

        for (int c = 0; c < w; c++) {
            this->data[r][c] = other.data[r][c];
        }
    }
}

int Matrix::width() const {
    return w;
}

int Matrix::height() const {
    return h;
}

double &Matrix::operator()(int r, int c) {
    return data[r][c];
}

Matrix Matrix::transpose() {
    Matrix res(h, w);

    for (int r = 0; r < res.h; r++) {
        for (int c = 0; c < res.w; c++) {
            res(r, c) = this->data[c][r];
        }
    }

    return res;
}

double Matrix::getSum() {
    double sum = 0;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            sum += data[r][c];
        }
    }

    return sum;
}

Matrix Matrix::scalarMult(const Matrix &a, const Matrix &b) {

    if (a.w != b.w || a.h != b.h) {
        cout << "Matrix (.) operation invalid: " << a.w << "x" << a.h << " times " << b.w << "x" << b.h << endl;
    }

    Matrix res(a.w, a.h);

    for (int r = 0; r < a.h; r++) {
        for (int c = 0; c < a.w; c++) {
            res.data[r][c] = a.data[r][c] * b.data[r][c];
        }
    }

    return res;
}


void Matrix::randomize(Randomizer *random) {

    int seed = time(nullptr);
    srand(seed);

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            data[r][c] = random->getRandom();
        }
    }
}

ostream &operator<<(ostream &os, const Matrix &other) {

    for (int r = 0; r < other.h; r++) {
        os << '|';
        for (int c = 0; c < other.w; c++) {
            os << std::setw(5) << roundf(other.data[r][c] * 100) / 100;
        }

        os << '|' << endl;
    }

    return os;
}

// pre: w and h of other matrix is same as this one's
Matrix Matrix::operator+(const Matrix &other) {

    if (this->w != other.w || this->h != other.h) {
        cout << "Matrix + operation invalid: " << this->w << "x" << this->h << " plus " << other.w << "x" << other.h
             << endl;
    }

    Matrix res(this->w, this->h);

    for (int r = 0; r < this->h; r++) {
        for (int c = 0; c < this->w; c++) {
            res(r, c) = this->data[r][c] + other.data[r][c];
        }
    }

    return res;
}


void Matrix::operator+=(const Matrix &other) {

    if (this->w != other.w || this->h != other.h) {
        cout << "Matrix += operation invalid: " << this->w << "x" << this->h << " plus " << other.w << "x" << other.h
             << endl;
    }

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            data[r][c] += other.data[r][c];
        }
    }
}

void Matrix::operator+=(double off) {

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            data[r][c] += off;
        }
    }
}

// pre: w and h of other matrix is same as this one's
Matrix Matrix::operator-(const Matrix &other) {

    if (this->w != other.w || this->h != other.h) {
        cout << "Matrix - operation invalid: " << this->w << "x" << this->h << " minus " << other.w << "x" << other.h
             << endl;
    }

    Matrix res(this->w, this->h);

    for (int r = 0; r < this->h; r++) {
        for (int c = 0; c < this->w; c++) {
            res.data[r][c] = this->data[r][c] - other.data[r][c];
        }
    }

    return res;
}

void Matrix::operator-=(const Matrix &other) {

    if (this->w != other.w || this->h != other.h) {
        cout << "Matrix -= operation invalid: " << this->w << "x" << this->h << " minus " << other.w << "x" << other.h
             << endl;
    }

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            data[r][c] -= other.data[r][c];
        }
    }
}

void Matrix::operator-=(double off) {

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            data[r][c] -= off;
        }
    }
}

// pre: w of this must equal h of other
Matrix Matrix::operator*(const Matrix &other) {

    if (this->w != other.h) {
        cout << "Matrix * operation invalid: " << this->w << "x" << this->h << " into " << other.w << "x" << other.h
             << endl;
    }

    Matrix res(other.w, this->h);

    for (int r = 0; r < res.h; r++) {
        for (int c = 0; c < res.w; c++) {

            double sum = 0;
            // take the dot product of this matrix's row at r and other's column at c
            for (int i = 0; i < this->w; i++) {
                sum += this->data[r][i] * other.data[i][c];
            }

            res.data[r][c] = sum;
        }
    }

    return res;
}

Matrix Matrix::operator*(double off) {

    Matrix res(w, h);

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            res.data[r][c] = this->data[r][c] + off;
        }
    }
    return res;
}

void Matrix::operator*=(double off) {


    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            data[r][c] *= off;
        }
    }
}

void Matrix::operator/=(double off) {


    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            data[r][c] /= off;
        }
    }
}

Matrix::~Matrix() {
    delete[] data[0];
    delete[] data;
}
