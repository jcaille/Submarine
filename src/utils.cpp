//
//  utils.c
//  Submarine
//
//  Created by Florian Denis on 10/16/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#include "utils.h"

cv::Mat floatTo8U(const cv::Mat& I)
{
    double min, max;
    cv::minMaxLoc(I, &min, &max);
    
    cv::Mat dst(I.rows,I.cols,CV_8U);
    I.convertTo(dst, CV_8U, 255/(max-min),-255*min/(max-min) );
    return dst;
    
    
}
