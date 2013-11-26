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

/**
 *  Compute Exposedness weight
 *  @param I    Input cv::Mat of type CV_8UC3
 *  @param dst  Destination image. Needs to be of type CV_32FC1 and same size as I
 */
void computeEWeight(const cv::Mat& I,cv::Mat& dst);


/**
 *  Compute Laplacian weight
 *  @param I    Input cv::Mat of type CV_8UC3
 *  @param dst  Destination image. Needs to be of type CV_32FC1 and same size as I
 */
void computeLWeight(const cv::Mat& I,cv::Mat& dst);

/**
 *  Normalise the weight maps so that the sum of each pixels adds up to 1
 *
 *  @param maps std::vector containing all the maps. They need to be of the same size, type CV_32FC1
 */
void normalizeWeightMaps(std::vector<cv::Mat>& maps);


#endif
