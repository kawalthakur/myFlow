#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<vector>
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

    std::vector<std::vector<double> > Points;
    extractPoints(Points);
    // for(auto a : Points){
    //     for(int i = 0; i < a.size() ; i++){
    //         std::cout << a[i] << "," ;
    //     }
    //     std::cout << std::endl;
    // }
    std::vector<std::size_t> Neighbours;
    extractNeighbours(Neighbours);
    std::vector<std::size_t> Owners;
    extractOwners(Owners);

    return 0;    
}