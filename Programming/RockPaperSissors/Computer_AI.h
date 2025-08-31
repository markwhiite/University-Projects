#ifndef COMPUTER_AI_H
#define  COMPUTER_AI_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class  COMPUTER_AI {
public:

	COMPUTER_AI();
	COMPUTER_AI(double win, double loss, double draw, double rounds, int rate,string name);

	double GetWin();
	double GetLoss();
	double GetDraw();
	double GetRounds();
	int GetRate();
	string GetName();

	void SetWin(double win);
	void SetLoss(double loss);
	void SetDraw(double draw);
	void SetRounds(double rounds);
	void SetRate(int rate);
	void SetName(string name);

	int BigBadEvil();
	void Game();
	void PrintResult();
	void PrintRate();

private:
	double win;
	double loss;
	double draw;
	double rounds;
	int rate;
	string name;
};
 
#endif

