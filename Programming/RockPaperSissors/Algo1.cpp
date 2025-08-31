#include <iostream>
#include "Algo1.h"
#include <cmath>
#include <ctime>
using namespace std;

//Funtion sets the initial counters to 0 at beginning of game
void SetCounter(option &op){
    op.pCounter=0;
    op.rCounter=0;
    op.sCounter=0;
}


/*
This function updates the history of the battles
based on previous choice we update Rock, Paper, or Scissors
*/
void GatherResults(option &Rock, option &Paper, option &Scissors, int opp, int prev){
    if(prev==1){
        switch(opp){
            case 1: Rock.rCounter++; break;
            case 2: Rock.pCounter++; break;
            case 3: Rock.sCounter++; break;
            default: break;
        }
    }

    else if(prev ==2){
        switch(opp){
            case 1: Paper.rCounter++; break;
            case 2: Paper.pCounter++; break;
            case 3: Paper.sCounter++; break;
            default: break;
        }
    }


    else{
        switch(opp){
            case 1: Scissors.rCounter++; break;
            case 2: Scissors.pCounter++; break;
            case 3: Scissors.sCounter++; break;
            default: break;
        }
    }
}


//Group strategy algorithm, uses markov chains
int Group_Strategy(int total, int prev, option &Rock, option &Paper, option &Scissors){

    switch(prev){
        //previous was rock
        case 1:{
            int r = Rock.rCounter;
            int p = Rock.pCounter;
            int s = Rock.sCounter;
            if(r>s)
            {
                if(r>p)
                    return 2; //rock has highest probabilty to be played, choose paper
                else{
                    return 3; //paper has high prob, choose scissors
                   
                }

            }
            else{
                if(s>p)
                    return 1; //scissors has highest prob, choose rock
                else{
                    return 3;//paper has high prob, choose scissors
                    
                }
            }
        } break;

        //previous was paper
        case 2:{
            
            int r = Paper.rCounter;
            int p = Paper.pCounter;
            int s = Paper.sCounter;

            if(r>s)
            {
                if(r>p)
                    return 2; //rock has highest probabilty to be played, choose paper
                else
                    return 3; //paper has high prob, choose scissors

            }
            else{
                if(s>p)
                    return 1; //scissors has highest prob, choose rock
                else
                    return 3;//paper has high prob, choose scissors
            }
        } break;

        //previous was scissors
        case 3:{
            
            int r = Scissors.rCounter;
            int p = Scissors.pCounter;
            int s = Scissors.sCounter;

            if(r>s)
            {
                if(r>p)
                    return 2; //rock has highest probabilty to be played, choose paper
                else
                    return 3; //paper has high prob, choose scissors

            }
            else{
                if(s>p)
                    return 1; //scissors has highest prob, choose rock
                else
                    return 3;//paper has high prob, choose scissors
            }
        } break;
        default: break;
    }

    return 1;
}


//Algorithm 2, cycles through rock, paper and scissors
int Algo2(int prev){
   // return 3;
    if(prev==1)
        return 2;
    else if(prev==2)
        return 3;
    else
        return 1;

}




// I created this function to assist me when I was editing my algorithm
void ShowResults(option &Rock, option &Paper, option &Scissors){
    cout<<"Previous is rock\n";
    int r = Rock.rCounter;
    int p = Rock.pCounter;
    int s = Rock.sCounter;
    cout<<"Rock: "<<r<<" Paper: "<<p<<" Scissors: "<<s<<endl;

    cout<<"Previous is paper\n";
    r = Paper.rCounter;
    p = Paper.pCounter;
    s = Paper.sCounter;
    cout<<"Rock: "<<r<<" Paper: "<<p<<" Scissors: "<<s<<endl;


    cout<<"Previous is scissors\n";
    r = Scissors.rCounter;
    p = Scissors.pCounter;
    s = Scissors.sCounter;
    cout<<"Rock: "<<r<<" Paper: "<<p<<" Scissors: "<<s<<endl;
}
