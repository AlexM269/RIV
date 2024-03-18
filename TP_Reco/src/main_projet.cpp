#include <iostream>
#include <fstream>
#include <list>
#include <dirent.h>
#include <windows.h>
#include <array>
#include <vector>


using namespace std;

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

//#include "histogram.hpp"

//#include "text_size.hpp"
//#include "icon_label.hpp"
//#include "redresser_image.h"
//#include "reco_barycentre.hpp"
//#include "reco_lignes.hpp"

#include "feature_extraction.hpp"
#include "circles.hpp"
#include "feature_size.hpp"
#include "zoning.h"
#include "lines.h"
#include "rename_file.hpp"
#include "add_blank.hpp"

int main() {
    int i = 0;

    //ICI : Préciser le dossier auquel on veut acceder
    //const char* dossier = ".//..//out";
    //const char* dossier = ".//..//Exemples_icones";
    const char* dossier = ".//..//final_cropped";

    //Dans le cas du dossier des images de test, on renomme les fichiers des images pour enlever le ".png" en trop puis on les met au même format que nos images
    //rename_file(dossier);
    //addBlank(dossier);


    // Ouvrir le dossier
    DIR* dir = opendir(dossier);

    // Ouverture du fichier en mode écriture (creation)
    std::ofstream fichierARFF("./../FichierARFFtest.arff");
    if (fichierARFF.is_open()) {

        fichierARFF<<"@RELATION ../FichierARFF\n\n";
        fichierARFF<<"@ATTRIBUTE NbPixelsNoirs numeric\n";
        fichierARFF<<"@ATTRIBUTE NbPixelsNoirs_1 numeric\n";
        fichierARFF<<"@ATTRIBUTE NbPixelsNoirs_2 numeric\n";
        fichierARFF<<"@ATTRIBUTE NbPixelsNoirs_3 numeric\n";
        fichierARFF<<"@ATTRIBUTE NbPixelsNoirs_4 numeric\n";
        fichierARFF<<"@ATTRIBUTE NbPixelsNoirs_5 numeric\n";
        fichierARFF<<"@ATTRIBUTE NbPixelsNoirs_6 numeric\n";
        fichierARFF<<"@ATTRIBUTE NbPixelsNoirs_7 numeric\n";
        fichierARFF<<"@ATTRIBUTE NbPixelsNoirs_8 numeric\n";
        fichierARFF<<"@ATTRIBUTE NbPixelsNoirs_9 numeric\n";
        fichierARFF<<"@ATTRIBUTE Hauteur numeric\n";
        fichierARFF<<"@ATTRIBUTE Largeur numeric\n";
        fichierARFF<<"@ATTRIBUTE Air numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreX numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreY numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreX_1 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreY_1 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreX_2 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreY_2 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreX_3 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreY_3 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreX_4 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreY_4 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreX_5 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreY_5 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreX_6 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreY_6 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreX_7 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreY_7 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreX_8 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreY_8 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreX_9 numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreY_9 numeric\n";
        fichierARFF<<"@ATTRIBUTE 1nbCercles numeric\n";
        fichierARFF<<"@ATTRIBUTE 1CercleSize numeric\n";
        fichierARFF<<"@ATTRIBUTE 1CercleX numeric\n";
        fichierARFF<<"@ATTRIBUTE 1CercleY numeric\n";
        fichierARFF<<"@ATTRIBUTE 2nbCercles numeric\n";
        fichierARFF<<"@ATTRIBUTE 2CercleSize numeric\n";
        fichierARFF<<"@ATTRIBUTE 2CercleX numeric\n";
        fichierARFF<<"@ATTRIBUTE 2CercleY numeric\n";
        fichierARFF<<"@ATTRIBUTE 3nbCercles numeric\n";
        fichierARFF<<"@ATTRIBUTE 3CercleSize numeric\n";
        fichierARFF<<"@ATTRIBUTE 3CercleX numeric\n";
        fichierARFF<<"@ATTRIBUTE 3CercleY numeric\n";
        fichierARFF<<"@ATTRIBUTE 4nbCercles numeric\n";
        fichierARFF<<"@ATTRIBUTE 4CercleSize numeric\n";
        fichierARFF<<"@ATTRIBUTE 4CercleX numeric\n";
        fichierARFF<<"@ATTRIBUTE 4CercleY numeric\n";
        fichierARFF<<"@ATTRIBUTE 5nbCercles numeric\n";
        fichierARFF<<"@ATTRIBUTE 5CercleSize numeric\n";
        fichierARFF<<"@ATTRIBUTE 5CercleX numeric\n";
        fichierARFF<<"@ATTRIBUTE 5CercleY numeric\n";
        fichierARFF<<"@ATTRIBUTE linesX_1 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesY_1 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesAngle_1 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesLength_1 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesX_2 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesY_2 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesAngle_2 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesLength_2 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesX_3 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesY_3 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesAngle_3 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesLength_3 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesX_4 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesY_4 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesAngle_4 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesLength_4 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesX_5 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesY_5 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesAngle_5 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesLength_5 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesX_6 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesY_6 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesAngle_6 numeric\n";
        fichierARFF<<"@ATTRIBUTE linesLength_6 numeric\n";
        fichierARFF<<"@ATTRIBUTE class {accident, bomb, car, casualty, electricity, fire, fireBrigade, flood, gas, injury, paramedics, person, police, roadBlock}\n\n";

        fichierARFF<<"@DATA\n";

        if (dir) {
            std::cout<< "Dossier"  <<std::endl;

            // Parcourt les fichiers dans le dossier
            struct dirent *entry;
            while ((entry = readdir(dir)) != nullptr) {
                string nom = entry->d_name;

                if(nom.size() >2) {
                    //Affichage de l'icone
                    std::cout<<to_string(i)<< ":" << nom <<std::endl;
                    i++;

                    //Stockage du nom de l'image
                    string image = string(dossier) + "/" + entry->d_name;
                    string label = nom.substr(0,nom.size()-15);

                    //Si le label est Road Block, concatener les deux mots pour le .ARFF pour former "roadBlock"
                    if(label.find("road block") != std::string::npos) {
                        label = "roadBlock";
                    }


                    //Si le label est Fire brigade, concatener les deux mots pour le .ARFF pour former "fireBrigade"
                    if(label.find("fire brigade") != std::string::npos) {
                        label = "fireBrigade";
                    }


                    //Cropping de l'image
                    pair<pair<int,int>,cv::Mat> new_image = feature_size::extract(image);
                    cv::Mat cropped_image_mat = new_image.second;
                    std::string cropped_image = "../../TP_Reco/cropped_image.png";
                    cv::imwrite(cropped_image,cropped_image_mat);


                    //Génération des différentes zones de l'image et enregistrement dans le fichier temporaire "zoning"
                    vector<cv::Mat> zones = zoning::extract_zones(cropped_image,3);
                    int k = 1;
                    for (cv::Mat zone : zones){
                        nom = to_string(k);
                        k++;
                        std::string path = "../../TP_Reco/zoning/zone_"+nom+".png";
                        cv::imwrite(path,zone);
                    }


                    //Stocke le nombre de pixels noirs de l'image entière puis dans chaque zone
                    int count = countPixel(cropped_image)[1];
                    vector<int> counts;
                    for (int j = 1; j<10;j++){
                        std::string path = "../../TP_Reco/zoning/zone_"+ to_string(j)+".png";
                        int a_count = countPixel (path)[1];
                        counts.push_back(a_count);
                    }


                    //Stocke la hauteur et la largeur
                    pair<int, int> size = new_image.first;


                    //Stocke l'aire de l'image
                    double area = air(image);


                    // Stocke les coordonnées du barycentre sous la forme d'un point
                    Point barycentre = reco_barycentre(cropped_image);
                    //std::cout<<to_string(i)<< ":" << " Avant Barycentre" <<std::endl;

                    vector<Point> barycentres;
                    for (int j = 1; j<10;j++){
                        std::string path = "../../TP_Reco/zoning/zone_"+ to_string(j)+".png";
                        //std::cout<<to_string(j)<< ":" << " Avant reconnaissance" <<std::endl;
                        Point a_barycentre = reco_barycentre (path);
                        //std::cout<<to_string(j)<< ":" << " Apres reconnaissance" <<std::endl;

                        barycentres.push_back(a_barycentre);
                    }
                    //std::cout<<to_string(i)<< ":" << " Apres Barycentre" <<std::endl;


                    //Stocke dans une paire le nombre de cercle d'un côté et
                    // un vecteur contenant des array de taille 3 correspondant
                    // à la taille, la coord X et la coord Y de chaque cercle reconnu
                    //Nb de cercle max = 4
                    array<pair<int, array<int, 3>>,5> cercles = circles::extract_circles(cropped_image);

                    //Stockage des informations données par extract_circles des cercles présents pour chaque zone
                    vector<int> cercles_data ;

                    for(int i = 0; i<5; i++){
                        cercles_data.push_back(cercles[i].first);
                        cercles_data.push_back(cercles[i].second[0]);
                        cercles_data.push_back(cercles[i].second[1]);
                        cercles_data.push_back(cercles[i].second[2]);
                    }

                    //Stockage des lignes présentes dans l'image ainsi que dans chaque zone
                    array<array<float, 4>,6> extracted_lines = lines::extract_lines(cropped_image);


                    //Normalisation des données
                    vector<double> to_normalize;
                    to_normalize.push_back(count);
                    for(int j = 0; j<9; j++){
                        to_normalize.push_back(counts[j]);
                    }
                    to_normalize.push_back(size.first);
                    to_normalize.push_back(size.second);
                    to_normalize.push_back(area);
                    to_normalize.push_back(barycentre.x);
                    to_normalize.push_back(barycentre.y);
                    for(int j = 0; j<barycentres.size(); j++){
                        to_normalize.push_back(barycentres[j].x);
                        to_normalize.push_back(barycentres[j].y);
                    }
                    for(int elt : cercles_data){
                        to_normalize.push_back(elt);
                    }
                    for(int j = 0; j<6; j++){
                        for(int l = 0; l<4; l++){
                            to_normalize.push_back(extracted_lines[j][l]);
                        }
                    }

                    vector <double> normalized_data = normalisation(to_normalize);


                    //Impression des informations récupérées pour chaque imagette dans le fichier ARFF
                    for (double elt : normalized_data){
                        fichierARFF<< elt << ",";
                    }
                    fichierARFF << label <<endl;
                }
            }
        }
        // Fermeture du fichier
        fichierARFF.close();
    }else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }

    //termine le programme lorsqu'une touche est frappee
    waitKey(0);
    return EXIT_SUCCESS;
}
