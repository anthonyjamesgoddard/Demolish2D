#include"sector.h"
#include<algorithm>
#include<iostream>

bool compRadius(std::shared_ptr<Vertex> a, std::shared_ptr<Vertex> b)
{
    return a->getRadius() < b->getRadius();
}

int demolish::world::Sector::generateNextLoD()
{
    // we need to prune the vertices with the largest values of the radius 
    // from the finest level of detail
    return 0;
}

void demolish::world::Sector::displayContents()
{
   std::cout << _theta1 << " " << _theta2 << std::endl; 
   std::cout << "the finest level of detail is:" << std::endl;
   for(auto&vert:_finestLoD)
   {
       vert->displayProperties();
   }
   std::cout << "the layers in increasing levels of detail are given by" << std::endl;
   int LoDSz = _LoD.size();
   for(int i=0;i<LoDSz;i++)
   {
       int tempSz = _LoD[i].size();
       std::cout << "Layer " << i << " vertices" << std::endl;
       for(int j=0;j<tempSz;j++)
       {
           _LoD[i][j]->displayProperties();
       }
   }
}
