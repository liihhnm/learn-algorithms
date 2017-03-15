//O(n ^ 2)
#include <vector>
#include <iostream>

using namespace std;

int lis(const vector<int>& arr)
{
    if (arr.empty())
        return 0;
    int max = 1;

    vector<int> pre_lis(arr.size(), 1);
    for (int i = 1; i < arr.size(); ++i)
        for (int j = 0; j < i; ++j)
            if (arr[i] > arr[j] && pre_lis[i] < pre_lis[j] + 1)
                pre_lis[i] = pre_lis[j] + 1;

    for (int i = 0; i < arr.size(); ++i)
        if (max < pre_lis[i])
            max = pre_lis[i];

    return max;
}

int main()
{
    cout << lis(vector<int>({ 10, 22, 9, 33, 21, 50, 41, 60 })) << endl;
}