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
    for (int i = 0; i < height_; i++) {
        data[i] = new double[width_](); // making an array of arrays
    }
}

Matrix::Matrix(const Matrix &other) {
    w = other.w;
    h = other.h;

    this->data = new double *[h];
    for (int r = 0; r < h; r++) {
        data[r] = new double[w];

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
//            cout << sum << endl;
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

void Matrix::set(int r, int c, double v) {
    data[r][c] = v;
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

    if (data != nullptr) {
//        cout << "deleting matrix... ";
        for (int r = 0; r < h; r++) {
            delete[] data[r];
        }

        delete[] data;
        data = nullptr; // do I need this?
//        cout << "finished" << endl;
    }
}

double Matrix::get(int r, int c) {
    return data[r][c];
}

