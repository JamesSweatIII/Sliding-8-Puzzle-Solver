
// imports
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include "puzzleSolver.h" // includes the header file that declares the functions used in this file

using namespace std; 

// The solved puzzle state
string solvedPuzzle = "123456780"; 

/**
* The main function that takes input from the user, solves the puzzle and prints the solution or an error message.
* Prompts the user to enter a puzzle and combines the rows of the puzzle into a single string, removes any spaces from it.
* Checks if the puzzle is solvable using isSolveable function and if it is, solves the puzzle using breadthFirstSearch function.
* If the puzzle is not solvable, prints an error message.
* @param argc The number of command-line arguments passed to the program.
* @param argv An array of pointers to the command-line arguments passed to the program.
* @return 0 if the program executes successfully.
*/

int main(int argc, char *argv[]) {
    // Read in a file specified in the command line argument and store the contents in the 'grid' variable
    // Open the file with the name specified in the first command line argument
    string grid;
    ifstream file(argv[1]); 
    
    // If the file is successfully opened
    if (file.is_open()) { 

        // Read the entire line from the file and store it in the 'grid' variable
        getline(file, grid); 

    } else { 
    
    // If the file could not be opened
        throw runtime_error("Unable to open file."); // Terminate the program
    }

    if (grid.length() != 9){
 
         throw invalid_argument("The puzzle entered is not valid length (9)"); // Terminate the program

    }

    if(!containsAllNumbers(grid)){
    
        throw invalid_argument("The puzzle entered is not all numbers"); // Terminate the program
    }   


    cout << "Solving puzzle ..." << endl; // prints a message indicating that the puzzle is being solved

    if (isSolveable(grid)){ // checks if the puzzle is solvable

        breadthFirstSearch(grid); // solves the puzzle using breadth-first search
        cout << "Solved" << endl;
        file.close();

    } else {

        cout << "Impossible" << endl; // prints a message indicating that the puzzle is not solvable
        file.close();
    }
    return 0;

}

/**
 * Checks if a string contains only numeric characters.
 * @param grid The string to check.
 * @return True if the string contains only numeric characters, false otherwise.
 */
bool containsAllNumbers(string grid) {
    // Loop through each character in the string
     for(int i = 0; i < grid.length(); i++){
        // If the character is not a digit, return false
        if (!isdigit(grid[i])) {
            return false;
        }
    }
    // If all characters are digits, return true
    return true;
}

/**
* @param grid The input string to be printed as a grid.
* @return None. The function prints a 3x3 grid representation of the input string, where each character in the string represents a tile in the puzzle.
* After printing the entire grid, an arrow pointing to the next grid is printed on a new line.
*/
void gridPrinter(string grid){
    int count = 0; 
    // initialize a count variable to keep track of how many characters have been printed
    for (int i = 0; i < grid.length(); i++){
        // iterate through each character in the input grid
        cout << i << " ";
        // output the current character followed by a space
        count++;
        // increment the count
        if (count % 3 == 0) {
            // if the count is a multiple of 3 (i.e. we have printed a complete row), 
            // start a new line
            cout << endl;
        }
    }
    // after printing the entire grid, print an arrow pointing to the next grid
    cout << "->" << endl;
}


/**
 * Performs a breadth-first search on a given sliding puzzle to find the shortest path to the goal state.
 * 
 * @param puzzle A string representing the starting state of the puzzle.
 *               The string should consist of a 3x3 grid of numbers from 0-8 representing the tiles of the puzzle,
 *               with 0 representing the empty space.
 * 
 * @return None. The function prints out the number of steps to the solution and the path from the start to the goal state.
 * 
 * The function uses two queues, one for the current level of nodes to be processed and one for the next level of nodes to be processed.
 * An unordered map is used to store the distance from the start node to each node, and another unordered map is used to store the parent of each node in the search tree.
 * The function starts by adding the start node to the queue and setting its distance to 0.
 * The goal state of the puzzle is defined in a separate string.
 * While there are still nodes in the queue to be processed, the function gets the next node to be processed from the front of the queue.
 * If the current node is the goal state, the function prints the distance to the goal and the path from the start to the goal.
 * The path is obtained by using a stack to store the path from the start to the goal, and then printing out the path from the start to the goal.
 * The function then ends the search.
 */
