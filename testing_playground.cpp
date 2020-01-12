#include <iostream>
#include "Matrix.h"
#include "Layer.h"

int main() {

    // simulate 3, 2, 1 neuron network
//    Layer a1(786, 6);
////    Layer a2(2, 1);
//
//    Matrix activation1(1, 786);
//    activation1.set(0, 0, 1);
//    activation1.set(1, 0, 1);
//    activation1.set(2, 0, 1);
//    cout << "input" << endl << activation1 << endl;
//
//    cout << "layer 1 weights" << endl;
//    cout << a1.weights << endl;
//    cout << "layer 1 biases" << endl;
//    cout << a1.biases << endl;
//
//    cout << "feedforward forced step" << endl;
//    Matrix res = a1.weights * activation1;
//    cout << res.w() << "x" << res.h() << " matrix" << endl;
//    cout << res << endl;
//
//
//    Matrix activation2 = a1.feedforward(activation1);
//    cout << "post layer 1" << endl << activation2 << endl;

    Matrix a(3, 3);
    Matrix b(3, 3);

    a(0, 0) = 1;
    a(0, 1) = 2;
    a(0, 2) = 3;
    a(1, 0) = 4;
    a(1, 1) = 5;
    a(1, 2) = 6;
    a(2, 1) = -1;

    b(0, 0) = 2;
    b(0, 1) = 0;
    b(1, 0) = 2;
    b(2, 1) = -1;

    cout << a << endl;
    cout << b << endl;
    Matrix c = a;
//    c(0, 0) = -1;
    c += b;
    cout << c << endl;

    return 0;
}