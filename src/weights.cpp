//
//  weights.c
//  Submarine
//
//  Created by Florian Denis on 10/16/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#include "weights.h"

#include <opencv2/imgproc/imgproc.hpp>

#define SQR(x) ((x)*(x))

static const float Ker[] = {1/16.0f, 4/16.0f, 6/16.0f, 4/16.0f, 1/16.0f};
#define sigmaE 64.0f


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
    
    // Compute the boxed filter version
    cv::Mat mean(h,w,CV_8UC3);
    cv::boxFilter(I, mean, -1, cv::Size(5,5),cv::Point(-1,-1),true);
    
    // Compute the gaussian filtered version
    cv::Mat gauss(h,w,CV_8UC3);
    std::vector<float> K (Ker, Ker + sizeof(Ker) / sizeof(Ker[0]) );
    cv::sepFilter2D(I, gauss, -1, K, K);

    // Now that the images are filtered, let's convert them to Lab Color space
    cv::Mat meanLab(h,w,CV_8UC3), gaussLab(h,w,CV_8UC3);
    cv::cvtColor(mean, meanLab, CV_BGR2Lab);
    cv::cvtColor(gauss, gaussLab, CV_BGR2Lab);
    
    // Fill the dst
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            dst.at<float>(y,x) = 1/255.0*cv::norm(meanLab.at<cv::Vec3b>(y,x) , gaussLab.at<cv::Vec3b>(y,x),CV_L2);
    
}

void computeEWeight(const cv::Mat& I,cv::Mat& dst)
{
    int w = I.cols, h = I.rows;
    
    // Grey image
    cv::Mat Igray(h,w,CV_8UC1);
    cv::cvtColor(I, Igray, CV_BGR2GRAY);
    
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            dst.at<float>(y,x) = exp( -0.5*( SQR(Igray.at<uchar>(y,x)-128) /SQR(sigmaE)));

    
}

void computeLWeight(const cv::Mat& I,cv::Mat& dst)
{
    int w = I.cols, h = I.rows;
    
    // Y component, between 0 & 1
    cv::Mat yChar(h,w,CV_8UC1);
    cv::cvtColor(I, yChar, CV_BGR2GRAY);
    cv::Mat y(h,w,CV_32FC1);
    yChar.convertTo(y,CV_32FC1,1.0/255);
    
    
    // Apply laplacian filter
    cv::Mat lap(h,w,CV_32FC1);
    cv::Laplacian(y, lap, CV_32FC1);
    
    
    // Take abs
    dst = cv::abs(lap);
    
}

void normalizeWeightMaps(std::vector<cv::Mat>& maps)
{
    
    size_t n = maps.size();
    
    assert(n>0);
    
    int w = maps[0].cols, h = maps[0].rows;
    float e = 1/float(n);
    
    // Compute the per element sum
    cv::Mat sum(h,w,CV_32FC1);
    maps[0].copyTo(sum);
    for (size_t i = 1; i < n; ++i)
        cv::add(sum, maps[i], sum);

    // Divide each map with the per-element sum
    for (size_t i = 0; i < n; ++i){
        for (int y = 0; y < h; ++y){
            for (int x = 0; x < w; ++x){
                if (sum.at<float>(y,x)){
                    maps[i].at<float>(y,x)/=sum.at<float>(y,x);
                } else {
                    maps[i].at<float>(y,x) = e;
                }
            }
        }
    }


    
    
}