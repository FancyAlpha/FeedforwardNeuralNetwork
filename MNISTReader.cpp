#include "MNISTReader.h"
#include <iostream>
#include <vector>

using namespace std;


vector<MNISTPicture> MNISTReader::getPictures(fstream &pictures, fstream &labels, const int MAX_PICTURES) {

    vector<MNISTPicture> pics;
    if (pictures.is_open() && labels.is_open()) {

        readHeader(pictures, labels);
        pics.reserve(numPictures);

        cout << "There are " << numPictures << " pictures to parse" << endl;
        cout << "Each picture is " << w << "x" << h << " pixels" << endl;
        cout << endl;

        for (int i = 0; i < numPictures && i < MAX_PICTURES; i++) {

            unsigned char label = readByteFromFile(labels);
            MNISTPicture pic(w, h, label);

            for (int j = 0; j < w * h; j++) {

                unsigned char pixel = readByteFromFile(pictures);
                pic.setPixel(j, pixel);
            }

            pics.push_back(pic);
        }
        cout << "finished parsing" << endl;
    } else {
        cout << "unable to parse" << endl;
    }

    return pics;
}


int MNISTReader::width() {

    return w;
}


int MNISTReader::height() {

    return h;
}


int MNISTReader::reverseInt(int i) {

    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int) c1 << 24) + ((int) c2 << 16) + ((int) c3 << 8) + c4;
}


int MNISTReader::readIntFromFile(fstream &file) {

    int val = 0;
    file.read((char *) &val, sizeof(val));
    val = reverseInt(val);
    return val;
}


unsigned char MNISTReader::readByteFromFile(fstream &file) {

    unsigned char val = 0;
    file.read((char *) &val, sizeof(val));
    return val;
}


void MNISTReader::readHeader(fstream &pictures, fstream &labels) {

    picMagicNum = readIntFromFile(pictures);
    labMagicNum = readIntFromFile(labels);

    if (picMagicNum != 2051 || labMagicNum != 2049) {
        cerr << "picture and label files' magic number do not correspond to each other: "
             << "pictures file: " << picMagicNum << ", labels file: " << labMagicNum << endl;
    }

    numPictures = readIntFromFile(pictures);
    int numLabels = readIntFromFile(labels);

    if (numPictures != numLabels) {
        cout << "incorrect number of pictures! " << numPictures << " vs " << numLabels;
    }

    h = readIntFromFile(pictures);
    w = readIntFromFile(pictures);
}