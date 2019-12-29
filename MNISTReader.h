//
// Created by tarak on 12/26/2019.
//

#ifndef NEURALNETWORK_MNISTREADER_H
#define NEURALNETWORK_MNISTREADER_H

#include <fstream>
#include <vector>
#include "MNISTPicture.h"

using namespace std;

class MNISTReader {

public:
    vector<MNISTPicture> getPictures(fstream &, fstream &);

private:
    int picMagicNum;
    int labMagicNum;
    int numPictures;
    int width;
    int height;

    static int reverseInt(int);

    void readHeader(fstream &, fstream &);

    static int readIntFromFile(fstream &file);

    static unsigned char readByteFromFile(fstream &file);

};


#endif //NEURALNETWORK_MNISTREADER_H
