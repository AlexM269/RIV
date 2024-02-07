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


int main (void){
    //Cree une liste contenant les nombres de contours de chaque image
    list<int> nb_contours;

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
