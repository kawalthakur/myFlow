#ifdef MESH_DATA_H
#ifndef MESH_DATA_H
#include<iostream>
#include<stdio.h>
#include<regex>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

class meshData{
    // This class clubs all polyMesh data into a single object. 
    // This is useful while creating the fundamental blocks like Nodes, Cells and Faces. 
    private:    
            std::vector<std::vector<std::size_t>> FaceList;
            std::vector<std::vector<std::size_t>> PointList;
            std::vector<std::size_t> OwnerList;
            std::vector<std::size_t> NeighbourList;
    
    public: 
            // Here we can define functions to extract data from the polyMesh folder. 
            
};
