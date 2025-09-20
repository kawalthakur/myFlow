#ifndef MESH_DATA_H
#define MESH_DATA_H

#include<iostream>
#include<stdio.h>
#include<regex>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
// #include"../include/utilities.h"
#include "dictionary.h"
#include "node.h"
#include "fvCell.h"
// #include "fvFace.h"

class meshData{
    // This class clubs all polyMesh data into a single object. 
    // This is useful while creating the fundamental blocks like Nodes, Cells and Faces. 
    private:    
        //     std::vector<std::vector<std::size_t>> FaceList;
        //     std::vector<std::vector<std::size_t>> PointList;
        //     std::vector<std::size_t> OwnerList;
        //     std::vector<std::size_t> NeighbourList;

            std::vector<node> nodeList;
        //     std::vector<fvFace> faceList;
            std::vector<fvCell> cellList;
    
    public: 
            // Here we can define functions to extract data from the polyMesh folder. 
            meshData(); 
            void displayNodes();
            
};

meshData::meshData(){
        // Initialise the Node centroid from the point data 
        std::vector<std::vector<double> > points_ ;
        extractPoints(points_);
        // nodeList.reserve(points_.size());
        nodeList.resize(points_.size());
        for(std::size_t i = 0 ; i < points_.size(); i++){
                nodeList[i].setIndex(i);
                nodeList[i].setCentroid(Point(points_[i]));
        } 

        // Extract the faces and this time also initialise the node iFace if the point index matches
        std::vector<std::vector<std::size_t> > faces_;
        extractFaces(faces_);
        for(std::size_t i = 0 ; i < faces_.size() ; i++){
                for(int j = 0 ; j < faces_[i].size() ; j++){
                        // push the Node index accordingly .
                        nodeList[faces_[i][j]].pushFaceIndex(i);         
                }
        } 
}

void meshData::displayNodes(){
        for(std::size_t i = 0 ; i < this->nodeList.size(); i++){
                this->nodeList[i].displayNode();
        }
}

#endif