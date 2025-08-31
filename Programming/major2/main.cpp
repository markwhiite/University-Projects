#include "Group_Strategy.h"
#include <iostream>

using namespace std;

int main()
{


	cout << "Lets play rock, paper, scissors! << endl;

	// Get the number of rounds to run
	int rounds;
	cout << "How many rounds would you like to run?: ";
	cin >> rounds;

	//number of times to print
	int printTimes;
	cout << "How many times would you like to see the current score: ";
	cin >> printTimes;

	//Group_Strategy object
	Group_Strategy gs;

	// Run the algorithm
	int numberOfWins = gs.run(rounds,printTimes);

	// Print results
	if (printTimes > 0)
	{
		for (int i = 0; i < printTimes; i++)
		{
			cout << "Round #" << i + 1 << ": ";
			cout << "Win: " << numberOfWins << " (" << (numberOfWins / rounds) * 100 << "%)" << endl;
			cout << "Tied: " << (rounds - numberOfWins) << " (" << ((rounds - numberOfWins) / rounds) * 100 << "%)" << endl;
			cout << "Loss: 0 (0%)" << endl;
		}
	}

	// Print final values
	cout << endl;
	cout << "WINNER'" << endl;
	//cout << "Winning Algorithm: Group_Strategy" << endl;
	//cout << "Win Percentage: " << (numberOfWins / rounds) * 100 << "%" << endl;
	//cout << "Tie Percentage: " << ((rounds - numberOfWins) / rounds) * 100 << "%" << endl;

	cout << "LOSER" << endl;
	//cout << "Losing Algorithm: BigBadEvilCode" << endl;
	//cout << "Win Percentage: 0%" << endl;
	//cout << "Tie Percentage: 0%" << endl;

	return 0;
}
