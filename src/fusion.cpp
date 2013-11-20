//
//  fusion.cpp
//  Submarine
//
//  Created by Jean Caillé on 11/11/2013.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#include "fusion.h"

#include <opencv2/imgproc/imgproc.hpp>

#pragma mark - GAUSSIAN PYRAMID

void gaussianPyramid(const cv::Mat& input, int levels, std::vector<cv::Mat>& pyramid)
{
    pyramid.clear();
    
    // Called on mask
    cv::Size pyrSize = input.size();
    pyramid.push_back(input);
    for(int i = 0 ; i < levels - 1 ; ++i){
        cv::Mat newLevel ;
        pyrSize = cv::Size(MAX(1, pyrSize.width / 2), MAX(1, pyrSize.height / 2)); // Make sure size is valid
        cv::pyrDown(pyramid.back(), newLevel, pyrSize);
        pyramid.push_back(newLevel);
    }
}

#pragma mark - LAPLACIAN PYRAMID

void laplacianPyramid(const cv::Mat& input, int levels, std::vector<cv::Mat>& pyramid)
{
    pyramid.clear();
    
    cv::Mat currentImg = input;
    for (int i = 0; i < levels; ++i) {
        cv::Mat down, up;
        cv::pyrDown(currentImg, down);
        cv::pyrUp(down, up, currentImg.size());
        cv::Mat newLevel;
        cv::subtract(currentImg, up, newLevel);
        pyramid.push_back(newLevel);
        currentImg = down;
    }
    pyramid.push_back(currentImg);
}

void reconstructFromLaplacianPyramid(const std::vector<cv::Mat>& pyramid, cv::Mat& dst)
{
    int level = (int)(pyramid.size()-1);
    cv::Mat current = pyramid[level];
    for (int i = level-1; i >= 0; --i) {
        cv::Mat up;
        cv::pyrUp(current, up, pyramid[i].size());
        cv::add(up, pyramid[i], current);
    }

    current.copyTo(dst);
    
}

#pragma mark - FUSION

void naiveFusion(const std::vector<cv::Mat>& inputs, const std::vector<cv::Mat>& weights, cv::Mat& dst)
{
    dst.create(inputs[0].size(), CV_8UC3);
    dst.setTo(cv::Scalar(0,0,0));
    
    int w = inputs[0].cols, h = inputs[0].rows;
    
    for(int i = 0 ; i < inputs.size(); ++i){
        for (int y = 0; y < h; ++y){
            for (int x = 0; x < w; ++x){
                dst.at<cv::Vec3b>(y,x) += weights[i].at<float>(y,x)*inputs[i].at<cv::Vec3b>(y,x);
            }
        }
    }
}

void laplacianFusion(const std::vector<cv::Mat>& inputs, const std::vector<cv::Mat>& weights, cv::Mat& dst)
{
    assert(inputs.size() == weights.size());

    const int levels = 5;
    const int n = (int)inputs.size();

    // Compute laplacian pyramids and gaussian weights
    std::vector< std::vector<cv::Mat> > inputPyramids(n);
    std::vector< std::vector<cv::Mat> > weightPyramids(n);
    for (int i = 0; i < n; ++i){
        laplacianPyramid(inputs[i], levels, inputPyramids[i]);
        gaussianPyramid(weights[i], levels+1, weightPyramids[i]);
    }
    
    // "Inverse" pyramids dimensions (start by level, then by image instead of the inverse)
    std::vector< std::vector<cv::Mat> > invInputPyramids(levels+1);
    std::vector< std::vector<cv::Mat> > invWeightPyramids(levels+1);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < levels+1; ++j){
            invInputPyramids[j].push_back(inputPyramids[i][j]);
            invWeightPyramids[j].push_back(weightPyramids[i][j]);
        }
    }
    
    // "Naively" merge all levels of pyramid
    std::vector<cv::Mat> outputPyr(levels+1);
    for (int i = 0 ; i < levels+1; ++i){
        naiveFusion(invInputPyramids[i], invWeightPyramids[i], outputPyr[i]);
    }
    
    // And construct the output from the pyramod
    reconstructFromLaplacianPyramid(outputPyr, dst);
}

