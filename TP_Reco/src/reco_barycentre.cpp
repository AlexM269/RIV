#include <iostream>
#include <fstream>
#include <list>
#include <dirent.h>
#include <windows.h>
#include <string>
#include <vector>
#include "reco_barycentre.hpp"

using namespace std;

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

cv::Mat reco_barycentre2(const string imName){

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

    cv::Moments moments0 = cv::moments(contours[0]);

    double centerX;
    double centerY;

    // Renvoie la valeur des moments calculés
    //std::cout << "moments0.m10 : "<< to_string(moments0.m10) <<"; moments.m01 : " << to_string(moments0.m01) <<"; moments.m00 : " << to_string(moments0.m00) << std::endl;

    if(moments0.m10!=0 && moments0.m01!=0 && moments0.m00 != 0){
        // Calcule les coordonnées du centre de masse
        centerX = moments0.m10 / moments0.m00;
        centerY = moments0.m01 / moments0.m00;
    }

    else if((cv::moments(contours[1])).m10!=0 && (cv::moments(contours[1])).m01!=0 && (cv::moments(contours[1])).m00 != 0){
        cv::Moments moments1 = cv::moments(contours[1]);
        //Sinon, calcule le barycentre avec le deuxième contour capté
        centerX = moments1.m10 / moments1.m00;
        centerY = moments1.m01 / moments1.m00;
    }
    else if((cv::moments(contours[2])).m10!=0 && (cv::moments(contours[2])).m01!=0 && (cv::moments(contours[2])).m00 != 0){
        cv::Moments moments2 = cv::moments(contours[2]);
        //Sinon, calcule le barycentre avec le troisième contour capté
        centerX = moments2.m10 / moments2.m00;
        centerY = moments2.m01 / moments2.m00;
    }
    else{
        cv::Moments moments3 = cv::moments(contours[3]);

        //Sinon, calcule le barycentre avec le troisième contour capté
        if(!moments3.m00==0){
            centerX = moments3.m10 / moments3.m00;
            centerY = moments3.m01 / moments3.m00;
        }
        //Si le moment est toujours nul, on met le centre de masse au centre
        else{
            centerX = im.cols/2;
            centerY = im.rows/2;
        }
    }


    // Affiche les coordonnées du centre de masse
    std::cout << "Le centre de masse de "<< imName <<" a pour coordonnees : (" << centerX << ", " << centerY << ")" << std::endl;

    // Dessine le centre de masse sur l'image
    cv::circle(im, cv::Point(centerX, centerY), 5, cv::Scalar(0, 0, 255), -1);

    imshow("Extraction du centre de masse", im);

    return im;

};
