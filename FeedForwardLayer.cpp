//
// Created by tarak on 12/28/2019.
//

#include "FeedForwardLayer.h"

FeedForwardLayer::FeedForwardLayer(int width, int height)
        : weights(width, height),
          biases(1, width) {
}
