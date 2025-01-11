#include<bits/stdc++.h>
using namespace std;
// we can use a backtracking approach to check whenever a char is not '.' 
// to check a 3x3 block we use row = 3(row/3)+i/3 , col = 3(col/3)+i%3
class Solution {
public:
    bool isvalid(vector<vector<char>> &board, int row, int col, char c){
        for(int i=0; i<9; i++){
            if(board[row][i] == c) return false;
            if(board[i][col] == c) return false;
            if(board[3*(row/3) + i/3][3*(col/3) + i%3] == c) return false;
        }
        return true;
    }
    bool isValidSudoku(vector<vector<char>>& board) {
        for(int row=0; row<9; row++){
            for(int col=0; col<9; col++){
                if(board[row][col] != '.'){
                    char c = board[row][col];
                    board[row][col] = '.';
                    if(isvalid(board, row, col, c) == false) return false;
                    board[row][col] = c;
                }
            }
        }
        return true;
    }
};