/**
	localizer.cpp

	Purpose: implements a 2-dimensional histogram filter
	for a robot living on a colored cyclical grid by 
	correctly implementing the "initialize_beliefs", 
	"sense", and "move" functions.
*/

#include "localizer.h"
#include "helpers.cpp"
#include <stdlib.h>
#include "debugging_helpers.cpp"

using namespace std;

/**   
    Initializes a grid of beliefs to a uniform distribution. 

    @param grid - a two dimensional grid map (vector of vectors 
    	   of chars) representing the robot's world. For example:
    	   
    	   g g g
    	   g r g
    	   g g g
		   
		   would be a 3x3 world where every cell is green except 
		   for the center, which is red.

    @return - a normalized two dimensional grid of floats. For 
           a 2x2 grid, for example, this would be:

           0.25 0.25
           0.25 0.25
*/
vector< vector <float> > initialize_beliefs(vector< vector <char> > grid) {
    vector< vector<float> > newGrid;
	vector<float> row;
    int height = grid.size();
    int width = grid[0].size();
    float area = height * width;
    float belief_per_cell = 1.0/area;
  for(int i =0; i < height; i++){
    row.clear();
    for(int j =0; j< width; j++){
      row.push_back(belief_per_cell);
    }
    newGrid.push_back(row);
  }
    
	return newGrid;
}
