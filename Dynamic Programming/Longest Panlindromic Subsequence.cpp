//O(n ^ 2)
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int lps(const string& s)
{
    int size = s.size();
    if (size <= 1)
        return size;

    vector<vector<int>> board(size, vector<int>(size, 0));
    for (int i = 0; i < size; ++i)
    {
        board[i][i] = 1;
    }
    
    for (int len = 2; len <= size; ++len)
    {
        for (int start = 0; start < size - len + 1; ++start)
        {
            int last = start + len - 1;
            if (s[start] == s[last])
                board[start][last] = board[start + 1][last - 1] + 2;
            else
                board[start][last] = max(board[start + 1][last], board[start][last - 1]);
        }
    }
    return board[0][size - 1];
}

int main()
{
    string test = "geeksforgeeks";
    cout << lps(test) << endl;

    return 0;
}