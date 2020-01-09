//
// Created by tarak on 12/26/2019.
//

#include <iomanip>
#include <iostream>
#include "Matrix.h"

// pre: width_ > 0, height_ > 0
Matrix::Matrix(int width_, int height_) {
    w = width_;
    h = height_;

    data = new double *[height_];
    data[0] = new double[width_ * height_]();

    for (int r = 1; r < height_; r++) {
        data[r] = data[0] + r * w;
    }
}

Matrix::Matrix(const Matrix &other) {
    w = other.w;
    h = other.h;

    data = new double *[h];
    data[0] = new double[w * h]();

    for (int r = 1; r < h; r++) {
        data[r] = data[0] + r * w;

        for (int c = 0; c < w; c++) {
            this->data[r][c] = other.data[r][c];
        }
    }
}

// pre: w of this must equal h of other
Matrix Matrix::operator*(const Matrix &other) {

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

// pre: w and h of other matrix is same as this one's
Matrix Matrix::operator+(const Matrix &other) {

    Matrix res(this->w, this->h);

    for (int r = 0; r < this->h; r++) {
        for (int c = 0; c < this->w; c++) {
            res.data[r][c] = this->data[r][c] + other.data[r][c];
        }
    }

    return res;
}

// pre: w and h of other matrix is same as this one's
Matrix Matrix::operator-(const Matrix &other) {

    Matrix res(this->w, this->h);

    for (int r = 0; r < this->h; r++) {
        for (int c = 0; c < this->w; c++) {
            res.data[r][c] = this->data[r][c] - other.data[r][c];
        }
    }

    return res;
}

int Matrix::height() const {
    return h;
}

int Matrix::width() const {
    return w;
}

ostream &operator<<(ostream &os, const Matrix &other) {

    for (int r = 0; r < other.h; r++) {
        os << '|';
        for (int c = 0; c < other.w; c++) {
            os << std::setw(5) << roundf(other.data[r][c] * 100) / 100;
//            os << std::setw(5) << other.data[r][c];
        }

        os << '|' << endl;
    }

    return os;
}

Matrix::~Matrix() {

//    for (int r = 0; r < h; r++) {
//        delete[] data[r];
//    }
//
//    delete[] data;

    delete[] data[0];
    delete[] data;
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

void Matrix::operator+=(const Matrix &other) {

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

void Matrix::operator-=(double off) {

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            data[r][c] -= off;
        }
    }
}

Matrix Matrix::scalarMult(const Matrix &a, const Matrix &b) {

    Matrix res(a.w, a.h);

    for (int r = 0; r < a.h; r++) {
        for (int c = 0; c < a.w; c++) {
            res.data[r][c] = a.data[r][c] * b.data[r][c];
        }
    }

    return res;
}

Matrix Matrix::transpose() {
    Matrix res(h, w);

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            res.data[c][r] = data[r][c];
        }
    }

    return res;
}

bool Matrix::isNan() {
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (_isnan(data[c][r])) return true;
        }
    }

    return false;
}

void Matrix::operator-=(const Matrix &other) {
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            data[r][c] -= other.data[r][c];
        }
    }
}

double &Matrix::operator()(int r, int c) {
    return data[r][c];
}
