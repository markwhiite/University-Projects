//Name: Alhassan Mohamed
//Professor: Chambers
#include <iostream>
#include <string>


using namespace std;

//Global Variables
    int rounds = 0;
    double win = 0;
    double loss = 0;
    double tie = 0;
    string groupChoice = "";
    string evilChoice = "";

//Function Prototypes
string Group_Strategy();
string BigBadEvilCode();
void printResults();
void calculateResults(string groupChoice, string evilChoice);

int main()
{
    //Variables
    int print = 0;

    //Get number of rounds
    cout << "How many rounds would you like to play? ";
    cin >> totalRounds;

    //Get number of times to print
    cout << "How many times would you like to print the results? ";
    cin >> print;

    //Loop through rounds
    for (int i = 0; i < totalRounds; i++)
    {
        rounds++;
        
        //Call Group_Strategy
        Group_Strategy();

        //Call BigBadEvilCode
        BigBadEvilCode();
        
        //Calculate results
        calculateResults(groupChoice, evilChoice);
        
        
    }

    cout << "\n\nFinal Results\n";
    printResults();
    
    //Exit program
    return 0;
}

string Group_Strategy()
{
    //Variables
    int choice = 0;

    //Get random number
    choice = rand() % 3 + 1;

    //Rock
    if (choice == 1)
    {
        cout << "Group_Strategy chose Rock" << endl;
        groupChoice = "rock";
        return groupChoice;
    }

    //Paper
    else if (choice == 2)
    {
        cout << "Group_Strategy chose Paper" << endl;
        groupChoice = "paper";
        return groupChoice;
    }

    //Scissors
    else if (choice == 3)
    {
        cout << "Group_Strategy chose Scissors" << endl;
        groupChoice = "scissors";
        return groupChoice;
    }

    else
    {
        return 0;
    }
}

string BigBadEvilCode()
{
    //Variables
    int choice = 0;

    //Get random number
    choice = rand() % 3 + 1;
    
    //Rock
    if (choice == 1)
    {
        cout << "BigBadEvilCode chose Rock" << endl;
        evilChoice = "rock";
        return evilChoice;
    }
    
    //Paper
    else if (choice == 2)
    {
        cout << "BigBadEvilCode chose Paper" << endl;
        evilChoice = "paper";
        return evilChoice;
    }

    //Scissors
    else if (choice == 3)
    {
        cout << "BigBadEvilCode chose Scissors" << endl;
        evilChoice = "scissors";
        return evilChoice;
    }

}

// function to calculate wins, losses, and ties

void calculateResults(string groupChoice, string evilChoice)
{
    //Rock
    if (groupChoice == "rock" && evilChoice == "rock")
    {
        tie++;
    }

    else if (groupChoice == "rock" && evilChoice == "paper")
    {
        loss++;
    }

    else if (groupChoice == "rock" && evilChoice == "scissors")
    {
        win++;
    }

    //Paper
    else if (groupChoice == "paper" && evilChoice == "rock")
    {
        win++;
    }

    else if (groupChoice == "paper" && evilChoice == "paper")
    {
        tie++;
    }

    else if (groupChoice == "paper" && evilChoice == "scissors")
    {
        loss++;
    }

    //Scissors
    else if (groupChoice == "scissors" && evilChoice == "rock")
    {
        loss++;
    }

    else if (groupChoice == "scissors" && evilChoice == "paper")
    {
        win++;
    }

    else if (groupChoice == "scissors" && evilChoice == "scissors")
    {
        tie++;
    }
}

// function to print results
void printResults()
{
    //Variables
    double winPercent = 0.0;
    double lossPercent = 0.0;
    double tiePercent = 0.0;

    //Calculate percentages
    winPercent = (win / rounds) * 100.0;
    lossPercent = (loss / rounds) * 100.0;
    tiePercent = (tie / rounds) * 100.0;

    //Print results
    cout << "Round: " << rounds << endl;
    cout << "Win: " << win << " (" << winPercent << "%)" << endl;
    cout << "Loss: " << loss << " (" << lossPercent << "%)" << endl;
    cout << "Tie: " << tie << " (" << tiePercent << "%)" << endl;
}

/*
Stratergy Researched:

This stratergy keeps track of the opponent's
moves by storing it in a queue. The opponent's move will be added to the
end of the queue and the oldest move will be removed from the beggining of the queue.
Then use the previous moves to determine the most common move and use that to win.
If the most common move is rock, then use paper. If the most common move is paper, then use scissors.
If the most common move is scissors, then use rock.
 
#include <iostream>
#include <queue>
#include <string>

const int N = 3; // number of previous moves to keep track of

int main() {
  // Create a queue to store the previous moves
  std::queue<std::string> prev_moves;

  // Loop indefinitely (until the game is over)
  while (true) {
    std::string opponent_move;
    std::cout << "Enter the opponent's move: ";
    std::cin >> opponent_move;

    // Add the opponent's move to the queue and remove the oldest move
    prev_moves.push(opponent_move);
    if (prev_moves.size() > N) {
      prev_moves.pop();
    }

    // Determine the most common move among the previous N moves
    std::string most_common_move = "rock"; // default to "rock"
    int rock_count = 0, paper_count = 0, scissors_count = 0;
    for (int i = 0; i < prev_moves.size(); i++) {
      if (prev_moves.front() == "rock") rock_count++;
      else if (prev_moves.front() == "paper") paper_count++;
      else if (prev_moves.front() == "scissors") scissors_count++;
      prev_moves.push(prev_moves.front());
      prev_moves.pop();
    }
    if (paper_count >= rock_count && paper_count >= scissors_count) {
      most_common_move = "paper";
    } else if (scissors_count >= rock_count && scissors_count >= paper_count) {
      most_common_move = "scissors";
    }

    // Use the most common move to determine your own move
    std::string my_move;
    if (most_common_move == "rock") {
      my_move = "paper";
    } else if (most_common_move == "paper") {
      my_move = "scissors";
    } else if (most_common_move == "scissors") {
      my_move = "rock";
    }

    std::cout << "My move: " << my_move << std::endl;
  }

  return 0;
}
*/
