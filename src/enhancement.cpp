//
//  enhancement.cpp
//  Submarine
//
//  Created by Florian Denis on 23/10/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#include "enhancement.h"

#include "weights.h"
#include "colorimetry.h"

void _computeFirstInput(const cv::Mat& I, cv::Mat& out)
{
    // First input is white balanced original image
    whiteBalance(I,out);
}

void _computeSecondInput(const cv::Mat& firstInput, cv::Mat& out)
{
    
    // Apply a filter to remove the noise
    cv::Mat smooth = firstInput.clone();
    
    // Enhance contrast
    enhanceContrast(smooth, out);
}


void enhanceUnderwaterImage(const cv::Mat& I, cv::Mat& out)
{
    
    int w = I.cols, h = I.rows;
    
    // Compute 1st input
    cv::Mat firstInput(h,w,CV_8UC3);
    _computeFirstInput(I,firstInput);

    // Compute 2nd input
    cv::Mat secondInput(h,w,CV_8UC3);
    _computeSecondInput(firstInput,secondInput);
    
    // For now
    secondInput.copyTo(out);
    
    
}