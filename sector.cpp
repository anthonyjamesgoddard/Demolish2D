#include"sector.h"
#include<algorithm>
#include<iostream>

bool compRadius(std::shared_ptr<Vertex> a, std::shared_ptr<Vertex> b)
{
    return a->getRadius() < b->getRadius();
}

void demolish::world::Sector::generateLoDs()
{
    std::sort(_LoD[0].begin(),_LoD[0].end(),compRadius);

    // the sectors are now sorted from largest to smallest.
    // radially speaking

    
    int numberOfVertsInSector = _LoD[0].size();
    auto temp = _LoD[0];
    for(int i=1;i<numberOfVertsInSector-2;i++)
    {
        temp.pop_back();
        _LoD.push_back(temp);
    }
    
    // BEFORE THE FUNCTION ENDS SORT WITH RESPECT TO THETA AGAIN
    //
    //
    // THIS IS FU**ING ESSENTIAL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
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
