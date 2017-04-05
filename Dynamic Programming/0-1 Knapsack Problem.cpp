#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//O(nW)
int knap_back(int W, vector<int> weight, vector<int> value, int n)
{
    vector<vector<int>> board(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= W; ++j)
        {
            if (weight[i - 1] <= j)
                board[i][j] = max(value[i - 1] + board[i - 1][j - weight[i - 1]],
                    board[i - 1][j]);
            else
                board[i][j] = board[i - 1][j];
        }
    }

    return board[n][W];
}

int main()
{
    vector<int> weight = { 10, 20, 30 };
    vector<int> value = { 60, 100, 120 };
    int W = 50;
    cout << knap_back(W, weight, value, weight.size());
}
