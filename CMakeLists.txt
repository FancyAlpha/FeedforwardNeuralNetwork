cmake_minimum_required(VERSION 3.15)
project(NeuralNetwork)

set(CMAKE_CXX_STANDARD 14)

add_executable(NeuralNetwork main.cpp MNISTReader.cpp MNISTReader.h Matrix.cpp Matrix.h FeedforwardNeuralNet.cpp FeedforwardNeuralNet.h MNISTPicture.cpp MNISTPicture.h Neuron.cpp Neuron.h Layer.cpp Layer.h)