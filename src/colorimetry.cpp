//
//  colorimetry.cpp
//  Submarine
//
//  Created by Jean Caillé on 20/10/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//
// Source for gray-world algorithm : http://www.mathworks.com/matlabcentral/fileexchange/41341-color-constancy-algorithms-gray-world-white-patch-modified-white-patch-etc/content/colorConstancy.m

#include "colorimetry.h"

#include <opencv2/imgproc/imgproc.hpp>


void whiteBalance(const cv::Mat& I, cv::Mat& dst, double lambda)
{
    
    //Compute mean color of I
    cv::Scalar meanColor = cv::mean(I) / 255.0;
    
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

void enhanceContrast(const cv::Mat& I, cv::Mat& dst)
{
    int w = I.cols, h = I.rows;
    
    // Convert to YUV
    cv::Mat Iyuv(h,w,CV_8UC3);
    cv::cvtColor(I, Iyuv, CV_BGR2YUV);
    
    //Split the image into channels, first one being the luminance
    cv::Mat newY;
    cv::Mat channels[3];
    cv::split(Iyuv, channels);
    
    // Apply contrast optimisation on luminance channel
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    clahe->setClipLimit(4);
    clahe->apply(channels[0],newY);
    
    // Change Y and re-merge
    cv::Mat enhanceYUV;
    channels[0] = newY;
    cv::merge(channels, 3, enhanceYUV);
    
    // Convert to RGB
    cv::cvtColor(enhanceYUV, dst, CV_YUV2BGR);
    
}