#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>

using namespace std; 


#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

// Forward declaration of function "breadthFirstSearch"
void breadthFirstSearch(string x);

// Forward declaration of function "isSolveable"
bool isSolveable(string x);

// Forward declaration of function "getInversions"
bool getInversions(string x);

// Forward declaration of function "generateNeighbors"
vector<string> generateNeighbors(string x);

// Forward declaration of function "gridPrinter"
void gridPrinter(string grid);

// Forward declaration of function "containsAllNumbers"
bool containsAllNumbers(string grid);
;

#endif