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

#include "enhancement.h"

int main(int argc, const char * argv[])
{

    cv::Mat I = cv::imread("test_img/PICT0422.png");
    int w = I.cols, h = I.rows;
    
    cv::Mat betterI(h, w, CV_8UC3);
    enhanceUnderwaterImage(I, betterI);
    
    cv::imshow("original", I);
    cv::imshow("enhanced", betterI);
    
    cv::waitKey();
    
    return 0;
}

