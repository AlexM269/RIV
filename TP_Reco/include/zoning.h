//
// Created by anouk on 19/02/2024.
//

#ifndef PROJET_OPENCV_CMAKE_ZONING_H
#define PROJET_OPENCV_CMAKE_ZONING_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;


class zoning {

public:
    static vector<cv::Mat> extract_zones(const string& fileIm, const int taille);
};


#endif //PROJET_OPENCV_CMAKE_ZONING_H
