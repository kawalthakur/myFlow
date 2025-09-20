#ifdef NODE_H
#ifndef NODE_H
#include<iostream>
#include<vector>
#include "Point.h"

class node{
    private: 
            std::size_t index; 
            Point centroid ; 
            std::vector<std::size_t> iFaces;
            std::vector<std::size_t> iCells;
    
    public: 
            node(std::size_t index_=0, Point centroid_(0,0,0));
            void setCentroid(Point C);
            void pushFaceIndex(std::size_t iFace);
};

node::node(std::size_t index_, Point centroid){
    this->index = index_;
    this->centroid = centroid_;
}

void node::setCentroid(Point C){
    this->centroid = C;
}

void node::pushFaceIndex(std::size_t iFace){
    iFaces.push_back(iFace);
}
#endif