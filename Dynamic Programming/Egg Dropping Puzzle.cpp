#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int egg_drop(int egg_num, int floor_num)
{
    if (egg_num == 0)
        return INT_MAX;
    if (floor_num == 0)
        return 0;

    vector<vector<int>> board(egg_num + 1, vector<int>(floor_num + 1, INT_MAX));
    //init floor_num equals to 1 or 0
    for (int i = 1; i <= egg_num; ++i)
    {
        board[i][0] = 0;
        board[i][1] = 1;
    }
    //init egg_num equals to 1
    for (int i = 1; i <= floor_num; ++i)
        board[1][i] = i;

    for (int i = 2; i <= egg_num; ++i)
    {
        for (int j = 2; j <= floor_num; ++j)
        {
            for (int k = 1; k <= j; ++k)
            {
                int drop_num = 1 + max(board[i - 1][k - 1], board[i][j - k]);
                if (drop_num < board[i][j])
                    board[i][j] = drop_num;
            }
        }
    }
    return board[egg_num][floor_num];
}

int main()
{
    int egg_num = 2, floor_num = 36;
    int drop_num = egg_drop(egg_num, floor_num);
    cout << "Minimum number of trials in worst case" << endl
        << "with " << egg_num << " eggs and " << floor_num << " floors is " << drop_num << endl;
    cout << "And the first egg's drop trials should be : " << endl;

    int floor = 0;
    for (int i = floor_num; ; --i)
    {
        if (egg_drop(egg_num - 1, i) == drop_num - 1)
        {
            floor = floor + i + 1;
            if (floor >= floor_num)
            {
                cout << floor_num;
                break;
            }
            cout << floor << " ";
            drop_num--;
        }
    }

    return 0;
}