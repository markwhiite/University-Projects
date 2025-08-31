#include "Zone.h"
#include "Commercial.h"
#include <iostream>
#include <vector>
using namespace std;

void updateCommercial(std::vector<std::vector<Zone>> &region, int &availableWorkers, int &availableGoods){
    int count = 0;
    for(int i = 0; i<region.size(); i++){
        for(int j =0; j<region[i].size(); j++){
            
            if(region[i][j].GetType()=='C'){ // check for residential
                vector<Zone*> tempAdjacent = region[i][j].GetAdjacent();
                if(region[i][j].GetPopulation()==0){ //1st case population = 0
                    for(Zone* z: tempAdjacent){
                        if((z->GetType()=='T'|| z->GetType()=='#'|| z->GetType()=='P') && (availableGoods>=1 && availableWorkers>=1)){ //if zone is adjacent to powerline, workers>=1, goods>=1
                            region[i][j].SetPopulation(region[i][j].GetPopulation()+1); //increment population
                            availableWorkers--;
                            availableGoods--;
                            break;
                        }

                        else if(z->GetPopulation()>=1 && availableGoods>=1 && availableWorkers>=1){ // check population requirements
                            region[i][j].SetPopulation(region[i][j].GetPopulation()+1); //increment population
                            availableWorkers--;
                            availableGoods--;
                            break;
                        }
                    }
                }
                //END OF 1ST CASE 

                //BEGIN 2ND CASE
                else if(region[i][j].GetPopulation()==1){ //2nd case population =1
                    for(Zone* z: tempAdjacent){
                        if(z->GetPopulation()>=1){
                            count++;
                        }
                    }
                    if(count>=2 && availableGoods>=1 && availableWorkers>=1){
                        region[i][j].SetPopulation(region[i][j].GetPopulation()+1);
                        availableWorkers--;
                        availableGoods--;
                    }
                    count =0;
                }

                //END OF SECOND CASE

                
            }
        }
    }
    
}
