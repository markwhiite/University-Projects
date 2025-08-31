#ifndef ALGO1_H
#define ALGO1_H
struct option{
    int rCounter, pCounter, sCounter;
};
void SetCounter(option &op);
void GatherResults(option &Rock, option &Paper, option &Scissors, int opp, int prev);
int Group_Strategy(int total, int prev, option &Rock, option &Paper, option &Scissors);
int Algo2(int prev);
void ShowResults(option &Rock, option &Paper, option &Scissors);
#endif

