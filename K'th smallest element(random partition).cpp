//K'th smallest element
#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include <iterator>

using namespace std;

int partition(vector<int>& arr, int left, int right)
{
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

int random_partition(vector<int>& arr, int left, int right)
{
    default_random_engine d(time(0));
    uniform_int_distribution<int> u(left, right);
    int i = u(d);
    swap(arr[left], arr[i]);
    return partition(arr, left, right);
}

void quick_sort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;
    int mid = random_partition(arr, left, right);
    quick_sort(arr, left, mid - 1);
    quick_sort(arr, mid + 1, right);
}

int random_select(vector<int>& arr, int left, int right, int k)
{
    if (left == right)
        return arr[left];
    int q = random_partition(arr, left, right);
    int i = q - left + 1;

    if (i == k)
        return arr[q];
    else if (i > k)
        return random_select(arr, left, q - 1, k);
    else
        return random_select(arr, q + 1, right, k - i);
}

int kth_smallest(vector<int>& arr, int k)
{
    return random_select(arr, 0, arr.size() - 1, k);
}

int main()
{
    vector<int> v{ 12, 3, 5, 7, 4, 19, 26 };
    cout << kth_smallest(v, 1) << endl;
    quick_sort(v, 0, v.size() - 1);
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
}