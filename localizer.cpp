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

/**Implements robot motion by updating beliefs based on the 
    intended dx and dy of the robot. 

    For example, if a localized robot with the following beliefs

    0.00  0.00  0.00
    0.00  1.00  0.00
    0.00  0.00  0.00 

    and dx and dy are both 1 and blurring is 0 (noiseless motion),
    than after calling this function the returned beliefs would be

    0.00  0.00  0.00
    0.00  0.00  0.00
    0.00  0.00  1.00 

  @param dy - the intended change in y position of the robot

  @param dx - the intended change in x position of the robot

    @param beliefs - a two dimensional grid of floats representing
         the robot's beliefs for each cell before sensing. For 
         example, a robot which has almost certainly localized 
         itself in a 2D world might have the following beliefs:

         0.01 0.98
         0.00 0.01

    @param blurring - A number representing how noisy robot motion
           is. If blurring = 0.0 then motion is noiseless.

    @return - a normalized two dimensional grid of floats 
         representing the updated beliefs for the robot. 
*/
vector< vector <float> > move(int dy, int dx, 
  vector < vector <float> > beliefs,
  float blurring) 
{
  int height = beliefs.size();
  int width = beliefs[0].size();
  int new_i;
  int new_j;
  vector < vector <float> > newGrid(height, vector<float>(width,0.0));
  for(int i =1; i<height; i++){
          for(int j = 1; j<width; j++){
            new_i = (i + dy) % height;
            new_j = (j + dx) % width;
            newGrid[new_i][new_j] = beliefs[i][j] ;
          }
       } 
  

  return blur(newGrid, blurring);
}
