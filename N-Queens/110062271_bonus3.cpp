#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

// Time complexity is O(n!), where n is the size of the checkboard (n x n)

class Solution {
public:
    int result = 0;
    int totalNQueens(int n) {
        vector<vector<int>> board(n, vector<int>(n, 0));
        NQueenUtil(board, n, 0);
        return result; 
    }
    
    void NQueenUtil(vector<vector<int>> &board, int n, int col){
        if(col == n) result++;
        else{
            for(int row = 0; row < n; row++){
                if(is_safe(board, n, row, col)){
                    board[row][col] = 1;
                    NQueenUtil(board, n, col+1);
                    board[row][col] = 0; // backtrack
                }
            }
        }
    }
    
    bool is_safe(vector<vector<int>> &board, int n, int row, int col){
        for(int i=row, j=col; i>=0 && j>=0; j--){
            if(board[i][j]) return false;
            // check left half
        }
        for(int i=row, j=col; i>=0 && j>=0; i--, j--){
            if(board[i][j]) return false;
            // check upper diagonal
        }
        for(int i=row, j=col; i<n && j>=0; i++, j--){
            if(board[i][j]) return false;
            // check lower diagonal
        }
        
        return true;
    }
};

int main(void){
    Solution s;

    // cout << s.totalNQueens(8) << endl;

    for(int i=1; i<15; i++){
        cout << "n = " << i << ", number of solutions = " << s.totalNQueens(i) << endl;
    }

    return 0;
}