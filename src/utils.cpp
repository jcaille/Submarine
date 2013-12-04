//
//  utils.c
//  Submarine
//
//  Created by Florian Denis on 10/16/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#include "utils.h"
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

cv::Mat floatTo8U(const cv::Mat& I)
{
    double min, max;
    cv::minMaxLoc(I, &min, &max);
    
    cv::Mat dst(I.rows,I.cols,CV_8U);
    I.convertTo(dst, CV_8U, 255/(max-min),-255*min/(max-min) );
    return dst;
}

int countSURFFound(const cv::Mat I)
{
    int minHessian = 400;
    cv::SurfFeatureDetector detector( minHessian );
    std::vector<cv::KeyPoint> keypoints;
    detector.detect(I, keypoints );
    
    cv::Mat res;
    cv::drawKeypoints(I, keypoints, res);
    cv::imwrite("/Users/jean/Devel/Submarine/rapport/Support/keypoints_input.png", res);
    
    return (int) keypoints.size();
}