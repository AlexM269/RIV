#include <iostream>
#include <fstream>
#include <list>
#include <dirent.h>
#include <windows.h>


using namespace std;

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

#include "histogram.hpp"

#include "text_size.hpp"
#include "icon_label.hpp"
#include "redresser_image.h"
#include "reco_barycentre.hpp"
#include "reco_lignes.hpp"
#include "nb_contours.hpp"


int main (void){
    //Cree une liste contenant les nombres de contours de chaque image
    list<int> list_nb_contours;

    //Cree une liste contenant les centres de masse de chaque image
    list<cv::Point> list_center_of_mass;

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
                //string outputPath = "../Exemples_resultat/" + nom;

                // Cree une image im où on ajoute un barycentre à l'image
                //cv::Mat im = reco_barycentre(".//..//Exemples_icones/" + nom);
                // Enregistre l'image avec le centre de masse
                //cv::imwrite(outputPath, im);

                //Ajoute à la liste le nombre de contours
                list_nb_contours.push_back(nb_contours(".//..//Exemples_icones/" + nom));

                //Ajoute à la liste le centre de masse
                list_nb_contours.push_back(reco_barycentre(".//..//Exemples_icones/" + nom));
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

    //Test de la reconnaissance du nombre de contours
    std::cout<< "Nombres de contours : "<<std::endl;
    for (int i = 0; i < list_nb_contours.size(); i++){
        std::cout<< i <<"e image : "<<list_nb_contours.front()<<
        " ; ("<< list_center_of_mass.front().x<<","<<list_center_of_mass.front().y<<")"<<std::endl;

        //Supprime le premier élément des listes
        list_nb_contours.pop_front();
    }

    //termine le programme lorsqu'une touche est frappee
    waitKey(0);
    return EXIT_SUCCESS;
}
