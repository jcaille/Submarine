//
//  WhiteBalance.h
//  Submarine
//
//  Created by Jean Caillé on 20/10/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#ifndef __Submarine__WhiteBalance__
#define __Submarine__WhiteBalance__

#include <iostream>
#include <opencv2/core/core.hpp>

/**
 *  Compute White balance fusion input
 *  @param I    Input cv::Mat of type CV_8UC3
 *  @param dst  Destination image. Needs to be of same type and size as I
 */
void whiteBalanceInput(cv::Mat I, double lambda, cv::Mat dst);

#endif /* defined(__Submarine__WhiteBalance__) */
