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
#include "fusion.h"

#include <opencv2/imgproc/imgproc.hpp>

void _computeFirstInput(const cv::Mat& I, cv::Mat& out)
{
    // First input is white balanced original image
    whiteBalance(I,out,.0);
}

void _computeSecondInput(const cv::Mat& firstInput, cv::Mat& out)
{
    
    // Apply a filter to remove the noise
    cv::Mat smooth;
    cv::bilateralFilter(firstInput, smooth, -1, 20, 5);
    
    // Enhance contrast
    enhanceContrast(smooth, out);
}


void _computeWeights(const std::vector<cv::Mat>& input, std::vector<cv::Mat>& weights)
{
    
    for (int i = 0; i<input.size(); ++i) {
        computeEWeight(input[i], weights[i]);
    }
    
    normalizeWeightMaps(weights);
    
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
    
    std::vector<cv::Mat> input;
    input.push_back(secondInput);
    input.push_back(firstInput);
    
    std::vector<cv::Mat> weights;
    weights.push_back(cv::Mat(h,w,CV_32F));
    weights.push_back(cv::Mat(h,w,CV_32F));
    
    _computeWeights(input,weights);
    
    laplacianFusion(input, weights, out);
    
    
}