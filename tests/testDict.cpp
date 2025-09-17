#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<vector>
#include"../include/utilities.h"
#include"../include/dictionary.h"
int main(){
    std::vector<std::vector<std::size_t> > Faces;
    extractFaces(Faces);
    // for(auto a : Faces){
    //     for(int i = 0; i < a.size() ; i++){
    //         std::cout << a[i] << "," ;
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << "Displaying Faces" << std::endl;
    dispArray(Faces);

    std::vector<std::vector<double> > Points;
    extractPoints(Points);
    // for(auto a : Points){
    //     for(int i = 0; i < a.size() ; i++){
    //         std::cout << a[i] << "," ;
    //     }
    //     std::cout << std::endl;
    // }
    std::cout << "Displaying Points" << std::endl;
    dispArray(Points);

    std::vector<std::size_t> Owners;
    extractOwners(Owners);

    std::vector<std::size_t> Neighbours;
    extractNeighbours(Neighbours);

    return 0;    
}