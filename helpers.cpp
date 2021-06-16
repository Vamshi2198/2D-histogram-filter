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
	
	vector < vector <float> > newGrid(grid.size(), vector<float>(grid[0].size()));

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

/** Blurs (and normalizes) a grid of probabilities by spreading 
    probability from each cell over a 3x3 "window" of cells. This 
    function assumes a cyclic world where probability "spills 
    over" from the right edge to the left and bottom to top. 

    EXAMPLE - After blurring (with blurring=0.12) a localized 
    distribution like this:

    0.00  0.00  0.00 
    0.00  1.00  0.00
    0.00  0.00  0.00 

    would look like this:
	
	0.01  0.02	0.01
	0.02  0.88	0.02
	0.01  0.02  0.01

    @param grid - a two dimensional grid (vector of vectors of floats)
		   where each entry represents the unnormalized probability 
		   associated with that grid cell.

	  @param blurring - a floating point number between 0.0 and 1.0 
		   which represents how much probability from one cell 
		   "spills over" to it's neighbors. If it's 0.0, then no
		   blurring occurs. 

    @return - a new normalized two dimensional grid where probability 
    	   has been blurred.
*/
vector < vector <float> > blur(vector < vector < float> > grid, float blurring) {

    int height = grid.size();
    int width = grid[0].size();
  vector < vector <float> > newGrid(height, vector<float>(width,0.0));
 
    float center_prob = 1.0 - blurring;
    float corner_prob = blurring/12.0;
    float adjacent_prob = blurring/6.0;
    
    vector < vector <float> > window{ {corner_prob, adjacent_prob, corner_prob},
                                      {adjacent_prob, center_prob, adjacent_prob},
                                      {corner_prob, adjacent_prob, corner_prob}};
    
  
  vector < vector <float> > grid_val;
  int new_i;
  int new_j;
  for(int i =0; i<height; i++){
     for(int j =0; j<width; j++){
       grid_val[i][j] = grid[i][j];
       for(int dx = -1; dx<window.size(); dx++){
          for(int dy = -1; dy<window[0].size(); dy++){
            new_i = (i + dy) % height;
            new_j = (j + dx) % width;
            newGrid[new_i][new_j] += window[dx+1][dy+1] * grid_val[i][j];
          }
       }            
     }
   }
  
   
  
    
    
	return normalize(newGrid);
}