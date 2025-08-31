#include "Residential.h"
#include "Zone.h"
#include <iostream>
#include <vector>
//#include "globalFile.h"
using namespace std;

void updateResidential(vector<vector<Zone>> &region, int &availableWorkers){
    int count = 0;
    for(int i = 0; i<region.size(); i++){
        for(int j =0; j<region[i].size(); j++){
            
            if(region[i][j].GetType()=='R'){ // check for residential
                vector<Zone*> tempAdjacent = region[i][j].GetAdjacent();
                if(region[i][j].GetPopulation()==0){ //1st case population =0
                    for(Zone* z: tempAdjacent){
                        if(z->GetType()=='T'||z->GetType()=='#'||z->GetType()=='P'){ //if zone is adjacent to powerline
                            region[i][j].SetPopulation(region[i][j].GetPopulation()+1); //increment population
                            availableWorkers++;
                            break;
                        }

                        else if(z->GetPopulation()>=1){ // check population requirements
                            count++;
                        }
                    }

                    //check if two zones had population
                    if(count>=2){
                        region[i][j].SetPopulation(region[i][j].GetPopulation()+1); //increment population
                        availableWorkers++;
                    }   
                    
                    count =0;
                }

                //BEGIN 2ND CASE
                else if(region[i][j].GetPopulation()==1){ //2nd case population =1
                    for(Zone* z: tempAdjacent){
                        if(z->GetPopulation()>=1){
                            count++;
                        }
                    }
                    if(count>=2){
                        region[i][j].SetPopulation(region[i][j].GetPopulation()+1);
                        availableWorkers++;
                    }
                    count =0;
                }

                //END SECOND CASE

                //BEGIN THIRD CASE
                else if(region[i][j].GetPopulation()==2)
                {
                    for(Zone* z: tempAdjacent){
                        if(z->GetPopulation()>=2){
                            count++;
                        }
                    }
                    if(count>=4){
                        region[i][j].SetPopulation(region[i][j].GetPopulation()+1);
                        availableWorkers++;
                    } 
                    count =0;
                }

                //END THIRD CASE

                //BEGIN FOURTH CASE
                else if(region[i][j].GetPopulation()==3)
                {
                    for(Zone *z: tempAdjacent){
                        if(z->GetPopulation()>=3){
                            count++;
                        }
                    }
                    if(count>=6){
                        region[i][j].SetPopulation(region[i][j].GetPopulation()+1);
                        availableWorkers++;
                    } 
                    count =0;
                }
                //END FOURTH CASE
                else if(region[i][j].GetPopulation()==4)
                {
                    for(Zone *z: tempAdjacent){
                        if(z->GetPopulation()>=4){
                            count++;
                        }
                    }
                    if(count>=8){
                        region[i][j].SetPopulation(region[i][j].GetPopulation()+1);
                        availableWorkers++;
                    } 
                    count =0;
                }
                
            }
        }
    }
}