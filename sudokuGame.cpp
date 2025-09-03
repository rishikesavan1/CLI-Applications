#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Sudoku{
private:
	vector<vector<int>> board;
	const int boardSize = 9;
	const int innerDimention = 3;
public:
	Sudoku(vector<vector<int>> board) : board(board) {}
	
	void solveSudoku(){
		if(solveSudoku(0,0)){
			cout << "-----Sudoku Solved------\n" << endl;
			displaySudoku();
			return;
		}
		cout << "Unable to solve..." << endl;
		
	}
	
	bool isBoardInitiallyValid(){
		for(int i = 0 ; i < boardSize;i++){
			for(int j = 0 ; j < boardSize;j++){
				if(board[i][j] != 0){
					int num = board[i][j];
					board[i][j] = 0;
					if(!isValid(i,j,num)){
						board[i][j] = num;
						return false;
					}
					board[i][j] = num;
				}
			}
		}
		return true;
	}
private:
	bool solveSudoku(int row, int col){
		if(row == boardSize){
			col++;
			if(col == board.size()) return true;
			else row = 0;
		}
		
		if(board[row][col] != 0) return solveSudoku(row+1,col);
		
		for(int num = 1; num <= boardSize;num++){
			if(isValid(row,col,num)){
				board[row][col] = num;
				if(solveSudoku(row+1,col)) return true;
				board[row][col] = 0;
			}
		}
		return false;
	}
	
	bool isValid(int row, int col, int num){
		for(int i = 0 ; i < board.size();i++){
			if(board[row][i] == num){
				return false;
			}
		}
		for(int i = 0 ; i < board[0].size();i++){
			if(board[i][col] == num){
				return false;
			}
		}
		int innerRow = (row / 3) * 3;
		int innerCol = (col / 3) * 3;
		for(int i = innerRow ; i < innerRow + 3;i++){
			for(int j = innerCol ; j < innerCol + 3;j++){
				if(board[i][j] == num){
					return false;
				}
			}
		}
		return true;
	}
	
	void displaySudoku(){
		for(int i = 0; i < boardSize;i++){
			if(i%3 == 0 && i != 0){
				cout << "-----------------------"<<endl;
			}
			for(int j = 0; j < boardSize; j++){
				if(j%3 == 0 && j != 0){
					cout << " |" ;
				}
				cout<< " " << board[i][j] ;
			}
			cout << endl;
		}
	}
};

int main(){
	vector<vector<int>> board = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };
    
    Sudoku sudoku(board);
    if(!sudoku.isBoardInitiallyValid()){
    	cout << "Invalid Sudoku";
    	return 0;
	}
	sudoku.solveSudoku();
	return 0;
}