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

    cv::Mat I = cv::imread("test_img/DSCN6538_1.png");
    int w = I.cols, h = I.rows;
    
    
    cv::Mat lcW(h,w,CV_32F);
    computeLCWeight(I, lcW);
    
    cv::imshow("I", I);
    cv::imshow("LC", floatTo8U(lcW));
    
    cv::waitKey();
    
    
    return 0;
}

