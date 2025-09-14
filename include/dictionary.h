#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<vector>

// Read the polyMesh data 
void readData(std::vector<std::vector<std::size_t>>& Faces, std::string& FileName ){
    // Create a file object and open the file
    std::ifstream faceFile(FileName);
    if (!faceFile.is_open()) {
        std::cerr << "Error opening file: " << FileName << std::endl;
        return;
    }
    std::string line;
    // Example: skip header or parse as needed
    while (std::getline(faceFile, line)) {
        std::cout << line << std::endl; // just printing for now
    }
    faceFile.close()
}