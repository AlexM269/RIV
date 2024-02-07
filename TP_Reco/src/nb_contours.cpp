#include "nb_contours.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <dirent.h>
#include <windows.h>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int nb_contours (const std::string imName){
    // Load image
    Mat im = imread(imName);
    if(im.data == nullptr){
        cerr << "Image not found: "<< imName << endl;
        waitKey(0);
        //system("pause");
        exit(EXIT_FAILURE);
    }

    imshow("exemple_init", im);

    // Convertit l'image en niveaux de gris
    cv::Mat imGray;
    cv::cvtColor(im, imGray, cv::COLOR_BGR2GRAY);

    // Binarise l'image à l'aide de la méthode d'Otsu
    cv::Mat imBinary;
    cv::threshold(imGray, imBinary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // Inverser l'image binaire
    cv::bitwise_not(imBinary, imBinary);

    // Trouve les contours de l'objet dans l'image binaire
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(imBinary, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // Dessine les contours sur l'image
    cv::drawContours(im, contours, -1, cv::Scalar(0, 255, 0), 2);

    std::cout << "Nombre de contours de l'imagette : "<<to_string(contours.size())<< std::endl;

    return contours.size();
}