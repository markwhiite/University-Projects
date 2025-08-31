#include "Zone.h"
#include "Industrial.h"
#include<iostream>
#include<vector>
using namespace std;

void updateIndustrial(std::vector<std::vector<Zone> > &region, int &availableWorkers, int &availableGoods){
    int count = 0;
    for(int i = 0; i<region.size(); i++){
        for(int j =0; j<region[i].size(); j++){
            
            if(region[i][j].GetType()=='I'){ // check for residential
                vector<Zone*> tempAdjacent = region[i][j].GetAdjacent();
                if(region[i][j].GetPopulation()==0){ //1st case population =0
                    for(Zone* z: tempAdjacent){
                        if((z->GetType()=='T'||z->GetType()=='#'||z->GetType()=='P') && availableWorkers>=2){ //if zone is adjacent to powerline
                            region[i][j].SetPopulation(region[i][j].GetPopulation()+1); //increment population
                            availableWorkers-=2;
                            availableGoods++;
                            break;
                        }

                        else if(z->GetPopulation()>=1 && availableWorkers>=2){// check population requirements
                            region[i][j].SetPopulation(region[i][j].GetPopulation()+1); //increment population
                            availableWorkers-=2;
                            availableGoods++;
                            break;
                        }
                    }
                    count =0;
                }

                //END 1ST CASE



                //BEGIN 2ND CASE
                else if(region[i][j].GetPopulation()==1){ //2nd case population =1
                    for(Zone* z: tempAdjacent){
                        if(z->GetPopulation()>=1){
                            count++;
                        }
                    }
                    if(count>=2 && availableWorkers>=2){
                        region[i][j].SetPopulation(region[i][j].GetPopulation()+1);
                        availableWorkers-=2;
                        availableGoods++;
                    }
                    count =0;
                }

                //END SECOND CASE

                //BEGIN THIRD CASE
                else if(region[i][j].GetPopulation()==2){ //2nd case population =1
                    for(Zone* z: tempAdjacent){
                        if(z->GetPopulation()>=2){
                            count++;
                        }
                    }
                    if(count>=4 && availableWorkers>=2){ //4 zones with population of 2 and >=2 available workers
                        region[i][j].SetPopulation(region[i][j].GetPopulation()+1);
                        availableWorkers-=2;
                        availableGoods++;
                    }
                    count =0;
                }

                //END THIRD CASE
                
            }
        }
    }
    
}