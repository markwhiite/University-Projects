#include "Zone.h"
#include <iostream>
#include <vector>
using namespace std;
//constructors

Zone::Zone(){
    type = ' ';
    population = 0;
    pollution = 0;
    cordA = -1;
    cordB = -1;
    
}

Zone::Zone(char type, int population=0, int pollution=0, int cordA=-1, int cordB=-1){
    this->type = type;
    this->population = population;
    this->pollution = pollution;
    this->cordA = cordA;
    this->cordB = cordB;
}

//mutators
void Zone::SetType(char type){
    this->type = type;
}

void Zone::SetPopulation(int population){
    this->population = population;
}

void Zone::SetPollution(int pollution){
    this->pollution = pollution;    
}

void Zone::SetCords(int cordA, int cordB){
    this->cordA = cordA;
    this->cordB = cordB;
}

//accessors
char Zone::GetType(){
    return type;
}

int Zone::GetPopulation(){
    return population;
}

int Zone::GetPollution(){
    return pollution;
}

int Zone::GetCordA(){
    return cordA;
}

int Zone::GetCordB(){
    return cordB;
}

void Zone::PrintPopulation(){
    cout<<population;
}

void Zone::PrintPollution(){
    cout<<pollution;
}

vector<Zone*> Zone::GetAdjacent(){
    return adjacent;
}

//operator
void Zone::operator = (const Zone &Z){
    type = Z.type;
    population = Z.population;
    pollution = Z.pollution;
}



//SetAdjacent function
//Add neighbors to adjaceny list
void Zone::SetAdjacency(vector<vector<Zone>> &region){
    int colLen = region[0].size()-1;
    int rowLen = region.size()-1;
    if(cordA==0)
    {
        if(cordB==0) // top left
        {
            adjacent.push_back(&region[0][1]);
            adjacent.push_back(&region[1][0]);
            adjacent.push_back(&region[1][1]);
        }
        else if(cordB==colLen){  // top right
            adjacent.push_back(&region[0][colLen-1]);
            adjacent.push_back(&region[1][colLen-1]);
            adjacent.push_back(&region[1][colLen]);
        }
        else{ // top row, not on either end
            adjacent.push_back(&region[0][cordB-1]);
            adjacent.push_back(&region[0][cordB+1]);
            adjacent.push_back(&region[1][cordB-1]);
            adjacent.push_back(&region[1][cordB]);
            adjacent.push_back(&region[1][cordB+1]);
            
        }
        return;
    }
    if(cordB==0){
        if(cordA == rowLen){ // bottom left
            adjacent.push_back(&region[rowLen][1]);
            adjacent.push_back(&region[rowLen-1][1]);
            adjacent.push_back(&region[rowLen-1][0]);
        }

        else{ // on left column, not on top or bottowm
            adjacent.push_back(&region[cordA-1][0]);
            adjacent.push_back(&region[cordA-1][1]);
            adjacent.push_back(&region[cordA][1]);
            adjacent.push_back(&region[cordA+1][0]);
            adjacent.push_back(&region[cordA+1][1]);
        }
        return;
    }
    if(cordA==rowLen){
        if(cordB==colLen){ // bottom right
            adjacent.push_back(&region[cordA][cordB-1]);
            adjacent.push_back(&region[cordA-1][cordB-1]);
            adjacent.push_back(&region[cordA-1][cordB]);
        }
        
        else{ // bottom row, not either end
            adjacent.push_back(&region[cordA][cordB-1]);
            adjacent.push_back(&region[cordA-1][cordB-1]);
            adjacent.push_back(&region[cordA-1][cordB]);
            adjacent.push_back(&region[cordA-1][cordB+1]);
            adjacent.push_back(&region[cordA][cordB+1]);
        }
        return;
    }

    if(cordB==colLen){ // right side, but not top or bottom
        adjacent.push_back(&region[cordA-1][cordB]);
        adjacent.push_back(&region[cordA-1][cordB-1]);
        adjacent.push_back(&region[cordA][cordB-1]);
        adjacent.push_back(&region[cordA+1][cordB-1]);
        adjacent.push_back(&region[cordA+1][cordB]);
        return;
    }

    else{ //somewhere in middle, will have eight zones surrounding it
        adjacent.push_back(&region[cordA-1][cordB-1]);
        adjacent.push_back(&region[cordA-1][cordB]);
        adjacent.push_back(&region[cordA-1][cordB+1]);
        adjacent.push_back(&region[cordA][cordB-1]);
        adjacent.push_back(&region[cordA][cordB+1]);
        adjacent.push_back(&region[cordA+1][cordB-1]);
        adjacent.push_back(&region[cordA+1][cordB]);
        adjacent.push_back(&region[cordA+1][cordB+1]);
    }
}


void Zone::Print(){
    cout<<"Type of Zone is "<<type<<endl;
    cout<<"Population is "<<population<<endl;
    cout<<"Pollution is "<<pollution<<endl;
    cout<<"Coordinates are ("<<cordA<<","<<cordB<<")"<<endl;
}