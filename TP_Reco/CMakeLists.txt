cmake_minimum_required(VERSION 3.14)
project(TP-Reco)


set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

include_directories(include ${OpenCV_INCLUDE_DIRS})


add_executable(TP-Reco
        include/histogram.hpp
        src/main_projet.cpp
        src/text_size.cpp
        src/icon_label.cpp
        include/redresser_image.h
        src/redresser_image.cpp
        include/reco_barycentre.hpp
        src/reco_barycentre.cpp
        src/reco_lignes.cpp
        src/nb_contours.cpp
        include/feature_extraction.hpp
        src/feature_extraction.cpp
        include/circles.hpp
        src/circles.cpp
        src/feature_size.cpp)

target_link_libraries(TP-Reco ${OpenCV_LIBS})

