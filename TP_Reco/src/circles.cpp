//
// Created by anouk on 14/02/2024.
//

#include "circles.h"
#include <algorithm> // Pour std::min
#include <string>

/*Traitement sur 5 zones : image complète, partie gauche, partie droite, partie haute, partie basse (corresp aux 5 paires du tableau résultant)
-> image complete permet aperçu global et comparaison générale, notament pour les cercles qui sont proches
  d'une frontière (mais de part et d'autre) et qui donc ne seront pas comparés entre eux
-> partie droite permet de comparer les cercles à droite de l'image (leur nombre et position moyenne) dans le fichier ARF
  ,respectivement pour les autres parties
Cette séparation des zones est importante pour avoir des attributs comparables (en situant les cercles avant de comparer
car sinon par ex, on pourrait avoir un symbole avec 2 cercle dont le premier est excentré dû à un mauvais coup de stylo, si on
ne maitrise pas les emplacements des cercles comparés c'est ce "mauvais" cercle qui pourrait être utilisé pour
la comparaison au premier cercle trouvé d'un autre symbole, et le 2e cercle serait comparé au 2e cercle de l'autre symbole
alors que sa position correspondait peut être plutôt à celui du premier)
Pas plus de zones car sinon trop précis et le moindre basculement d'une frontière à une autre empêche la comparaison des 2 cercles
Pas de zoning car découper vraiment le symbole tronquerait les cercles et donc on ne les détecterait pas
Retourne vecteur de 5 paires correspondant aux 5 zones avec (nombre de cercles, triplets (rayon cercle moyen, centre coord X moyen, centre coord Y moyen)
-> si pas de cercles : val -1 */
array<pair<int, array<int, 3>>,5> circles::extract_circles(const string& fileIm) {
    // Initialisation du tuple avec -1 partout (val par défaut si pas de cercle)
    std::array<std::pair<int, std::array<int, 3>>, 5> resCercles{
            std::make_pair(-10, std::array<int, 3>{-10, -10, -10}),
            std::make_pair(-10, std::array<int, 3>{-10, -10, -10}),
            std::make_pair(-10, std::array<int, 3>{-10, -10, -10}),
            std::make_pair(-10, std::array<int, 3>{-10, -10, -10}),
            std::make_pair(-10, std::array<int, 3>{-10, -10, -10})
    };


    // Chargement de l'image
    cv::Mat image = cv::imread(fileIm, cv::IMREAD_GRAYSCALE);

    cv::erode(image, image, cv::Mat(), cv::Point(-1, -1), 5);
    cv::dilate(image, image, cv::Mat(), cv::Point(-1, -1), 5);

    // Application d'un lissage pour réduire le bruit
    cv::GaussianBlur(image, image, cv::Size(9, 9), 3, 3);
    threshold(image, image, 240, 255, cv::THRESH_BINARY);

    // Détectage des cercles avec la transformée de Hough
    std::vector<cv::Vec3f> cercles;
    cv::HoughCircles(image, cercles, cv::HOUGH_GRADIENT, 1, image.rows / 3, 100, 18, 10, image.rows / 2);

    array<int, 5> nbCercles {0,0,0,0,0};
    array<int, 5> rayonsMoy {-10,-10,-10,-10,-10};
    array<int, 5> centresXmoy {-10,-10,-10,-10,-10};
    array<int, 5> centresYmoy {-10,-10,-10,-10,-10};
    // Parcours du tableau des cercles détéctés
   for (int i = 0; i < cercles.size(); ++i) {
        int radius = cvRound(cercles[i][2]);
        int centreX = cercles[i][0];
        int centreY = cercles[i][1];

        // Traitement image globale
       nbCercles[0]++; // Nb de cercles total
       rayonsMoy[0] += radius; // Pour calcul rayon moyen
       centresXmoy[0] += centreX; // Pour calcul position X moyenne
       centresYmoy[0] += centreY; // Pour calcul position Y moyenne

       // Traitement zone gauche else zone droite
       if(centreX<125){
           nbCercles[1]++; // Nb de cercles à gauche
           rayonsMoy[1] += radius; // Pour calcul rayon moyen des cercles gauches
           centresXmoy[1] += centreX; // Pour calcul position X moyenne
           centresYmoy[1] += centreY; // Pour calcul position Y moyenne
       } else {
           nbCercles[2]++; // Nb de cercles à droite
           rayonsMoy[2] += radius; // Pour calcul rayon moyen des cercles droits
           centresXmoy[2] += centreX; // Pour calcul position X moyenne
           centresYmoy[2] += centreY; // Pour calcul position Y moyenne
       }

       // Traitement zone haute else basse
       if(centreY<125){
           nbCercles[3]++; // Nb de cercles en haut
           rayonsMoy[3] += radius; // Pour calcul rayon moyen des cercles hauts
           centresXmoy[3] += centreX; // Pour calcul position X moyenne
           centresYmoy[3] += centreY; // Pour calcul position Y moyenne
       } else {
           nbCercles[4]++; // Nb de cercles à gauche
           rayonsMoy[4] += radius; // Pour calcul rayon moyen des cercles gauches
           centresXmoy[4] += centreX; // Pour calcul position X moyenne
           centresYmoy[4] += centreY; // Pour calcul position Y moyenne
       }
    }


    // Moyennage des valeurs si il y a des cercles
    for(int i=0;i<5;i++){
        resCercles[i].first = nbCercles[i];
        resCercles[i].second[0] = rayonsMoy[i];
        resCercles[i].second[1] = centresXmoy[i];
        resCercles[i].second[2] = centresYmoy[i];

        if(resCercles[i].first!=0) {
            resCercles[i].second[0] =  resCercles[i].second[0]/resCercles[i].first; // Moyenne rayon
            resCercles[i].second[1] =  resCercles[i].second[1]/resCercles[i].first; // Moyenne X
            resCercles[i].second[2] =  resCercles[i].second[2]/resCercles[i].first; // Moyenne Y
        }
    }

    // Retourne le tableau résultant
    return resCercles;
}



/* EXEMPLE POUR RECUPERER VALEURS (dans Main) :
     string file = string("../img_test/draws/fire/test5.png");
    feature_size::extract(file);
    array<pair<int, array<int, 3>>,5> res = circles::extract_circles("../saved_model.png");
    std::cout << "Nombre de cercles détectés total : " << res[0].first << std::endl;
    std::cout << "Rayon moyen total : " << res[0].second[0] << std::endl;
    std::cout << "Position centre moyen total : (" << res[0].second[1]<<", "<< res[0].second[2] <<")"<< std::endl;
    for (int i=1; i<5;i++){
        cout << "Cercle zone " <<i+1<<" : Nombre = "<< res[i].first<<" ; Rayon moyen : "<< res[i].second[0] <<
             " ; Coord centre moyen = ("<<res[i].second[1]<<", "<<res[i].second[2]<<")" <<endl;
    }
*/

