#include <iostream>
#include <string>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>
#include <regex>
#include <iomanip> // pour std::setw et std::setfill

std::string formatFileName(const std::string& oldName) {
    // Utilisation d'expressions régulières pour extraire le préfixe et les nombres
    std::regex regex("([a-zA-Z_]+)_([0-9]+)_([0-9]+)_([0-9]+)_([0-9]+)(\\.png)");
    std::smatch match;

    if (std::regex_search(oldName, match, regex)) {
        // Extraire le préfixe et les nombres
        std::string prefix = match[1].str();
        std::string numbers[4];
        for (int i = 2; i <= 5; ++i) {
            std::string numStr = match[i].str();
            if(i == 3) // Deuxième nombre
                numbers[i - 2] = std::string(2 - numStr.length(), '0') + numStr;
            else
                numbers[i - 2] = std::string((i == 2) ? 3 - numStr.length() : 1 - numStr.length(), '0') + numStr;
        }

        // Construire le nouveau nom de fichier
        std::string newFileName = prefix + "_";
        for (int i = 0; i < 4; ++i) {
            newFileName += numbers[i] + (i < 3 ? "_" : "");
        }
        newFileName += ".png";
        return newFileName;
    }

    // Retourner l'ancien nom s'il ne correspond pas au modèle attendu
    return oldName;
}

void rename_file(const std::string& folderPath){
    if (folderPath.empty()) {
        std::cerr << "Folder path is empty." << std::endl;
        return;
    }

    DIR* dir = opendir(folderPath.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_name[0] != '.') {
                std::string oldName = entry->d_name;
                if (oldName.size() > 4 && oldName.substr(oldName.size() - 4) == ".png") {
                    std::string oldPath = folderPath + "/" + oldName;
                    std::string newName = folderPath + "/" + formatFileName(oldName);

                    struct stat fileStat;
                    if (stat(oldPath.c_str(), &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
                        if (rename(oldPath.c_str(), newName.c_str()) == 0) {
                            std::cout << "Renamed: " << oldName << " -> " << newName << std::endl;
                        } else {
                            std::cerr << "Failed to rename: " << oldName << std::endl;
                        }
                    } else {
                        std::cerr << "Not a regular file: " << oldName << std::endl;
                    }
                }
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Failed to open directory: " << folderPath << std::endl;
    }
}

/*
#include <iostream>
#include <string>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>

void rename_file(const std::string& folderPath){
    if (folderPath.empty()) {
        std::cerr << "Folder path is empty." << std::endl;
        return;
    }

    DIR* dir = opendir(folderPath.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            // On vérifie si le nom de fichier ne commence pas par '.' pour ignorer les fichiers cachés
            if (entry->d_name[0] != '.') {
                std::string oldName = entry->d_name;
                if (oldName.size() > 4 && oldName.substr(oldName.size() - 4) == ".png") {
                    std::string oldPath = folderPath + "/" + oldName;
                    std::string newName = folderPath + "/" + oldName.substr(0, oldName.size() - 4);

                    struct stat fileStat;
                    if (stat(oldPath.c_str(), &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
                        if (rename(oldPath.c_str(), newName.c_str()) == 0) {
                            std::cout << "Renamed: " << oldName << " -> " << oldName.substr(0, oldName.size() - 4) << std::endl;
                        } else {
                            std::cerr << "Failed to rename: " << oldName << std::endl;
                        }
                    } else {
                        std::cerr << "Not a regular file: " << oldName << std::endl;
                    }
                }
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Failed to open directory: " << folderPath << std::endl;
    }
}
 */