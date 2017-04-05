#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int matrix_chain_mul(const vector<int>& matrix)
{
    int size = matrix.size();
    vector<vector<int>> board(size, vector<int>(size, INT_MAX));

    for (int i = 1; i < size; ++i)
        board[i][i] = 0;

    for (int length = 2; length < size; ++length)
    {
        for (int i = 1; i < size - length + 1; ++i)
        {
            int j = i + length - 1;
            //board[i][j] = INT_MAX;
            for (int k = i; k < j; ++k)
            {
                int q = board[i][k] + board[k + 1][j] + matrix[i - 1] * matrix[k] * matrix[j];
                if (q < board[i][j])
                    board[i][j] = q;
            }
        }
    }
    return board[1][size - 1];
}

int main()
{
    vector<int> matrix = { 1, 2, 3, 4 };
    cout << matrix_chain_mul(matrix) << endl;
}
