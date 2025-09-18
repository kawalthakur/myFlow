#include<iostream>
#include "./Vector.h"
#include "./Face.H"
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
            Vector Centre(0,0,0);
            std::double CellVolume;
            // This vector should be of the Type Faces 
            // std::vector<Face> FaceList;
            std::vector<int> FaceSign;
            std::vector<std::size_t> NeighbourCells;


    private: 
            // Methods to Calculate all the stuff 
            fvCell(){
                // We need to access the owners field. 
            }
};