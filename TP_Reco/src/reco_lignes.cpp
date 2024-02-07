#include "reco_lignes.hpp"

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

cv::Mat reco_lignes(const string imName){
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

    //cv::Mat edges = cv::Canny(imGray,50, 150, apertureSize=3);

    //cv::Mat lines = cv2.HoughLines(edges, 1, M_PI/180, 200);

    /*
    // Binarise l'image à l'aide de la méthode d'Otsu
    cv::Mat imBinary;
    cv::threshold(imGray, imBinary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // Inverser l'image binaire
    cv::bitwise_not(imBinary, imBinary);


    // Trouve les contours de l'objet dans l'image binaire
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(imBinary, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // Parcourir les contours et afficher les coordonnées des points
    for (const auto& contour : contours) {
        for (const auto& point : contour) {
            std::cout << "Coordonnées du point : x = " << point.x << ", y = " << point.y << std::endl;
        }
    }
     */

    // Dessiner les contours sur l'imagette (facultatif, à des fins de visualisation)
    cv::Mat result = im.clone();
   // cv::drawContours(result, contours, -1, cv::Scalar(0, 255, 0), 2);

    // Afficher l'imagette avec les contours
    cv::imshow("Contours", result);

    return result;
}
