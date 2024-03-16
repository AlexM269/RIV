//
// Created by anouk on 19/02/2024.
//

#include "lines.h"
#include <iostream>

// retourne liste de 6 éléments correspondant aux 6 zones d'analyse
// (zones verticales : droite, centrale, gauche, et zones horizontales : haute, centrale, basse)
// chaque élément du vecteur représente la plus longue ligne trouvée dans la zone
// (par un vec4 contenant (coord x du milieu, coord y du milieu, angle de la ligne, longueur de la ligne))
// val -10 partout si pas de ligne trouvée
array<array<float, 4>,6> lines::extract_lines(const string& fileIm){
    std::array<std::array<float, 4>, 6> res = {{
        {-10, -10, -10, -10},
        {-10, -10, -10, -10},
        {-10, -10, -10, -10},
        {-10, -10, -10, -10},
        {-10, -10, -10, -10},
        {-10, -10, -10, -10}
    }};

    // Chargement de l'image
    cv::Mat image = cv::imread(fileIm, cv::IMREAD_GRAYSCALE);

    cv::erode(image, image, cv::Mat(), cv::Point(-1, -1), 5);
    cv::dilate(image, image, cv::Mat(), cv::Point(-1, -1), 5);

    // Application d'un lissage pour réduire le bruit
    cv::GaussianBlur(image, image, cv::Size(9, 9), 3, 3);
    threshold(image, image, 240, 255, cv::THRESH_BINARY);
    // Inversion de l'image car la fonction détecte les lignes blanches sur fond noir
    cv::Mat invertedImage = cv::Scalar::all(255) - image;

    // Détection des segments (lignes droites) sur l'image
    std::vector<cv::Vec4i> segments;
    cv::HoughLinesP(invertedImage, segments, 1, 0.01, 40, 80, 10);

    // Pour stocker val temporaires
    array<float, 6> lenMax {0.0,0.0,0.0,0.0,0.0,0.0};
    array<float, 6> angleMax {0.0,0.0,0.0,0.0,0.0,0.0};
    array<float, 6> milXmax {0.0,0.0,0.0,0.0,0.0,0.0};
    array<float, 6> milYmax {0.0,0.0,0.0,0.0,0.0,0.0};

    for (const auto& segment : segments) {
        // Extracation des coords des extrémités du segments
        int x1 = segment[0];
        int y1 = segment[1];
        int x2 = segment[2];
        int y2 = segment[3];

        // Calcul des coord du milieu
        float milX = (x1 + x2) / 2.0;
        float milY = (y1 + y2) / 2.0;
        // Longueur du segment
        float len = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));

        // Angle par rapport à l'axe des abscisses x (radians)
        float angle = std::atan2(y2 - y1, x2 - x1);
        // Ramène valeur négative à même angle opposé (positif) car corresp à même ligne
        if (angle < 0.0) {
            angle = angle + 3.14;
        }
        // Ramène valeur angle proche de PI à proche de 0 car corresp à lignes quasi horizontale aussi
        if (std::abs(angle - 3.14) < 0.2) {
            angle = std::abs(angle - 3.14);
        }

        //PARTIES verticales (angle toujours >0 maintenant
        if((angle>0.7&&angle<2.3)||(angle>-2.3&&angle<-0.7)) {
            // Zone 1
            if (milX < 250.0 / 3.0) {
                if (len > lenMax[0]) {
                    lenMax[0] = len;
                    milXmax[0] = milX;
                    milYmax[0] = milY;
                    angleMax[0] = angle;
                }
            }
            // Zone 2
            if (milX > 250.0 / 3.0 && milX < 500.0 / 3.0) {
                if (len > lenMax[1]) {
                    lenMax[1] = len;
                    milXmax[1] = milX;
                    milYmax[1] = milY;
                    angleMax[1] = angle;
                }
            }
            // Zone 3
            if (milX > 500.0 / 3.0) {
                if (len > lenMax[2]) {
                    lenMax[2] = len;
                    milXmax[2] = milX;
                    milYmax[2] = milY;
                    angleMax[2] = angle;
                }
            }
        }
        //ZONES HORIZONTALES
        else {
            // Zone 4
            if (milY < 250.0 / 3.0) {
                if (len > lenMax[3]) {
                    lenMax[3] = len;
                    milXmax[3] = milX;
                    milYmax[3] = milY;
                    angleMax[3] = angle;
                }
            }
            // Zone 5
            if (milY > 250.0 / 3.0 && milX < 500.0 / 3.0) {
                if (len > lenMax[4]) {
                    lenMax[4] = len;
                    milXmax[4] = milX;
                    milYmax[4] = milY;
                    angleMax[4] = angle;

                }
            }
            // Zone 6
            if (milY > 500.0 / 3.0) {
                if (len > lenMax[5]) {
                    lenMax[5] = len;
                    milXmax[5] = milX;
                    milYmax[5] = milY;
                    angleMax[5] = angle;

                }
            }
        }
    }

    // POUR DESSINER POUR VERIFIER
   // cv::Mat imageSegments;
   // cv::cvtColor(invertedImage, imageSegments, cv::COLOR_GRAY2BGR);

    // Moyennage des valeurs si il y a des lignes
    for(int i=0;i<6;i++){
        if(lenMax[i]>0) {
            res[i][0] = milXmax[i];
            res[i][1] = milYmax[i];
            res[i][2] = angleMax[i];
            res[i][3] = lenMax[i];

          /*  // POUR DESSINER
            double dx = lenMax[i] * std::cos(angleMax[i]);
            double dy = lenMax[i] * std::sin(angleMax[i]);
            cv::Point pt1(milXmax[i] - dx/2, milYmax[i]- dy/2);
            cv::Point pt2(milXmax[i] + dx/2, milYmax[i] + dy/2);
            cv::line(imageSegments, pt1, pt2, cv::Scalar(255/(i+1), 20, 51*i), 2);
            */
        }
    }

    //POUR DESSINER
   // cv::imwrite("../saved_model1.png", imageSegments);

    return res;
}

/* POUR TESTER DANS MAIN :
   string file = string("../img_test/draws/injury/test1.png");
    feature_size::extract(file);


    feature_size::extract(file);
    array<array<float, 4>,6> res = lines::extract_lines("../saved_model.png");
    for (int i=0; i<6;i++){
        cout << "Ligne zone " <<i+1<<" : Angle moyen = "<< res[i][2]<<" ; Longueur : "<< res[i][3] <<
             " ; Coord milieu moyen = ("<<res[i][0]<<", "<<res[i][1]<<")" <<endl;
    }
*/