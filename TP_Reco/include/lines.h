//
// Created by anouk on 19/02/2024.
//

#ifndef PROJET_OPENCV_CMAKE_LINES_H
#define PROJET_OPENCV_CMAKE_LINES_H

#include <tuple>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

class lines {
public:
    static array<array<float, 4>,6> extract_lines(const string& fileIm);
};


#endif //PROJET_OPENCV_CMAKE_LINES_H
