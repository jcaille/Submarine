//
//  weights.c
//  Submarine
//
//  Created by Florian Denis on 10/16/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#include <opencv2/imgproc/imgproc.hpp>

#include "weights.h"

static const float Ker[] = {1/16.0f, 4/16.0f, 6/16.0f, 4/16.0f, 1/16.0f};

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
    std::vector<float> K (Ker, Ker + sizeof(Ker) / sizeof(Ker[0]) );
    cv::sepFilter2D(y, ybar, CV_32FC1, K, K);
    
    // Fill
    cv::absdiff(y, ybar, dst);

}

void computeSWeight(const cv::Mat& I,cv::Mat& dst)
{
    int w = I.cols, h = I.rows;
    
    // Transform into the Lab space
    cv::Mat ILab(h,w,CV_8UC3);
    cv::cvtColor(I, ILab, CV_BGR2Lab);
    
    
    // Compute the boxed filter version
    cv::Mat mean(h,w,CV_8UC3);
    cv::boxFilter(ILab, mean, -1, cv::Size(5,5),cv::Point(-1,-1),true);
    
    // Compute the gaussian filtered version
    cv::Mat gauss(h,w,CV_8UC3);
    std::vector<float> K (Ker, Ker + sizeof(Ker) / sizeof(Ker[0]) );
    cv::sepFilter2D(ILab, gauss, -1, K, K);
    
    // Fill the dst
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            dst.at<float>(y,x) = 1/255.0*cv::norm(mean.at<cv::Vec3b>(y,x) , gauss.at<cv::Vec3b>(y,x),CV_L2);
    
}