void breadthFirstSearch(string puzzle){

    // Create a queue for the current level of nodes to be processed
    queue<string> currentlevel;
    
    // Create an unordered map to store the distance from the start node to each node
    unordered_map<string, int> distancemap;
    
    // Create an unordered map to store the parent of each node in the search tree
    unordered_map<string, string> parentmap;

    // Add the start node to the queue and set its distance to 0
    currentlevel.push(puzzle);
    distancemap[puzzle] = 0;
    
    // Create a string to store the goal state of the puzzle
    string goalstate;
   
    // While there are still nodes in the queue to be processed
    while (!currentlevel.empty()){

        // Get the next node to be processed from the front of the queue
        goalstate = currentlevel.front();
        currentlevel.pop();

        // If the current node is the goal state, print the distance to the goal and the path from the start to the goal
        if (goalstate == solvedPuzzle){

            cout << "The number of steps to the solution: " << distancemap[goalstate] << endl;
            cout << "The path to the solution is: " << endl;
            
            // Use a stack to store the path from the start to the goal
            stack<string> path;
            while (goalstate != puzzle) {
                path.push(goalstate);
                goalstate = parentmap[goalstate];
            }
            path.push(puzzle);
            
            // Print out the path from the start to the goal
            while (!path.empty()) {

                gridPrinter(path.top());
                path.pop();
            }
            
            // End the search
            break;
        }

        // Generate the neighbors of the current node
        vector<string> neighbors = generateNeighbors(goalstate);
        
        // For each neighbor of the current node
        for (int i = 0; i < neighbors.size(); i++){

            // If the neighbor has not been visited before
            if(distancemap.count(neighbors[i]) == 0){
                	
                // Set the distance to the neighbor to be one more than the distance to the current node
                distancemap[neighbors[i]] = distancemap[goalstate] + 1;
                
                // Set the parent of the neighbor to be the current node
                parentmap[neighbors[i]] = goalstate;
                
                // Add the neighbor to the queue to be processed in the next level
                currentlevel.push(neighbors[i]);
                
            }
	    
        }

    }
   
}

/**
 * Determines if a given puzzle is solvable by checking if the number of inversions is even.
 * @param puzzle The puzzle to check, represented as a string.
 * @return True if the puzzle is solvable, false otherwise.
 */
bool isSolveable(string puzzle){

    // Check if the number of inversions in the puzzle is even
    // Returns true if even, else false
    return getInversions(puzzle);
}

/**
 * Determines if a given puzzle is solvable by counting the number of inversions.
 * An inversion is defined as any pair of tiles (a, b) where a appears before b, but a > b.
 * A solvable puzzle has an even number of inversions.
 * @param puzzle The puzzle to check, represented as a string.
 * @return True if the puzzle is solvable, false otherwise.
 */
bool getInversions(string puzzle){

    // Initialize a total inversions variable to keep track of how many inversions have been collected
     int totalinversions = 0; 
    
    // Loop through all pairs of numbers in the puzzle
    for(int i = 0; i < puzzle.length(); i++){
        for(int j = i+1; j < puzzle.length(); j++){

            // If a larger number appears before a smaller number, increment the total inversions
            if (puzzle[j] != '0' && puzzle[i] != '0' && puzzle[j] > puzzle[i]){
                totalinversions++;
            }
        }   
    }

    // Check if the puzzle is solvable

    int blank_row = 0; // Initialize a variable to keep track of the row number of the blank space (set to 0 by default)

    // Iterate through the puzzle and find the row number of the blank space
    for (int i = 0; i < 9; i++) {
        // If the current tile is the blank space
        if (puzzle[i] == '0') { 
            // Calculate the row number of the blank space (adding 1 to the quotient of i/3)
            blank_row = i / 3 + 1; 
            break; // Exit the loop since we have found the blank space
        }
    }

    // Check if the row number of the blank space is even or odd and return true or false based on the total number of inversions
    // If the blank space is in an even row
    if (blank_row % 2 == 0) { 
        // Return true if the total number of inversions is odd, false if it's even
        return totalinversions % 2 == 1; 
        
    } else { 

        // If the blank space is in an odd row
        // Return true if the total number of inversions is even, false if it's odd
        return totalinversions % 2 == 0; 
    }
}

/**
 * Generates all possible neighbor configurations of a given puzzle configuration.
 * @param closetSolution The puzzle configuration for which to generate neighbors, represented as a string.
 * @return A vector of strings representing all possible neighbor configurations.
 */
vector<string> generateNeighbors(string closetSolution){

    vector<string> neighbours; // vector to store all the neighbor configurations
    int emptySpace; // variable to store the index of the empty space
     
    for (int i = 0; i < solvedPuzzle.size(); i++){

        if (closetSolution[i] == '0'){ // find the index of the empty space

            emptySpace = i;
        }
    }

    // Check if the empty space can be moved upwards
    if (emptySpace > 2){

        string solution = closetSolution;
        solution[emptySpace] = solution[emptySpace - 3]; // swap empty space with the tile above it
        solution[emptySpace - 3] = '0';
        neighbours.push_back(solution); // add the new configuration to the vector of neighbors

    }

    // Check if the empty space can be moved downwards
    if (emptySpace < 6){
        
        string solution = closetSolution;
        solution[emptySpace] = solution[emptySpace + 3]; // swap empty space with the tile below it
        solution[emptySpace + 3] = '0';
        neighbours.push_back(solution); // add the new configuration to the vector of neighbors

    }

    // Check if the empty space can be moved to the left
    if (emptySpace != 0 && emptySpace != 3 && emptySpace != 6){
        
        string solution = closetSolution;
        solution[emptySpace] = solution[emptySpace - 1]; // swap empty space with the tile to its left
        solution[emptySpace - 1] = '0';
        neighbours.push_back(solution); // add the new configuration to the vector of neighbors
    }

    // Check if the empty space can be moved to the right
    if (emptySpace != 2 && emptySpace != 5 && emptySpace != 8){
        
        string solution = closetSolution;
        solution[emptySpace] = solution[emptySpace + 1]; // swap empty space with the tile to its right
        solution[emptySpace + 1] = '0';
        neighbours.push_back(solution); // add the new configuration to the vector of neighbors
    }

    return neighbours; // return the vector of all possible neighbor configurations
}
