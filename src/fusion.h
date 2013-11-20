//
//  fusion.h
//  Submarine
//
//  Created by Jean Caillé on 11/11/2013.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#ifndef __Submarine__fusion__
#define __Submarine__fusion__

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>

void fuseInputs(std::vector<cv::Mat> inputs, std::vector<cv::Mat> weights, cv::Mat& dst);

#endif /* defined(__Submarine__fusion__) */
