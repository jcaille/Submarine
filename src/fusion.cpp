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

void gaussianPyramid(const cv::Mat& input, int levels, std::vector<cv::Mat>& pyramid)
{
    pyramid.clear();
    
    // Called on mask
    cv::Size pyrSize = input.size();
    pyramid.push_back(input);
    for(int i = 0 ; i < levels - 1 ; i++){
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
    for (int i = 0; i < levels; i ++) {
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

#pragma mark - FUSION

void fuseInputs(std::vector<cv::Mat> inputs, std::vector<cv::Mat> weights, cv::Mat& dst)
{
    dst.setTo(cv::Scalar(0,0,0));
    
    int levels = 5;
    //Compute laplacian pyramid
    std::vector<cv::Mat> firstInputPyramid; laplacianPyramid(inputs[0], levels, firstInputPyramid);
    std::vector<cv::Mat> secondInputPyramid; laplacianPyramid(inputs[1], levels, secondInputPyramid);
    
    //Compute gaussian pyramid of weights
    std::vector<cv::Mat> firstWeightPyramid; gaussianPyramid(weights[0], levels, firstWeightPyramid);
    std::vector<cv::Mat> secondWeightPyramid; gaussianPyramid(weights[1], levels, secondWeightPyramid);
    
    //Fuse inputs according to formula
    for (int i = 0 ; i < firstInputPyramid.size(); i++){
        cv::Mat A, B;
        cv::multiply(firstInputPyramid[i], firstWeightPyramid[i], A);
        cv::multiply(secondInputPyramid[i], secondWeightPyramid[i], B);
        dst += A+B;
    }
}

void naiveFusion(std::vector<cv::Mat> inputs, std::vector<cv::Mat> weights, cv::Mat& dst)
{
    dst.setTo(cv::Scalar(0,0,0));
    
    for(int i = 0 ; i < inputs.size(); i++){
        cv::Mat A;
        cv::multiply(inputs[i], weights[i], A);
        dst += A;
    }
}