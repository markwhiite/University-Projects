#ifndef GROUP_STRATEGY_H
#define GROUP_STRATEGY_H

#include <iostream>

class Group_Strategy
{

	public:
 	void run(int num_rounds, int num_prints);
 	void outputResults();

	private:
 	int wins, ties, losses;
};
#endif
