#include"sector.h"

#include<iostream>


void demolish::world::Sector::generateLoDs()
{
    // sort each vertex in the sector in terms
    // of thier radial coordinate

}

void demolish::world::Sector::displayContents()
{
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
