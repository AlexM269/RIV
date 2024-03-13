//
// Created by anouk on 14/02/2024.
//

#ifndef PROJET_OPENCV_CMAKE_CIRCLES_HPP
#define PROJET_OPENCV_CMAKE_CIRCLES_HPP

#include <tuple>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;

class circles {
    public:
        static array<pair<int, array<int, 3>>,5>  extract_circles(const string& fileIm);

};


#endif //PROJET_OPENCV_CMAKE_CIRCLES_HPP
