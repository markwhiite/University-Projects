#include <iostream>
#include<cstdlib>
#include "Computer_AI.h"

using namespace std;

int main()
{
    COMPUTER_AI Ct;
   

    cout << "Welcome to Rock Paper Scissors Game!!!" << endl;

    string Pname;
    cout << "Enter your Name: ";
    cin >> Pname;
    Ct.SetName(Pname);
  //  system("cls");

    int rounds, rate;
    cout << Pname << " How many rounds do you want to play?: ";
    cin >> rounds;
    Ct.SetRounds(rounds);

    cout << "What would you like the refresh rate to be?: ";
    cin >> rate;
    Ct.SetRate(rate);

    //int P_score = 0, C_score = 0; //The player and the computer score.

    srand((unsigned)time(NULL));
    Ct.Game();

    return 0;
}

