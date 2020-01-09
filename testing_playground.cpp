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
//    cout << res.width() << "x" << res.height() << " matrix" << endl;
//    cout << res << endl;
//
//
//    Matrix activation2 = a1.feedforward(activation1);
//    cout << "post layer 1" << endl << activation2 << endl;

    Matrix a(2, 2);
    Matrix b(2, 2);

//    a.set(0, 0, -1);
//    a.set(0, 1, -2);
//    a.set(1, 0, -2);
//    a.set(1, 1, -1);
//
//    b.set(0, 0, 2);
//    b.set(0, 1, 0);
//    b.set(1, 0, 2);
//    b.set(1, 1, -1);

    cout << a << endl;
    cout << b << endl;
    cout << a * b << endl;

    return 0;
}