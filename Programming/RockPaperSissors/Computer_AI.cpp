#include <iostream>
#include <string>
#include<cstdlib>
#include <vector>
#include <ctime>
using namespace std;
#include "Computer_AI.h"
#include "Algo1.h"

COMPUTER_AI::COMPUTER_AI() {
	win = 0;
	loss = 0;
	draw = 0;
	rounds = 0;
	rate = 0;
    name = "";
}

COMPUTER_AI::COMPUTER_AI(double win, double loss, double draw, double rounds, int rate,string name) {
	this->win = win;
	this->loss = loss;
	this->draw = draw;
	this->rounds = rounds;
	this->rate = rate;
    this->name = name;
}

double COMPUTER_AI::GetWin() {
	return win;
}

double COMPUTER_AI::GetLoss() {
	return loss;
}

double COMPUTER_AI::GetDraw() {
	return draw;
}

double COMPUTER_AI::GetRounds() {
	return rounds;
}
int COMPUTER_AI::GetRate() {
	return rate;
}

string COMPUTER_AI::GetName() {
    return name;
}

void COMPUTER_AI::SetWin(double win) {
	this->win = win;
}
void COMPUTER_AI::SetLoss(double loss) {
	this->loss = loss;
}
void COMPUTER_AI::SetDraw(double draw) {
	this->draw = draw;
}
void COMPUTER_AI::SetRounds(double rounds) {
	this->rounds = rounds;
}
void COMPUTER_AI::SetRate(int rate) {
	this->rate = rate;
}
void COMPUTER_AI::SetName(string name) {
    this->name = name;
}

int COMPUTER_AI::BigBadEvil() {
	int num;
    
       
    num = (rand() % 10) + 1;

    if (num == 9 || num == 10) {
            num = (rand() % 3) + 1;
            return num;
    }

    else if (num == 6 || num == 8) {
        num = (rand() % 2) + 1;
        return num;
    }

    else if (num == 4 || num == 7) {
        num = (rand() % 3) + 2;
        if (num == 4) {
            num = (rand() % 3) + 1;
            return num;
        }
        else {
            return num;
        }
    }
    else if (num == 2 || num == 5) {
        num = (rand() % 100) + 1;
        if (num <= 50) {
            num = 1;
            return num;
        }
        else if(num <= 75) {
            num = 2;
            return num;
        }
        else {
            num = (rand() % 3) + 1;
            return num;
        }
    }
    else if(num == 1 || num == 3) {
        num = (rand() % 1);
        if (num == 0) {
            num = (rand() % 7) + 1;
            if (num == 7) {
                num = 1;
                return num;
            }
            else {
                num = (rand() % 2) + 1;
                return num;
            }
        }
        else {
            do {
                num = (rand() % 4) + 1;
                return num;
            } while (num == 4);
 
        }
    }
    return 0;
  
}

