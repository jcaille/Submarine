//
//  colorimetry.h
//  Submarine
//
//  Created by Jean Caillé on 20/10/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#ifndef __Submarine__WhiteBalance__
#define __Submarine__WhiteBalance__

#include <opencv2/core/core.hpp>

/**
 *  Apply white balance correction to image
 *  @param I    Input cv::Mat of type CV_8UC3
 *  @param dst  Destination image. Needs to be of same type and size as I
 */
void whiteBalance(const cv::Mat& I, cv::Mat& dst, double lambda = 0.2);

/**
 *  Contrast enhancement of color images using CLAHE technique
 *
 *  @param I   Input cv::Mat of type CV_8UC3
 *  @param dst Destination image. Needs to be of same type and size as I
 */
void enhanceContrast(const cv::Mat& I, cv::Mat& dst);


#endif /* defined(__Submarine__WhiteBalance__) */
