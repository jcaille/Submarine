//
//  fusion.cpp
//  Submarine
//
//  Created by Jean Caillé on 11/11/2013.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#include "fusion.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#pragma mark - GAUSSIAN PYRAMID

std::vector<cv::Mat> gaussianPyramid(const cv::Mat input, int levels){
    // Called on mask
    std::vector<cv::Mat> pyramid = std::vector<cv::Mat>();
    cv::Size pyrSize = input.size();
    pyramid.push_back(input);
    for(int i = 0 ; i < levels ; i++){
        cv::Mat newLevel ;
        pyrSize = cv::Size(MAX(1, pyrSize.width / 2), MAX(1, pyrSize.height / 2)); // Make sure size is valid
        cv::pyrDown(pyramid.back(), newLevel, pyrSize);
        pyramid.push_back(newLevel);
    }
    return pyramid;
}

#pragma mark - LAPLACIAN PYRAMID

std::vector<cv::Mat> laplacianPyramid(cv::Mat input, int levels){
    std::vector<cv::Mat> pyramid = std::vector<cv::Mat>();
    cv::Mat currentImg = input;
    for (int i = 0; i < levels; i ++) {
        cv::Mat down, up;
        cv::pyrDown(currentImg, down);
        cv::pyrUp(down, up, currentImg.size());
        cv::Mat newLevel = currentImg - up;
        pyramid.push_back(newLevel);
        currentImg = down;
    }
    return pyramid;
}

#pragma mark - FUSION

void naiveFusion(cv::Mat a, cv::Mat b, cv::Mat dst){
    
}