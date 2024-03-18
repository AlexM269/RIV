//
// Created by anouk on 24/01/2024.
//

#include "feature_extraction.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

pair<int,int> extractSize(const string& fileIm){
    Mat imBase = imread(fileIm);
    Mat im;
    cvtColor(imBase, im, cv::COLOR_BGR2GRAY);
    threshold(im, im, 200, 255, cv::THRESH_BINARY);

    int premierPixelNoirX = im.cols;
    int dernierPixelNoirX = 0;
    int premierPixelNoirY = im.rows;
    int dernierPixelNoirY = 0;
    // parcourt les colonnes de l'image
    for (int x = 0; x < im.cols; ++x) {
        // parcourt les lignes de l'image
        for (int y = 0; y < im.rows; ++y) {
            if (im.at<uchar>(y, x) < 100) {  // pixel noir trouvé
                if (y<premierPixelNoirY) {
                    premierPixelNoirY = y;
                }
                if (y>dernierPixelNoirY) {
                    dernierPixelNoirY = y;
                }
                if (x<premierPixelNoirX) {
                    premierPixelNoirX = x;
                }
                if (x>dernierPixelNoirX) {
                    dernierPixelNoirX = x;
                }
            }
        }
    }

    // Calcul la largeur du motif
    int largeur = dernierPixelNoirX - premierPixelNoirX ;
    // Calcul la hauteur du motif
    int hauteur = dernierPixelNoirY - premierPixelNoirY ;
    //std::cout<<"x :"<<premierPixelNoirX<<" x der : "<< dernierPixelNoirX<<"   y:"<<premierPixelNoirY<<" y der :"<<dernierPixelNoirY<<endl;

    Rect roiRect(premierPixelNoirX, premierPixelNoirY, largeur, hauteur);  // (x, y, width, height)
    Mat roi = imBase(roiRect).clone();
    int newHauteur;
    int newLargeur;
    if(hauteur>largeur){
        newHauteur=250;
        double ratio=(static_cast<double>(largeur)/hauteur)*250;
        newLargeur = static_cast<int>(ratio);
    } else {
        newLargeur = 250;
        double ratio = (static_cast<double>(hauteur)/largeur)*250;
        newHauteur = static_cast<int>(ratio);
    }
    resize(roi, roi, cv::Size(newLargeur, newHauteur));

    // Image vide blanche pour les marges
    Mat imVide(250, 250, roi.type(), cv::Scalar(255, 255, 255));
    // Position de l'image redimensionnée sur la vide
    int posX = static_cast<int>((250 - newLargeur) / 2);
    int posY = static_cast<int>((250 - newHauteur) / 2);
    Rect rec = Rect(posX, posY, newLargeur, newHauteur);
    // Place image redimensionnée sur le fond blanc
    roi.copyTo(imVide(rec));

    imwrite("../saved_model.png",imVide);

    return make_pair(largeur, hauteur);
}

vector<int> countPixel( const string& image) {
    vector<int> res;

    Mat im = imread(image);

    if (im.data == nullptr) {
        cerr << "Image not found: " << endl;
        waitKey(0);
        //system("pause");
        exit(EXIT_FAILURE);
    }

    Mat gray ;
    cvtColor(im, gray, cv::COLOR_BGR2GRAY);

    // Transform it to binary and invert it. White on black is needed.
    Mat bw;
    threshold(gray, bw, 40, 255, THRESH_BINARY_INV | THRESH_OTSU);

    //vector<Point> black_pixels;   // output, locations of non-zero pixels
    int nbBlack = cv::countNonZero(bw);

    int nbPixels = bw.rows * bw.cols;

    res.push_back(nbPixels); res.push_back(nbBlack); res.push_back(nbPixels - nbBlack);

    return res;
}

double air(const string& image){
    Mat img = imread(image, IMREAD_GRAYSCALE);

    // Binarise l'image à l'aide de la méthode d'Otsu
    Mat binary;
    cv::threshold(img, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // Inverse l'image binaire
    cv::bitwise_not(binary, binary);


    // Trouve les contours dans l'image binarisée
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // Calcule les moments du premier contour trouvé
    Moments M = moments(contours[0]);
    double area = 0;
    // Calculer l'aire du premier contour trouvé
    for(int i = 0; i < contours.size(); i++) {
        area += cv::contourArea(contours[i]);
    }

    return area;
}

Point reco_barycentre(const string imName){

    // Load image
    Mat im = imread(imName);
    if(im.data == nullptr){
        cerr << "Image not found: "<< imName << endl;
        waitKey(0);
        //system("pause");
        exit(EXIT_FAILURE);
    }

    // Convertit l'image en niveaux de gris
    Mat imGray;
    cvtColor(im, imGray, cv::COLOR_BGR2GRAY);

    // Binarise l'image à l'aide de la méthode d'Otsu
    Mat imBinary;
    threshold(imGray, imBinary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // Inverser l'image binaire
    bitwise_not(imBinary, imBinary);

    // Trouve les contours de l'objet dans l'image binaire
    vector<vector<Point>> contours;
    findContours(imBinary, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // Dessine les contours sur l'image
    drawContours(im, contours, -1, cv::Scalar(0, 255, 0), 2);

    double centerX = 0;
    double centerY = 0;

    if(!contours.empty()) {
        Moments calculatedMoments;
        if (contours.size() >= 1) {
            calculatedMoments = moments(contours[0]);
        } else if (contours.size() >= 2) {
            calculatedMoments = moments(contours[1]);
        } else if (contours.size() >= 3) {
            calculatedMoments = moments(contours[2]);
        } else if (contours.size() >= 4) {
            calculatedMoments = moments(contours[3]);
        }

        if (calculatedMoments.m00 != 0) { // Utilisez la variable renommée ici
            // Calcule les coordonnées du centre de masse
            centerX = calculatedMoments.m10 / calculatedMoments.m00;
            centerY = calculatedMoments.m01 / calculatedMoments.m00;
        } else {
            // Si le moment est toujours nul, on met le centre de masse au centre
            centerX = im.cols / 2;
            centerY = im.rows / 2;
        }

    }
    // Enregistre le centre de masse dans res
    Point res = Point (centerX,centerY);

    return res;
}

/*
vector<double> normalisation(const vector<double>& vec){
    std::vector<double> res;
    std::vector<double> new_vec;
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(new_vec), [](double num) { return num != -10; });
    double moy = std::accumulate(new_vec.begin(),new_vec.end(),0.0)/new_vec.size();
    double sum = 0;
    int size_normalisation = 0;
    for(double v : new_vec){
        sum += pow( v - moy, 2 );
        size_normalisation++;
    }
    double et = sqrt(sum/size_normalisation);

    for(double v : vec){
        if(v!=-10){
            res.push_back((v - moy)/et);
        }
        else {
            res.push_back(v);
        }
    }

    return res;
}
 */

vector<double> normalisation(const vector<double>& vec){
    vector<double> res;
    double moy = accumulate(vec.begin(),vec.end(),0.0)/vec.size();
    double sum = 0;
    for(double v : vec){
        sum += pow( v - moy, 2 );
    }
    double et = sqrt(sum/vec.size());

    for(double v : vec){
        res.push_back((v - moy)/et);
    }

    return res;
}