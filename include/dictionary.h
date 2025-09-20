#ifdef DICTIONARY_H
#ifndef DICTIONARY_H

#include<iostream>
#include<stdio.h>
#include<regex>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

// Read the polyMesh/faces file 
void extractFaces(std::vector<std::vector<std::size_t> >& Faces){
    // Create a file object and open the file
    std::ifstream faceFile("./polyMesh/faces");
    if (!faceFile.is_open()) {
        std::cerr << "Error opening file: " << "./polyMesh/faces" << std::endl;
        return;
    }
    std::string line;
    std::size_t nFaces;
    const std::regex pattern ("(\\(\\s*([\\d\\s]+)\\s*\\))");
    while(std::getline(faceFile,line)){
        std::smatch match;
        if (std::regex_search(line, match, pattern)) {
            std::string inside = match[2].str(); // "1 4 13 10"
            // std::cout << inside << std::endl;

            std::vector<std::size_t> PointIndex; 
            std::istringstream iss (inside);
            std::size_t  idx; 
            while (iss >> idx) {
                PointIndex.push_back(idx);
            }
            Faces.push_back(PointIndex);
        }
        else{
            continue;
        }
    }
    faceFile.close();
}

// Read the polyMesh/points file 
void extractPoints(std::vector<std::vector<double> >& Points){
    std::ifstream pointsFile("./polyMesh/points");
    if (!pointsFile.is_open()) {
        std::cerr << "Error opening file: " << "./polyMesh/points" << std::endl;
        return;
    }
    std::string line;
    std::size_t nFaces;
    // const std::regex pattern ("(\\(\\s*([\\d\\s]+)\\s*\\))");
    const std::regex pattern ("(\\(\\s*([-+]?\\d*\\.?\\d+(?:[eE][-+]?\\d+)?)\\s+([-+]?\\d*\\.?\\d+(?:[eE][-+]?\\d+)?)\\s+([-+]?\\d*\\.?\\d+(?:[eE][-+]?\\d+)?)\\s*\\))");
    while(std::getline(pointsFile,line)){
        std::smatch match;
        if (std::regex_search(line, match, pattern)) {
            std::vector<double> PointsCoord; 
            PointsCoord.push_back(stod(match[2].str()));
            PointsCoord.push_back(stod(match[3].str()));
            PointsCoord.push_back(stod(match[4].str()));
            Points.push_back(PointsCoord);
        }
        else{
            continue;
        }
    }
    pointsFile.close();
}

// Extract owner data 
void extractOwners(std::vector<std::size_t>& Owners){
    std::ifstream ownerFile("./polyMesh/owner");
    if (!ownerFile.is_open()) {
        std::cerr << "Error opening file: " << "./polyMesh/owner" << std::endl;
        return;
    }
    std::string line;
    const std::regex pattern ("^\\d+");
    while(std::getline(ownerFile,line)){
        std::smatch match;
        if (std::regex_search(line, match, pattern)) {
            std::string inside = match[0].str(); // "1 4 13 10"
            // std::cout << inside << std::endl;
            Owners.push_back(std::stoul(inside));
        }
        else{
            continue;
        }
    }
    ownerFile.close();
}

// Extract neighbour data 
void extractNeighbours(std::vector<std::size_t>& Neighbours){
    std::ifstream neighbourFile("./polyMesh/neighbour");
    if (!neighbourFile.is_open()) {
        std::cerr << "Error opening file: " << "./polyMesh/neighbour" << std::endl;
        return;
    }
    std::string line;
    const std::regex pattern ("^\\d+");
    while(std::getline(neighbourFile,line)){
        std::smatch match;
        if (std::regex_search(line, match, pattern)) {
            std::string inside = match[0].str(); // "1 4 13 10"
            // std::cout << inside << std::endl; 
            Neighbours.push_back(std::stoul(inside));

        }
        else{
            continue;
        }
    }
    neighbourFile.close();

}
#endif