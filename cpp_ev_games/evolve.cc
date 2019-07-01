#include "evolve.h"
#include <cmath>
#include <iostream>

void evolveT(std::vector<int>& field, double b, int num_steps)
{
    int size = static_cast<int>(sqrt(field.size()));

	std::vector<double> scores(size*size, 0);
	std::vector<int> currentField(size*size, 0);

	for(int step = 0; step < num_steps; step++) 
	{	
		//Field
		std::copy(field.begin(), field.end(), currentField.begin());
		
		//Scores
		scores.assign(size*size, 0);

		for (int k = 0; k < size*size; k++) {
			int y = k / size; // Row
			int x = k % size; // Col

			for (int i = -1; i <= 1; i++) //Row
			{
				for (int j = -1; j <= 1; j++) //Col
				{
					if ((i == -1 && j == -1) || (i == 1 && j == 1))
						continue;

					int memberIndex = (x + i + size) % size + size * ((y + j + size) % size);

					scores[k] += field[memberIndex] == 0 ? 1 : 0;
				}
			}

			if (field[k] == 1)
			{
				scores[k] = scores[k] * b;
			}
		}		

		//Strategy
		for (int k = 0; k < size*size; k++) {
			int y = k / size; // Row
			int x = k % size; // Col

			int bestStrategyIndex = k;

			for (int i = -1; i <= 1; i++) //Row
			{
				for (int j = -1; j <= 1; j++) //Col
				{
					if ((i == -1 && j == -1) || (i == 1 && j == 1))
						continue;
											
					int memberIndex = (x + i + size) % size + size * ((y + j + size) % size);

					if (scores[bestStrategyIndex] < scores[memberIndex]) 
					{
						bestStrategyIndex = memberIndex;
					}
				}
			}

			field[k] = currentField[bestStrategyIndex];
		}
	}

	scores.clear();
	currentField.clear();
}


void evolveQ(std::vector<int>& field, double b, int num_steps)
{
    int size = static_cast<int>(sqrt(field.size()));

	std::vector<double> scores(size*size, 0);
	std::vector<int> currentField(size*size, 0);

	for(int step = 0; step < num_steps; step++) 
	{	
		//Field
		std::copy(field.begin(), field.end(), currentField.begin());
		
		//Scores
		scores.assign(size*size, 0);

		for (int k = 0; k < size*size; k++) {
			int y = k / size; // Row
			int x = k % size; // Col

			for (int i = -1; i <= 1; i++) //Row
			{
				for (int j = -1; j <= 1; j++) //Col
				{
					int memberIndex = (x + i + size) % size + size * ((y + j + size) % size);

					scores[k] += field[memberIndex] == 0 ? 1 : 0;
				}
			}

			if (field[k] == 1)
			{
				scores[k] = scores[k] * b;
			}
		}		

		//Strategy
		for (int k = 0; k < size*size; k++) {
			int y = k / size; // Row
			int x = k % size; // Col

			int bestStrategyIndex = k;

			for (int i = -1; i <= 1; i++) //Row
			{
				for (int j = -1; j <= 1; j++) //Col
				{		
					int memberIndex = (x + i + size) % size + size * ((y + j + size) % size);

					if (scores[bestStrategyIndex] < scores[memberIndex]) 
					{
						bestStrategyIndex = memberIndex;
					}
				}
			}

			field[k] = currentField[bestStrategyIndex];
		}
	}

	scores.clear();
	currentField.clear();
}