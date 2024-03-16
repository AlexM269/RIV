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