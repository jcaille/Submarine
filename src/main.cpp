//
//  main.c
//  Submarine
//
//  Created by Florian Denis on 10/16/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "weights.h"
#include "utils.h"

int main(int argc, const char * argv[])
{

    cv::Mat I = cv::imread("test_img/DSCN6533.png");
    int w = I.cols, h = I.rows;
    
    
    cv::Mat lW(h,w,CV_32F), lcW(h,w,CV_32F), sW(h,w,CV_32F), eW(h,w,CV_32F);
    computeLWeight(I, lW);
    computeLCWeight(I, lcW);
    computeSWeight(I, sW);
    computeEWeight(I, eW);

    
    std::vector<cv::Mat> weights(4);
    weights[0] = lW;
    weights[1] = lcW;
    weights[2] = sW;
    weights[3] = eW;
    
    normalizeWeightMaps(weights);
    
    cv::imshow("I", I);
    cv::imshow("L", floatTo8U(lW));
    cv::imshow("LC", floatTo8U(lcW));
    cv::imshow("S", floatTo8U(sW));
    cv::imshow("E", floatTo8U(eW));
    
    
    cv::waitKey();
    
    
    return 0;
}

