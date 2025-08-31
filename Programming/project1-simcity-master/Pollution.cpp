#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Pollution.h"
#include "Zone.h"
#include <vector>
using namespace std;

void updatePollution(std::vector<std::vector<Zone> > &region){
int max = 0; //finds the max amount of times to run through the region

	for(int i = 0; i<region.size(); i++){ //rows
		for(int j =0; j<region[i].size(); j++){ //cols
			if(region[i][j].GetPopulation()>max)
				max = region[i][j].GetPopulation();
			
			if(region[i][j].GetType()=='I') //Set industrial zone to its population (this is pre updating pollution)
				region[i][j].SetPollution(region[i][j].GetPopulation());
			
		}
	}

	for(int runs = 0; runs<max; runs++)
	{
		for(int i = 0; i<region.size(); i++){
			for(int j =0; j<region[i].size(); j++){
				
				
				vector<Zone*> tempAdjacent = region[i][j].GetAdjacent();
				 for(Zone* z: tempAdjacent){ //for each loop running through neighbors
					if(z->GetPollution()>region[i][j].GetPollution()) //check to see if neighbor is more polluted
					{
						region[i][j].SetPollution(z->GetPollution()-1); //update current zone's pollution
					}
				}
			}
		}

	}
}


