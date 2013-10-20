//
//  WhiteBalance.cpp
//  Submarine
//
//  Created by Jean Caillé on 20/10/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//
// Source for gray-world algorithm : http://www.mathworks.com/matlabcentral/fileexchange/41341-color-constancy-algorithms-gray-world-white-patch-modified-white-patch-etc/content/colorConstancy.m

#include "WhiteBalance.h"
#include "math.h"
#include <opencv2/highgui/highgui.hpp>
#define SQR(x) ((x)*(x))

void whiteBalanceInput(cv::Mat I, double lambda, cv::Mat dst){
    //Compute mean color of I
    cv::Scalar meanColor = cv::mean(I) / 255.0;
    std::cout << meanColor << std::endl;
    
    //Grey average value
    double averageGrayValue = (meanColor[0] + meanColor[1] + meanColor[2]) / 3.0;
    
    //Correct average illumination as in paper
    if(lambda < 0){
        lambda = 0.2;
    }
    averageGrayValue = 0.5 + averageGrayValue * lambda;
    cv::Scalar illuminant = meanColor / averageGrayValue;

    //Split the image into channels
    cv::Mat channels[3];
    cv::split(I, channels);
    
    // Apply correction
    channels[0] /= illuminant[0];
    channels[1] /= illuminant[1];
    channels[2] /= illuminant[2];
    
    cv::merge(channels, 3, dst);
}