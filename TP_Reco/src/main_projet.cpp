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

int main() {

    int i = 0;

    const char* dossier = ".//..//out";
    //const char* dossier = ".//..//Exemples_icones";

    // Ouvrir le dossier
    DIR* dir = opendir(dossier);

    // Ouverture du fichier en mode écriture (creation)
    std::ofstream fichierARFF("./../FichierARFF.arff");
    if (fichierARFF.is_open()) {

        fichierARFF<<"@RELATION ../FichierARFF\n\n";
        fichierARFF<<"@ATTRIBUTE NbPixelsNoirs numeric\n";
        fichierARFF<<"@ATTRIBUTE Hauteur numeric\n";
        fichierARFF<<"@ATTRIBUTE Largeur numeric\n";
        fichierARFF<<"@ATTRIBUTE Air numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreX numeric\n";
        fichierARFF<<"@ATTRIBUTE barycentreY numeric\n";
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
                    if(std::equal(label.begin(), label.end(),"road block")){
                        label = "roadBlock";
                    }

                    //Si le label est Fire brigade, concatener les deux mots pour le .ARFF pour former "fireBrigade"
                    if(std::equal(label.begin(), label.end(),"fire brigade")){
                        label = "fireBrigade";
                    }

                    //Cropping de l'image
                    pair<pair<int,int>,cv::Mat> new_image = feature_size::extract(image);
                    cv::Mat cropped_image_mat = new_image.second;
                    std::string cropped_image = "../../TP_Reco/cropped_image.png";
                    cv::imwrite(cropped_image,cropped_image_mat);

                    cv::imshow("Image rognee",cropped_image);

                    //Stocke le nombre de pixels noirs
                    vector<int> count = countPixel(cropped_image);

                    //Stocke la hauteur et la largeur de l'image
                    pair<int, int> size = extractSize(image);

                    //Stocke l'aire de l'image
                    double area = air(image);

                    // Stocke les coordonnées du barycentre sous la forme d'un point
                    Point barycentre = reco_barycentre(image);

                    //Stocke dans une paire le nombre de cercle d'un côté et
                    // un vecteur contenant des array de taille 3 correspondant
                    // à la taille, la coord X et la coord Y de chaque cercle reconnu
                    //Nb de cercle max = 4
                    array<pair<int, array<int, 3>>,5> cercles = circles::extract_circles(image);
                    //cout << "Cercles: " << cercles.first << "," << cercles.second << endl;

                    //Stockage des informations données par extract_circles des cercles présents pour chaque zone
                    vector<int> cercles_data ;

                    for(int i = 0; i<5; i++){
                        cercles_data.push_back(cercles[i].first);
                        cercles_data.push_back(cercles[i].second[0]);
                        cercles_data.push_back(cercles[i].second[1]);
                        cercles_data.push_back(cercles[i].second[2]);
                    }


                    //Impression des informations récupérées pour chaque imagette dans le fichier ARFF
                    fichierARFF << count[1] << "," << size.first << "," << size.second << ","<< area <<","<< barycentre.x << ","<< barycentre.y<<","<<
                    cercles_data[0]<< "," << cercles_data[1] << "," << cercles_data[2] << "," << cercles_data[3] << "," <<
                    cercles_data[4]<< "," << cercles_data[5] << "," << cercles_data[6] << "," << cercles_data[7] << "," <<
                    cercles_data[8]<< "," << cercles_data[9] << "," << cercles_data[10] << "," << cercles_data[11] << "," <<
                    cercles_data[12]<< "," << cercles_data[13] << "," << cercles_data[14] << "," << cercles_data[15] << "," <<
                    cercles_data[16]<< "," << cercles_data[17] << "," << cercles_data[18] << "," << cercles_data[19] << "," <<
                    label<<endl;
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
    return EXIT_SUCCESS;}

/*
int main (void){
    // Spécifie le chemin du dossier à parcourir
    const char* dossier = ".//..//Exemples_icones";

    // Ouvre le dossier
    DIR* dir = opendir(dossier);

    if (dir) {
        // Parcoure les fichiers dans le dossier
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            //extrait le nom du fichier actuel dans la variable nom
            std::string nom = entry->d_name;

            // Ignore les répertoires spéciaux "." et ".."
            if(nom.size()>3){
                // Crée le chemin du nouveau fichier dans un dossier différent
                string outputPath = "../Exemples_resultat/" + nom;

                // Cree une image im où on ajoute un barycentre à l'image
                cv::Mat im = reco_barycentre(".//..//Exemples_icones/" + nom);
                // Enregistre l'image avec le centre de masse
                cv::imwrite(outputPath, im);
            }
        }
        // Ferme le dossier
        closedir(dir);
    } else {
        std::cerr << "Erreur lors de l'ouverture du dossier2." << std::endl;
        return 1;
    }

    //Test de la reconnaissance de lignes
    std::string imName = ".//..//accident_004_01_3_3.jpg";
    cv::Mat result = reco_lignes (imName);


    //termine le programme lorsqu'une touche est frappee
    waitKey(0);
    return EXIT_SUCCESS;
}
*/