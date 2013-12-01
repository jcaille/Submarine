//
//  enhancement.cpp
//  Submarine
//
//  Created by Florian Denis on 23/10/13.
//  Copyright (c) 2013 Florian Denis. All rights reserved.
//

#include "enhancement.h"

#include "weights.h"
#include "colorimetry.h"
#include "fusion.h"
#include "utils.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "iostream"

void _computeFirstInput(const cv::Mat& I, cv::Mat& out)
{
    // First input is white balanced original image
    whiteBalance(I,out,.0);
}

void _computeSecondInput(const cv::Mat& firstInput, cv::Mat& out)
{
    
    // Apply a filter to remove the noise
    cv::Mat smooth;
    cv::bilateralFilter(firstInput, smooth, -1, 20, 5);
    
    // Enhance contrast
    enhanceContrast(smooth, out);
}


void _computeWeights(const std::vector<cv::Mat>& input, std::vector<cv::Mat>& weights)
{
    
    for (int i = 0; i<input.size(); ++i) {
        computeEWeight(input[i], weights[i]);
    }
    
    normalizeWeightMaps(weights);
}

void saveWeights(cv::Mat I)
{
    int w = I.cols ; int h = I.rows;
    cv::Mat weight(h, w, CV_32F);
    
    computeEWeight(I, weight); cv::normalize(weight, weight, 0, 255, cv::NORM_MINMAX);
    cv::imwrite("/Users/jean/Devel/Submarine/rapport/Support/exposedness.png", weight);
    
    computeLCWeight(I, weight); cv::normalize(weight, weight, 0, 255*5, cv::NORM_MINMAX);
    cv::imwrite("/Users/jean/Devel/Submarine/rapport/Support/lc.png", weight);

    computeLWeight(I, weight); cv::normalize(weight, weight, 0, 255*5, cv::NORM_MINMAX);
    cv::imwrite("/Users/jean/Devel/Submarine/rapport/Support/laplacian.png", weight);

    computeSWeight(I, weight); cv::normalize(weight, weight, 0, 255*5, cv::NORM_MINMAX);
    cv::imwrite("/Users/jean/Devel/Submarine/rapport/Support/saliency.png", weight);
    cv::imshow("Youpi", weight);

}

void enhanceUnderwaterImage(const cv::Mat& I, cv::Mat& out)
{
    int w = I.cols, h = I.rows;
    
    // Compute 1st input
    cv::Mat firstInput(h,w,CV_8UC3);
    _computeFirstInput(I,firstInput);

    // Compute 2nd input
    cv::Mat secondInput(h,w,CV_8UC3);
    _computeSecondInput(firstInput,secondInput);

    std::vector<cv::Mat> input;
    input.push_back(secondInput);
    input.push_back(firstInput);
    
    std::vector<cv::Mat> weights;
    weights.push_back(cv::Mat(h,w,CV_32F));
    weights.push_back(cv::Mat(h,w,CV_32F));
    
    _computeWeights(input,weights);
    
    laplacianFusion(input, weights, out);
    
    //Compare the numbers of SURF found
    std::cout << "There were " << countSURFFound(I) << " found in the input image" << std::endl;
    std::cout << "There are  " << countSURFFound(out) << " found in the output image" << std::endl;
    saveWeights(firstInput);
    cv::imwrite("/Users/jean/Devel/Submarine/rapport/Support/color.png", firstInput);
    cv::imwrite("/Users/jean/Devel/Submarine/rapport/Support/contrast.png", secondInput);

}