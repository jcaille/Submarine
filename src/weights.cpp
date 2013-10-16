//
//  weights.c
//  Submarine
//
//  Created by Florian Denis on 10/16/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#include <opencv2/imgproc/imgproc.hpp>

#include "weights.h"

static const float LCKernel[] = {1/16.0f, 4/16.0f, 6/16.0f, 4/16.0f, 1/16.0f};

void computeLCWeight(const cv::Mat& I,cv::Mat& dst)
{
    int w = I.cols, h = I.rows;
    
    // Y component, between 0 & 1
    cv::Mat yChar(h,w,CV_8UC1);
    cv::cvtColor(I, yChar, CV_BGR2GRAY);
    cv::Mat y(h,w,CV_32FC1);
    yChar.convertTo(y,CV_32FC1,1.0/255);
    
    y.copyTo(dst);
    
    // local average
    cv::Mat ybar(h,w,CV_32FC1);
    std::vector<float> K (LCKernel, LCKernel + sizeof(LCKernel) / sizeof(LCKernel[0]) );
    cv::sepFilter2D(y, ybar, CV_32FC1, K, K);
    
    // Fill
    cv::absdiff(y, ybar, dst);

}