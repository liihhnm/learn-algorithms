//K'th smallest element
//deterministic select
//worsest O(n)
//but performance in practice is not good as randomized version
#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>

using namespace std;

int partition(vector<int>& arr, int left, int right, int median)
{
    for (int i = left; i <= right; i++)
    {
        if (arr[i] == median)
        {
            swap(arr[i], arr[left]);
            break;
        }
    }

    //select the left element as pivot
    int length = right - left + 1;
    int i = left;
    int key = arr[left];

    for (int j = 1; j < length; j++)
    {
        if (key >= arr[left + j])
        {
            i++;
            swap(arr[i], arr[left + j]);
        }
    }
    swap(arr[left], arr[i]);
    return i;
}

//return the median of small vector
int find_median(vector<int>::iterator left, int size)
{
    sort(left, left + size);
    return *(left + size / 2);
}

int kth_smallest(vector<int>& arr, int left, int right, int k)
{
    if (k <= 0 || k > right - left + 1)
        return INT_MAX;

    int size = right - left + 1;
    vector<int> median((size + 4) / 5); //floor (size + 4) / 5 subgroups
    int i;
    //get first (size / 5) subgroups' median
    for (i = 0; i < size / 5; i++)
        median[i] = find_median(arr.begin() + left + i * 5, 5);
    //if last subgroup has less than 5 elements, than get its median
    if (i * 5 < size)
    {
        median[i] = find_median(arr.begin() + left + i * 5, size % 5);
        i++;
    }

    //get med of med
    int med_of_med = (i == 1) ? 
                    median[i - 1] :
                    kth_smallest(median, 0, i - 1, i / 2);

    int q = partition(arr, left, right, med_of_med);
    int length = q - left + 1;

    if (length == k)
        return arr[q];
    else if (length > k)
        return kth_smallest(arr, left, q - 1, k);
    else
        return kth_smallest(arr, q + 1, right, k - length);

}

int main()
{
    vector<int> v{ 12, 3, 5, 7, 4, 19, 26 };
    cout << kth_smallest(v, 0, v.size() - 1, 8) << endl;
}