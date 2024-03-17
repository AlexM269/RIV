#include "add_blank.hpp"

#include <iostream>
#include <string>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isRegularFile(const std::string& path) {
    struct stat fileInfo;
    if (stat(path.c_str(), &fileInfo) != 0) {
        return false;
    }
    return S_ISREG(fileInfo.st_mode);
}

void addBlank(const std::string& directoryPath) {
    DIR* dir = opendir(directoryPath.c_str());
    if (dir == nullptr) {
        std::cerr << "Error opening directory " << directoryPath << std::endl;
        return;
    }

    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string fileName = entry->d_name;

        // Construire le chemin complet du fichier
        std::string filePath = directoryPath + "/" + fileName;

        // Vérifier si le chemin correspond à un fichier régulier
        if (isRegularFile(filePath)) {
            // Parcourir le nom de fichier et remplacer les underscores
            for (size_t i = 0; i < fileName.size(); ++i) {
                if (fileName[i] == '_' && i > 0 && i < fileName.size() - 1) {
                    if (isAlpha(fileName[i - 1]) && isAlpha(fileName[i + 1])) {
                        fileName[i] = ' ';
                    }
                }
            }

            // Renommer le fichier avec le nouveau nom
            std::string oldPath = directoryPath + "/" + entry->d_name;
            std::string newPath = directoryPath + "/" + fileName;
            if (rename(oldPath.c_str(), newPath.c_str()) != 0) {
                std::cerr << "Error renaming file " << oldPath << std::endl;
            } else {
                std::cout << "Renamed file: " << oldPath << " to " << newPath << std::endl;
            }
        }
    }

    closedir(dir);
}