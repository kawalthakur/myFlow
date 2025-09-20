#ifdef FV_CELL_H
#ifndef FV_CELL_H
#include<iostream>
#include "./Vector.h"
// #include "./Face.H"
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
    private:    
            std::size_t Index;
            Vector Centre;
            double CellVolume;
            // This vector should be of the Type Faces 
            // std::vector<Face> FaceList;
            std::vector<std::size_t> FaceIndices;
            std::vector<int> FaceSign;
            std::vector<std::size_t> NeighbourCells;


    public: 
            // Methods to Calculate all the stuff 
            fvCell(int Index_,std::vector<std::size_t>& OwnerList, std::vector<std::size_t>& NeighbourList);
            void displayFaceIndices();
            void displayFaceSigns();
};

fvCell::fvCell(int Index_,std::vector<std::size_t>& OwnerList,std::vector<std::size_t>& NeighbourList){
    // We need to access the owners field. 
    this->Index = Index_ ; 
    auto iter = OwnerList.begin();
    while((iter = std::find(iter,OwnerList.end(),this->Index)) != OwnerList.end()){
        FaceIndices.push_back((std::size_t)std::distance(OwnerList.begin(),iter));
        FaceSign.push_back(1);  // Since cell is the owner for this face. 
        ++iter ; 
    }
    // While the starting faces are the internal faces we need to also check for the NeighbourList 
    auto iter2 = NeighbourList.begin();
    while((iter2 = std::find(iter2,NeighbourList.end(),this->Index)) != NeighbourList.end()){
        FaceIndices.push_back((std::size_t)std::distance(NeighbourList.begin(),iter2));
        FaceSign.push_back(-1);     // Since cell is the neighbour for this face. 
        ++iter2 ;
    }

    // Finally we need to sort the face indices 

} 

void fvCell::displayFaceIndices(){
    std::cout << "The Face Index for Cell no. " << this-> Index << " is: ( ";
    for(int i = 0 ; i < this->FaceIndices.size() ; i++){
        std::cout << this->FaceIndices[i] << " " ; 
    }
    std::cout << ")" << std::endl ; 
}

void fvCell::displayFaceSigns(){
    std::cout << "The Face Sign for Cell no. " << this-> Index << " is: ( ";
    for(int i = 0 ; i < this->FaceSign.size() ; i++){
        std::cout << this->FaceSign[i] << " " ; 
    }
    std::cout << ")" << std::endl ; 
}

#endif