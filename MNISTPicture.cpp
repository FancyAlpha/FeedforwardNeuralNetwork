//
// Created by tarak on 12/27/2019.
//

#include "MNISTPicture.h"

MNISTPicture::MNISTPicture(int width_, int height_, int classification_) {
    this->w = width_;
    this->h = height_;
    this->classification = classification_;

    this->data = new double[width_ * height_](); // () ensures that every value here is a zero to begin with
}

void MNISTPicture::setPixel(int i, unsigned char val) {
    data[i] = val / 255.0; // normalize pixel value here
}

MNISTPicture::MNISTPicture(const MNISTPicture &other) {
    w = other.w;
    h = other.h;
    classification = other.classification;

    this->data = new double[w * h];
    for (int i = 0; i < w * h; i++) {
        this->data[i] = other.data[i];
    }
}

ostream &operator<<(ostream &os, const MNISTPicture &pic) {

    for (int c = 0; c < pic.w; c++) {
        os << '-';
    }

    os << endl;

    for (int r = 0; r < pic.h; r++) {
        for (int c = 0; c < pic.w; c++) {

            int i = (r * pic.w) + c;
            if (pic.data[i] > 0.5) {
                os << 'o';
            } else if (pic.data[i] > 0) {
                os << '.';
            } else {
                os << ' ';
            }
        }

        os << endl;
    }

    for (int c = 0; c < pic.w; c++) {
        os << '-';
    }
    os << endl;

    return os;
}

int MNISTPicture::height() {
    return this->h;
}

int MNISTPicture::width() {
    return this->w;
}

MNISTPicture::~MNISTPicture() {
    delete[] data;
    data = nullptr;
}

int MNISTPicture::getClass() {
    return classification;
}

//void MNISTPicture::setClass(int val) {
//    this->classification = val;
//}

