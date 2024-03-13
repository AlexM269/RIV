//
// Created by anouk on 19/02/2024.
//

#include "zoning.h"

vector<cv::Mat> zoning::extract_zones(const string& fileIm, const int nbZones){
    cv::Mat image = cv::imread(fileIm);
    // taille de chaque zone
    int taille = static_cast<int>(image.rows/nbZones);
    vector<Mat> subImages;
    vector<Rect> zones;
    // préparation des zones de découpe

    for (int x=0; x<nbZones;x++){
        for(int y=0; y<nbZones; y++){
            zones.push_back(Rect(x*taille,y*taille,taille,taille));
        }
    }
    // découpe de l'image de base
    for (int i = 0; i<nbZones*nbZones;i++){
        subImages.push_back(image(zones[i]).clone());
        //imwrite("../zone"+std::to_string(i)+".png",subImages[i]);
    }
    return subImages;
}

