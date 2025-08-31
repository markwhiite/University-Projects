#include "Group_Strategy.h"
using namespace std;

void Group_Strategy::run(int rounds, int prints)
{
 	// Initialize variables
 	wins = 0;
	ties = 0;
	losses = 0;




	// Our group strategy can possibly be entered here




	// Print results
 	for (int i = 0; i < prints; i++)
 	{
   		cout << "Round #" << i << endl;
   		cout << "Wins: " << wins << " (" << (wins/rounds)*100 << "%)" << endl;
   		cout << "Ties: " << ties << " (" << (ties/rounds)*100 << "%)" << endl;
   		cout << "Losses: " << losses << " (" << (losses/rounds)*100 << "%)" << endl;
 	}
}
