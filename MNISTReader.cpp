#include "MNISTReader.h"
#include <iostream>
#include <vector>

using namespace std;

int MNISTReader::reverseInt(int i) {
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int) c1 << 24) + ((int) c2 << 16) + ((int) c3 << 8) + c4;
}

vector<MNISTPicture> MNISTReader::getPictures(fstream &pictures, fstream &labels) {

    vector<MNISTPicture> pics;
    if (pictures.is_open() && labels.is_open()) {

        readHeader(pictures, labels);

        cout << "There are " << numPictures << " pictures to parse" << endl;
        cout << "Each picture is " << width << "x" << height << " pixels" << endl;
        cout << endl;

        for (int i = 0; i < numPictures; i++) {

            unsigned char label = readByteFromFile(labels);
            MNISTPicture pic(width, height, label);

            for (int j = 0; j < width * height; j++) {

                unsigned char pixel = readByteFromFile(pictures);
                pic.setPixel(j, pixel);
            }

//            cout << "digit @ " << i << ", label: " << (int)label << endl;
//            cout << pic;
            pics.push_back(pic);
        }
        cout << "finished parsing" << endl;
    } else {
        cout << "unable to parse" << endl;
    }

    return pics;
}

void MNISTReader::readHeader(fstream &pictures, fstream &labels) {

    picMagicNum = readIntFromFile(pictures);
    labMagicNum = readIntFromFile(labels);

    // todo do check for magic number here?

    numPictures = readIntFromFile(pictures);

    int numLabels = readIntFromFile(labels);
    if (numPictures != numLabels) {
        cout << "incorrect number of pictures! " << numPictures << " vs " << numLabels;
    }

    height = readIntFromFile(pictures);
    width = readIntFromFile(pictures);
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
