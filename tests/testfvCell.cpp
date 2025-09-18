#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<vector>
#include"../include/utilities.h"
#include"../include/dictionary.h"
#include"../include/fvCell.h"

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

    fvCell A(3,Owners,Neighbours);
    A.displayFaceIndices();
    A.displayFaceSigns();

    return 0;    
}