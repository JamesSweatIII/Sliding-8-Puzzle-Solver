# Sliding-8-Puzzle-Solver

This program solves a 3x3 sliding puzzle using breadth-first search algorithm. It takes an input file containing the starting state of the puzzle and outputs the shortest path to the goal state.

## Prerequisites

- C++ compiler

## Installation

1. Clone this repository.

``` bash
git clone https://github.com/JamesSweatIII/Sliding-8-Puzzle-Solver.git
```

2. Navigate to the project directory.

``` bash
cd Sliding-8-Puzzle-Solver
```
3. Compile the program with Makefile.
``` bash
Make
```
## Usage

```
./a.out input_file
```
`input_file` is a text file containing the starting state of the puzzle. The `input_file` should contain a single line 
with 9 digits representing the tiles of the puzzle, with 0 representing the empty space.

Example:
``` bash
./a.out puzzles/puzzle1.txt
```
`puzzle1.txt` contains:

``` 
013425786
```

## Output

The program outputs the shortest path to the goal state and the number of steps. 

``` 
Solving puzzle ...
The number of steps to the solution: 4
The path to the solution is: 
0 1 2 
3 4 5 
6 7 8 
->
0 1 2 
3 4 5 
6 7 8 
->
0 1 2 
3 4 5 
6 7 8 
->
0 1 2 
3 4 5 
6 7 8 
->
0 1 2 
3 4 5 
6 7 8 
->
Solved
```
If the puzzle is not solvable, the program outputs unsolvable.
``` 
Solving puzzle ...
Unsolvable
```