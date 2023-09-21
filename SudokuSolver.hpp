//Name: Justin Chu
//Date: 5/2/2023
//This program reads a sudoku puzzle from a .csv file and provides a solution if there is one.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_

//We define Location within the Sudoku namespace.
//To use Location, you must specify the namespace Sudoku::Location
//Just like you do when using the standard namespace std::
namespace Sudoku
{ 
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:
 //Add your public members here

 /* the default constructor initializes an emtpy board, that is, a board filled with zeros (an array of 9 arrays, each filled with 9 zeros). This board will be marked unsolvable.*/
 SudokuSolver();

 /*the parameterized constructor reads the input file to initialize the board. The input files consist of 9 digits on each row separated by commas, and 9 rows separated by new line characters \n, corresponding to a sudoku board. Empty squares contain the digit 0. After reading the puzzle, the constructor tries to solve it and records whether the puzzle has a solution or not.
TIP! We strongly suggest that you break down this task with the use of helper functions (reading the file, solving the puzzle etc.) and thoroughly test and debug each functionality separately.*/
 SudokuSolver(std::string input_file);

 /*returns true if the puzzle is solvable, false otherwise. We suggest you keep track of this when solving the problem at construction, rather than solving the puzzle again each time this function is called.*/
 bool isPuzzleSolvable();

//records the puzzle as being solvable.
void setSolvable();

//returns the  2D pointer array representing the puzzle
int** getPuzzleNumbers();

// sets the  2D pointer array representing the puzzle to the value of the parameter 
void setPuzzleNumbers(int** puzzle);

/*returns a Location object with the coordinates of the first 0 found in the 2D pointer array, meaning that it is an empty square in the sudoku board. To find the first empty square you must read the 2D array from top-left (0,0) to bottom right (8,8), one row at a time. Set the row and col of the Location to the indices at which the first 0 is found in the 2D array. If there are no empty squares the Location object should have row and col values of -1.*/
Sudoku::Location returnNextEmpty();

/* returns true if the value parameter (which can take on values 1-9) can legally be placed at the given location in the 2D array without breaking the rules of sudoku. It returns false if placing value at location is not a legal move. Remember, in order to be a valid move, the value must be unique with a row, column, and sub-grid.*/
bool checkLegalValue(int value, Sudoku::Location location);

//will display the board as illustrated in the specifications
void display();

//the principle of Information Hiding would dictate that setSolvable(), getPuzzleNumbers(), setPuzzleNumbers(int** puzzle), returnNextEmpty() and checkLegalValue(int value, Sudoku::Location location) should be private. We require these to be public here for unit-testing purposes.

private:
//Add your private members here

//stores the puzzle as a 2D pointer (as represented by **) to int (int** a pointer of pointers to int) used to dynamically allocate a 2-dimensional array.
int** board;

//returns true if puzzle is solvable, false if it is not and by default
bool isSolvable;

//helper function that determines if the provided sudoku puzzle will in fact be a valid one based upon the specifications necessitated by this program
bool isValid(int** board, int row, int col, int val){
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == val) {
            return false;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == val) {
            return false;
        }
    }
    int subgridRow = (row / 3) * 3;
    int subgridCol = (col / 3) * 3;

    for (int i = subgridRow; i < subgridRow + 3; i++) {
        for (int j = subgridCol; j < subgridCol + 3; j++) {
            if (board[i][j] == val) {
                return false;
            }
        }
    }
    return true;
}

//a helper function that will solve the sudoku puzzle and will return a result, whether it is solvable or not.
bool solve(int** board, int row, int col){
    if (row == 9) {
        return true;
    }
    if (col == 9) {
        return solve(board, row + 1, 0);
    }
    if (board[row][col] != 0) {
        return solve(board, row, col + 1);
    }
    for (int val = 1; val <= 9; val++) {
        if (isValid(board, row, col, val)) {
            board[row][col] = val;
            if (solve(board, row, col + 1)) {
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}
};

#endif
