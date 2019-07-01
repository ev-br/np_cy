#ifndef __EVOLVE_FIELD__
#define __EVOLVE_FIELD__

#include<vector>

void update(std::vector<int>& field, double b);
void evolveT(std::vector<int>& field, double b, int num_steps);
void evolveQ(std::vector<int>& field, double b, int num_steps);

#endif
