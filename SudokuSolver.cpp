#include "SudokuSolver.hpp"

 /* the default constructor initializes an empty board, that is, a board filled with zeros (an array of 9 arrays, each filled with 9 zeros). This board will be marked unsolvable.*/
 SudokuSolver::SudokuSolver(){
    board = new int*[9];
    for (int i = 0; i < 9; i++) {
        board[i] = new int[9];
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;
        }
    }
    isSolvable=false;
 }

 /*the parameterized constructor reads the input file to initialize the board. The input files consist of 9 digits on each row separated by commas, and 9 rows separated by new line characters \n, corresponding to a sudoku board. Empty squares contain the digit 0. After reading the puzzle, the constructor tries to solve it and records whether the puzzle has a solution or not.
TIP! We strongly suggest that you break down this task with the use of helper functions (reading the file, solving the puzzle etc.) and thoroughly test and debug each functionality separately.*/
 SudokuSolver::SudokuSolver(std::string input_file){
    board = new int*[9];
    for (int i = 0; i < 9; i++) {
        board[i] = new int[9];
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;
        }
    }
    std::ifstream inputFile(input_file);

    if (!inputFile) {
        std::cout << "Unable to open file." << std::endl;
    }

    std::string line;
    std::string tempString;
    int i = 0, j = 0;
    while (getline(inputFile, line)) {
        std::stringstream ss(line);

        while (getline(ss, tempString, ',')) {
            board[i][j] = stoi(tempString);
            j++;
        }
        i++;
        j = 0;
    }
    inputFile.close();
        int** puzzle2 = new int*[9];
    for (int i = 0; i < 9; i++) {
        puzzle2[i] = new int[9];
        for (int j = 0; j < 9; j++) {
            puzzle2[i][j] = board[i][j];
        }
    }
    isSolvable = solve(board,0,0);    
 }


  /*returns true if the puzzle is solvable, false otherwise. We suggest you keep track of this when solving the problem at construction, rather than solving the puzzle again each time this function is called.*/
 bool SudokuSolver::isPuzzleSolvable(){
    return isSolvable;
 }

//records the puzzle as being solvable.
void SudokuSolver::setSolvable(){
    isSolvable=true;
}

//returns the  2D pointer array representing the puzzle
int** SudokuSolver::getPuzzleNumbers(){
    return board;
}

// sets the  2D pointer array representing the puzzle to the value of the parameter 
void SudokuSolver::setPuzzleNumbers(int** puzzle){
    board = puzzle;
}


/*returns a Location object with the coordinates of the first 0 found in the 2D pointer array, meaning that it is an empty square in the sudoku board. To find the first empty square you must read the 2D array from top-left (0,0) to bottom right (8,8), one row at a time. Set the row and col of the Location to the indices at which the first 0 is found in the 2D array. If there are no empty squares the Location object should have row and col values of -1.*/
Sudoku::Location SudokuSolver::returnNextEmpty(){
    Sudoku::Location location = {-1, -1};
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                location.row = i;
                location.col = j;
                return location;
            }
        }
    }
    return location;
}

/* returns true if the value parameter (which can take on values 1-9) can legally be placed at the given location in the 2D array without breaking the rules of sudoku. It returns false if placing value at location is not a legal move. Remember, in order to be a valid move, the value must be unique with a row, column, and sub-grid.*/
bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location){
    for (int i = 0; i < 9; i++) {
        if (board[location.row][i] == value || board[i][location.col] == value)
            return false;
    }
    int subgridRow = (location.row / 3) * 3;
    int subgridCol = (location.col / 3) * 3;
    for (int i = subgridRow; i < subgridRow + 3; i++) {
        for (int j = subgridCol; j < subgridCol + 3; j++) {
            if (board[i][j] == value) {
                return false;
            }
        }
    }
    return true;
}

//will display the board as illustrated in the specifications
void SudokuSolver::display(){
    for (int i = 0; i < 9; i++) {
        if(i % 3 == 0 && i != 0){
            std::cout <<"- - - - - - - - - - - - " <<std::endl;
        }
        for (int j = 0; j < 9; j++) {
            if(j % 3 == 0 && j != 0){
                std::cout<<" | ";
            }
            if(board[i][j]!= 0){
            if(j!=8)
            std::cout << board[i][j] << " ";
            else std::cout << board[i][j];
            }
            else{
            if(j != 8)
            std::cout << "X ";
            else std::cout << "X";
            }  
            
        }
        std::cout << std::endl;
    }
}