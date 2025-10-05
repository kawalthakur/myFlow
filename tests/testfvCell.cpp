#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<vector>
#include"../include/utilities.h"
#include"../include/dictionary.h"
#include"../include/fvCell.h"
#include"../include/fvFace.h"
#include"../include/Point.h"

int main(){
    std::vector<std::vector<std::size_t> > Faces;
    extractFaces(Faces);
    std::vector<std::vector<double> > Points;
    extractPoints(Points);
    std::vector<std::size_t> Owners;
    extractOwners(Owners);
    Owners.erase(Owners.begin());
    std::vector<std::size_t> Neighbours;
    extractNeighbours(Neighbours);
    Neighbours.erase(Neighbours.begin());

    // Create a Node List from the Mesh data 
    std::vector<node> NodeList;
    for(std::size_t i=0 ; i < Points.size() ; i++){
        NodeList.push_back(node(i,Point(Points[i][0],Points[i][2],Points[i][3])));
    }

    fvFace faces(Faces, Points, Owners, Neighbours);

    // fvCell A(3,Owners,Neighbours);
    // A.displayFaceIndices();
    // A.displayFaceSigns();

    return 0;    
}