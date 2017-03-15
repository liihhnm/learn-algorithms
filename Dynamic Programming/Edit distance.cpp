////O(mn)
/*
*Given two strings str1 and str2 and below operations that can performed on str1. 
*Find minimum number of edits (operations) required to convert ‘str1’ into ‘str2’.
*
*1.Insert
*2.Remove
*3.Replace
All of the above operations are of equal cost.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

int edit_dist(const string& x, const string& y)
{
    int x_size = x.size();
    int y_size = y.size();
    vector< vector<int> > table(x_size + 1, vector<int>(y_size + 1, 0));

    for (int i = 0; i <= x_size; ++i)
    {
        for (int j = 0; j <= y_size; ++j)
        {
            if (i == 0)
                table[i][j] = j;
            else if (j == 0)
                table[i][j] = i;
            else if (x[i] == y[j])
                table[i][j] = table[i - 1][j - 1];
            else
                table[i][j] = 1 + min({ table[i][j - 1],       //insert 
                                        table[i - 1][j],       //remove
                                        table[i - 1][j - 1] });//replace
        }
    }

    return table[x_size][y_size];
}

int main()
{
    cout << edit_dist("sunday", "saturday") << endl;//3
}