void COMPUTER_AI::Game() {
    double P_wins = 0, C_wins = 0;
    double P_loss = 0, C_loss = 0;
    double P_draw = 0, C_draw = 0;
    option Rock, Paper, Scissors; //These are structs that hold the history of these choices
    SetCounter(Rock);
    SetCounter(Paper); //Setting each counter to 0
    SetCounter(Scissors);

    
    vector<int>list;
    vector<int>list_1;

    int prev =rand()%3+1; //previous choices of each player
    int prevC = rand()%3+1;
    int P_choose;
    for (int i = 1; i <= GetRounds(); i++)
    {

        //system("cls");

        int C_choose; //The player and computer choice.

        //How the Player will choose.
        P_choose = Group_Strategy(i, prev,Rock,Paper,Scissors);
        list.push_back(P_choose);

        /*"1 - Rock " << endl;
          "2 - Papar " << endl;
          "3 - Scissors " << endl;*/


          //How the Computer will choose. 
         // srand(time(0));
        C_choose = BigBadEvil();
        list_1.push_back(C_choose);

        if (P_choose == C_choose) {

            //cout << "It is a draw " << endl;
            P_draw++;
            C_draw++;
            SetDraw(C_draw);
        }
        else if (P_choose == 1 && C_choose == 2) {

            //cout << "Computer wins!!! Paper covers Rocks " << endl;
            C_wins++;
            P_loss++;
            SetWin(C_wins);
        }
        else if (P_choose == 2 && C_choose == 3) {

            //cout << "Computer wins!!! Scissors cut Paper " << endl;
            C_wins++;
            P_loss++;
            SetWin(C_wins);
        }
        else if (P_choose == 3 && C_choose == 1) {

            //cout << "Computer wins!!! Rock breaks Scissors " << endl;
            C_wins++;
            P_loss++;
            SetWin(C_wins);
        }
        else if (P_choose == 1 && C_choose == 3) {

           // cout << Pname << " wins!!! Rock breaks Scissors " << endl;
            P_wins++;
            C_loss++;
            SetLoss(C_loss);
        }
        else if (P_choose == 2 && C_choose == 1) {

            //cout << Pname << " wins!!! Paper covers Rocks " << endl;
            P_wins++;
            C_loss++;
            SetLoss(C_loss);
        }
        else {

            //cout << Pname << " wins!!! Scissors cut Paper " << endl;
            P_wins++;
            C_loss++;
            SetLoss(C_loss);
        }

        // Ct.SetRounds(i);
        if (i % GetRate() == 0) {
            cout << "Round # " << i << endl;
            PrintResult();
          //  ShowResults(Rock, Paper, Scissors);
        }

        GatherResults(Rock, Paper, Scissors, C_choose, prev);
       // cout<<"TEST "<<C_choose<<" "<< prev;
        prev = C_choose;

    }

    int totalP_wins, totalC_wins;


    cout << endl;
    

    //Print out all output and analysis here
    if (P_wins == C_wins) {
        cout << " ..::Game ended in a draw!::.." << endl << endl;;
        cout << "Algorithm: " << GetName() << endl;
        cout << "Win Percentage: " << (P_wins / GetRounds())* 100 << "%" <<" out of "<< GetRounds() <<" Rounds." << endl;// (percentage of wins)
        cout << "Tie Percentage: " << (P_draw / GetRounds())* 100 << "%" << " out of " << GetRounds() << " Rounds." << endl<<endl;// (percentage of ties)

        cout << "Algorithm: " << "Computer" << endl;
        cout << "Win Percentage: " << (C_wins/ GetRounds()) * 100 << "%" << " out of " << GetRounds() << " Rounds." << endl;// (percentage of wins)
        cout << "Tie Percentage: " << (C_draw/ GetRounds()) * 100 << "%" << " out of " << GetRounds() << " Rounds." << endl << endl;// (percentage of ties)
    }
    else if (P_wins > C_wins) {
        cout << GetName() << " won the Game!!! :>" << endl << endl;

        cout << "Winning Algorithm: " << GetName() << endl;
        cout << "Win Percentage: " << (P_wins / GetRounds()) * 100 << "%" << " out of " << GetRounds() << " Rounds." << endl;// (percentage of wins)
        cout << "Tie Percentage: " << (P_draw / GetRounds()) * 100 << "%" << " out of " << GetRounds() << " Rounds." << endl << endl;// (percentage of ties)

        cout << "Losing Algorithm: " << "Computer" << endl;
        cout << "Win Percentage: " << (C_wins / GetRounds()) * 100 << "%" << " out of " << GetRounds() << " Rounds." << endl;// (percentage of wins)
        cout << "Tie Percentage: " << (C_draw / GetRounds()) * 100 << "%" << " out of " << GetRounds() << " Rounds." << endl << endl;// (percentage of ties)
    }
    else {
        cout << "Computer won the Game!!!" << endl << endl;

        cout << "Winning Algorithm: " << "Computer" << endl;
        cout << "Win Percentage: " << (C_wins / GetRounds()) * 100 << "%" << " out of " << GetRounds() << " Rounds." << endl;// (percentage of wins)
        cout << "Tie Percentage: " << (C_draw / GetRounds()) * 100 << "%" << " out of " << GetRounds() << " Rounds." << endl << endl;// (percentage of ties)

        cout << "Losing Algorithm: " << GetName() << endl;
        cout << "Win Percentage: " << (P_wins / GetRounds()) * 100 << "%" << " out of " << GetRounds() << " Rounds." << endl;// (percentage of wins)
        cout << "Tie Percentage: " << (P_draw / GetRounds()) * 100 << "%" << " out of " << GetRounds() << " Rounds." << endl << endl;// (percentage of ties)
    }

    for (int i = 0; i < list.size(); i++) {
        cout << list.at(i) << " ";
    }
    cout << endl;

    for (int i = 0; i < list_1.size(); i++) {
        cout << list_1.at(i) << " ";
    }
}


// Function prints every refresh rate
void COMPUTER_AI::PrintRate() {

	for (int i = 0;i < rate; i++) {
		//if (i % GetRate() == 0) {
		cout << "Round # " << (i +1) << endl;
        PrintResult();
		
	}
}


//Final Result
void COMPUTER_AI::PrintResult() {

    cout << "Win: " << GetWin() << " and " <<(GetWin()/ GetRounds()) * 100<<"%" << endl;  //(countand%)
    cout << "Tied: " << GetDraw()<<" and " << (GetDraw() / GetRounds()) * 100 << "%" << endl;// (countand%)
    cout << "Loss: " << GetLoss() << " and " << (GetLoss() / GetRounds()) * 100 << "%" << endl;// (countand%)
    cout << endl;
}
