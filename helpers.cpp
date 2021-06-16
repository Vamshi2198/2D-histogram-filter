/**
	helpers.cpp

	Purpose: helper functions which are useful when
	implementing a 2-dimensional histogram filter.
*/

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/** Normalizes a grid of numbers. 

    @param grid - a two dimensional grid (vector of vectors of floats)
		   where each entry represents the unnormalized probability 
		   associated with that grid cell.

    @return - a new normalized two dimensional grid where the sum of 
    	   all probabilities is equal to one.
*/
vector< vector<float> > normalize(vector< vector <float> > grid) {
	
	vector< vector<float> > newGrid;

    float total = 0;
    for(int i =0; i<grid.size(); i++){
       for(int j = 0; j<grid[0].size(); j++){
        total = total + j;
      }
    }
    for(int i =0; i<grid.size(); i++){
        for(int j = 0; j<grid[0].size(); j++){
          newGrid[i][j] = grid[i][j]/(total);
      }
    }
        
  

	return newGrid;
}