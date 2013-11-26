//
//  fusion.h
//  Submarine
//
//  Created by Jean Caillé on 11/11/2013.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#ifndef __Submarine__fusion__
#define __Submarine__fusion__

#include <opencv2/core/core.hpp>

void naiveFusion(const std::vector<cv::Mat>& inputs, const std::vector<cv::Mat>& weights, cv::Mat& dst);
void laplacianFusion(const std::vector<cv::Mat>& inputs, const std::vector<cv::Mat>& weights, cv::Mat& dst);

#endif /* defined(__Submarine__fusion__) */
