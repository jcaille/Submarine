//
//  utils.h
//  Submarine
//
//  Created by Florian Denis on 10/16/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#ifndef Submarine_utils_h
#define Submarine_utils_h

#include <opencv2/core/core.hpp>

/**
 *  floatTo8u converts a CV_32F image to a CV_8U one for display purposes
 */
cv::Mat floatTo8U(const cv::Mat& I);

#endif
