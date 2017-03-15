//O(mn)
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

//Longest common subsequence.
//A subsequence is a sequence that appears in the same relative order, 
//but not necessarily contiguous. 
int lcs(const string& x, const string& y)
{
    int x_size = x.size();
    int y_size = y.size();
    string result;
    vector< vector<int> > table(x_size + 1, vector<int>(y_size + 1, 0));

    for (int i = 1; i <= x_size; ++i)
    {
        for (int j = 1; j <= y_size; ++j)
        {
            if (x[i] == y[j])
                table[i][j] = 1 + table[i - 1][j - 1];
            else
                table[i][j] = max(table[i - 1][j], table[i][j - 1]);
        }
    }
    return table[x_size][y_size];
}

int main()
{
    cout << lcs("AGGTAB", "GXTXAYB") << endl;
}