//
//  weights.h
//  Submarine
//
//  Created by Florian Denis on 10/16/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#ifndef Submarine_weights_h
#define Submarine_weights_h

#include <opencv2/core/core.hpp>

/**
 *  Compute Local Contrast weight
 *  @param I    Input cv::Mat of type CV_8UC3
 *  @param dst  Destination image. Needs to be of type CV_32FC1 and same size as I
 */
void computeLCWeight(const cv::Mat& I,cv::Mat& dst);

/**
 *  Compute Saliency weight
 *  @param I    Input cv::Mat of type CV_8UC3
 *  @param dst  Destination image. Needs to be of type CV_32FC1 and same size as I
 */
void computeSWeight(const cv::Mat& I,cv::Mat& dst);

#endif
