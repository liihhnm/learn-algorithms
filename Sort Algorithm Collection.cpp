/*
    1) select_sort
    2) bubble_sort
    3) insertion_sort
    4) merge_sort
    5) heap_sort
    6) quick_sort
    7) counting_sort
    8) radix_sort
*/

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void select_sort(vector<int>& arr)
{
    int size = arr.size();
    int min_index;

    for (int i = 0; i < size - 1; ++i)
    {
        min_index = i;
        for (int j = i + 1; j < size; ++j)
            if (arr[min_index] > arr[j])
                min_index = j;
        swap(arr[i], arr[min_index]);
    }
}

void bubble_sort(vector<int>& arr)
{
    int size = arr.size();

    for (int i = size - 1; i > 0; --i)
    {
        for (int j = 0; j < i; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
    }
}

void insertion_sort(vector<int>& arr)
{
    int size = arr.size();

    for (int i = 1; i < size; ++i)
    {
        int key = arr[i];
        int index = i - 1;
        while (index >= 0 && arr[index] > key)
        {
            arr[index + 1] = arr[index];
            index--;
        }
        arr[index + 1] = key;
    }
}

void merge(vector<int>& arr, int left, int mid, int right)
{
    int size1 = mid - left + 1;
    int size2 = right - mid;

    //copy two subarrays
    vector<int> l(size1), r(size2);
    for (int i = 0; i < size1; ++i)
        l[i] = arr[left + i];
    for (int i = 0; i < size2; ++i)
        r[i] = arr[mid + 1 + i];

    //merge two into originl arr
    int i = 0, j = 0, k = left;
    while (i < size1 && j < size2)
    {
        if (l[i] <= r[j])
            arr[k++] = l[i++];
        else
            arr[k++] = r[j++];
    }
    //add left elements in l arr or r arr
    while (i < size1)
    {
        arr[k++] = l[i++];
    }
    while (j < size2)
    {
        arr[k++] = r[j++];
    }
}

void merge_sort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;
    
    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void heapify(vector<int>& arr, int size, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int current_max = index;

    if (left < size && arr[left] > arr[current_max])
        current_max = left;
    if (right < size && arr[right] > arr[current_max])
        current_max = right;
    
    if (current_max != index)
    {
        swap(arr[index], arr[current_max]);
        heapify(arr, size, current_max);
    }
}

void heap_sort(vector<int>& arr)
{
    int size = arr.size();
    for (int i = size / 2; i >= 0; --i)
        heapify(arr, size, i);

    for (int i = size - 1; i > 0; --i)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(vector<int>& arr, int left, int right)
{
    //choose the left element as pivot
    int index = left;
    for (int i = left + 1; i <= right; ++i)
        if (arr[i] <= arr[left])
            swap(arr[++index], arr[i]);
    swap(arr[index], arr[left]);
    return index;
}

void quick_sort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;
    int mid = partition(arr, left, right);
    quick_sort(arr, left, mid - 1);
    quick_sort(arr, mid + 1, right);
}

//time O(n + k) while k is the range of numbers in arr
//space O(n + k)
//not comparison based sort
void counting_sort(vector<int>& arr)
{
    int size = arr.size();
    if (size <= 1)
        return;
    //find minimum and maximum number of arr
    int minimum = arr[0];
    int maximum = arr[0];
    for (int i = 1; i < size; ++i)
    {
        if (arr[i] < minimum)
            minimum = arr[i];
        if (arr[i] > maximum)
            maximum = arr[i];
    }
    
    int range = maximum - minimum + 1;
    vector<int> appear_count(range, 0);
    vector<int> result(size);

    //count the appearance times of number in the arr
    for (auto& num : arr)
        appear_count[num - minimum]++;
    //calculate index
    for (int i = 1; i < range; ++i)
        appear_count[i] += appear_count[i - 1];
    
    //for stability, arrange number from end to begin.
    for (int i = size - 1; i >= 0; --i)
    {
        int index = arr[i] - minimum;
        result[appear_count[index] - 1] = arr[i];
        appear_count[index]--;
    }
    //write result back to arr
    for (int i = 0; i < size; ++i)
        arr[i] = result[i];
}

//time O(d * (n + b)) while input number have d  digits, and b is the base.
void radix_sort_helper(vector<int>& arr, int exp) //count sort in one digit
{
    int size = arr.size();
    vector<int> result(size);
    vector<int> appear_count(10, 0);

    for (auto& num : arr)
        appear_count[(num / exp) % 10]++;
    for (int i = 1; i < 10; ++i)
        appear_count[i] += appear_count[i - 1];
    for (int i = size - 1; i >= 0; --i)
    {
        int index = (arr[i] / exp) % 10;
        result[appear_count[index] - 1] = arr[i];
        appear_count[index]--;
    }
    for (int i = 0; i < size; ++i)
        arr[i] = result[i];
}

void radix_sort(vector<int>& arr)
{
    int size = arr.size();
    if (size <= 1)
        return;
    //check if there exist negative number, and if so add all numbers up to non-negative number
    //I don't think this is a good way to solve the case which arr has negative number,
    //TODO a bettter solution.
    int minimum = arr[0];
    for (int i = 1; i < size; ++i)
        if (arr[i] < minimum)
            minimum = arr[i];
    if (minimum < 0)
        for (auto& num : arr)
            num += -minimum;

    //find the largest number in arr
    int maximum = arr[0];
    for (int i = 1; i < size; ++i)
        if (arr[i] > maximum)
            maximum = arr[i];

    //sort digit by digit, and keep the order of sort of last digit.
    for (int exp = 1; maximum / exp > 0; exp *= 10)
    {
        radix_sort_helper(arr, exp);
    }
    for (auto& num : arr)
        num += minimum;
}

int main()
{
    vector<int> arr = { 1, 3, 2, 8, 4, -34, 9, 5, 6, 0, 7, 21};
    //select_sort(arr);
    //bubble_sort(arr);
    //insertion_sort(arr);
    //merge_sort(arr, 0, arr.size() - 1);
    //heap_sort(arr);
    //quick_sort(arr, 0, arr.size() - 1);
    //counting_sort(arr);
    //radix_sort(arr);
    for (auto num : arr)
        cout << num << " ";
}
