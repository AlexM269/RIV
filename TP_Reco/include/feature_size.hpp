//
// Created by anouk on 24/01/2024.
//

#ifndef PROJET_OPENCV_CMAKE_FEATURE_SIZE_HPP
#define PROJET_OPENCV_CMAKE_FEATURE_SIZE_HPP

#include <utility> // pour std::pair
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;

class feature_size {

public:
    static pair<pair<int,int>,cv::Mat> extract(const string& fileIm);
};


#endif //PROJET_OPENCV_CMAKE_FEATURE_SIZE_HPP
