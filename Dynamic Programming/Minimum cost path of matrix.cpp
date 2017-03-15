/*
*               Minimum Cost Path in Matrix
*Given a cost matrix cost[][] and a position (m, n) in cost[][], 
*write a function that returns cost of minimum cost path to reach (m, n) from (0, 0). 
*Each cell of the matrix represents a cost to traverse through that cell.
*Can only traverse down, right and diagonally.
*           (0, 0)  --->  (2, 2)
*                1 - 2   3
*                      \
*                4   8   2
*                        |
*                1   5   3
*/
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//optimal substructure:
//min_cost(m, n) = cost(m, n) + min( min_cost(m - 1, n), min_cost(m - 1, n - 1), min_cost(m, n - 1))

//in this version, i calculate all path cost of every cell, and it's not necessary.
//can just calculate the sub-matrix pointed by x and y
int min_cost_path(const vector<vector<int>>& matrix, int x, int y)
{
    if (matrix.empty())
        return INT_MAX;
    int row_num = matrix.size();
    int column_num = matrix[0].size();

    vector< vector<int> > table(row_num, vector<int>(column_num, 0));
    table[0][0] = matrix[0][0];
    //initialize first row and first column
    for (int i = 1; i < column_num; ++i)
        table[0][i] = table[0][i - 1] + matrix[0][i];
    for (int i = 1; i < row_num; ++i)
        table[i][0] = table[i - 1][0] + matrix[i][0];

    for (int i = 1; i < row_num; ++i)
    {
        for (int j = 1; j < column_num; ++j)
        {
            table[i][j] = matrix[i][j] + min({ table[i - 1][j],
                                               table[i - 1][j - 1],
                                               table[i][j - 1] });
        }
    }
    return table[x][y];
}

int main()
{
    vector<vector<int>> matrix = { { 1, 2, 3 },
                                    { 4, 8, 2 },
                                    { 1, 5, 3 } };
    cout << min_cost_path(matrix, 2, 2) << endl;
}