#ifndef FV_CELL_H
#define FV_CELL_H

#include<iostream>
#include "Vector.h"
#include "fvFace.h"
#include "Node.h"
#include "utilities.h"
/* 
This is the finite Volume cell object 
    This object contains the following data 
    -> Faces indices on a cell 
    -> Cell Centroid 
    -> Cell Volume 
    -> Cell Index 
    -> Neighbour Cell Indices 
    -> Face sign  (1 if the element is owner for that face, -1 if element is neighbour for that face )
*/

class fvCell{
    public:  
            std::size_t index;
            std::vector<std::size_t> iNeighbour;
            std::vector<std::size_t> iFaces;
            std::vector<std::size_t> iNodes;
            double volume;
            std::vector<int> faceSign;
            int numberOfNeighbours;
            Point centroid;
            // Methods to Calculate all the stuff 
            fvCell(std::size_t index_,
                   std::vector<std::size_t>& ownerList, 
                   std::vector<std::size_t>& neighbourList,
                   std::vector<fvFace>& faceList,std::vector<node>& nodeList
                   );
            void debug();
            // void displayFaceIndices();
            // void displayFaceSigns();
};

fvCell::fvCell(std::size_t index_,
               std::vector<std::size_t>& ownerList,
               std::vector<std::size_t>& neighbourList, 
               std::vector<fvFace>& faceList, std::vector<node>& nodeList){
    // Initialize the iFaces from the ownerList 
    this->index = index_ ; 
    auto iter = ownerList.begin();
    while((iter = std::find(iter,ownerList.end(),this->index)) != ownerList.end()){
        iFaces.push_back((std::size_t)std::distance(ownerList.begin(),iter));
        faceSign.push_back(1);  // Since cell is the owner for this face. 
        ++iter ; 
    }
    // Add additional faces indices iFaces from the neighbourList 
    auto iter2 = neighbourList.begin();
    while((iter2 = std::find(iter2,neighbourList.end(),this->index)) != neighbourList.end()){
        iFaces.push_back((std::size_t)std::distance(neighbourList.begin(),iter2));
        faceSign.push_back(-1);     // Since cell is the neighbour for this face. 
        ++iter2 ;
    }

    // Initialise the iNodes from iFaces and the faceList
    for(int i = 0 ; i < this->iFaces.size() ; i++ ){
        std::vector<std::size_t> nodes = faceList[this->iFaces[i]].FaceData.iNodes_;
        for(int j = 0 ; j < nodes.size() ; j++){
            this->iNodes.push_back(nodes[j]);
        }
    }
    // Since we only want the unique indices of the Nodes 
    sort(this->iNodes.begin(), this->iNodes.end());
    std::vector<int>::iterator it;
    it = std::unique(this->iNodes.begin(), this->iNodes.end());  
    this->iNodes.resize(distance(this->iNodes.begin(),it)); 

    // Calculating the centroid from the Nodes 
    double Gx=0.0,Gy=0.0,Gz=0.0;
    for(int i = 0 ; i < iNodes.size() ; i++){
        Gx += nodeList[this->iNodes[i]].getCentroid().X();
        Gy += nodeList[this->iNodes[i]].getCentroid().Y();
        Gz += nodeList[this->iNodes[i]].getCentroid().Z();
    }
    Gx = Gx /(iNodes.size());
    Gy = Gy /(iNodes.size());
    Gz = Gz /(iNodes.size());
    this->centroid = Point(Gx,Gy,Gz);

} 

void fvCell::debug(){
    std::cout<< "Index : " << this->index;
    std::cout<< "iFaces : ";
    displayVector(this->iFaces);
    std::cout<< "iNodes : ";
    displayVector(this->iNodes);
    std::cout << "centroid : ";
    displayPoint(this->centroid);
}

// void fvCell::displayFaceIndices(){
//     std::cout << "The Face Index for Cell no. " << this-> Index << " is: ( ";
//     for(int i = 0 ; i < this->FaceIndices.size() ; i++){
//         std::cout << this->FaceIndices[i] << " " ; 
//     }
//     std::cout << ")" << std::endl ; 
// }

// void fvCell::displayFaceSigns(){
//     std::cout << "The Face Sign for Cell no. " << this-> Index << " is: ( ";
//     for(int i = 0 ; i < this->FaceSign.size() ; i++){
//         std::cout << this->FaceSign[i] << " " ; 
//     }
//     std::cout << ")" << std::endl ; 
// }

#endif