//build tree O(n)
//query O(logn)
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

//Sum of given range
class segment_tree {

public:
    segment_tree(const vector<int>& arr) : 
        origin_numbers(arr), size(arr.size()), tree(pow(2, 2 * (int)(ceil(log2(size)))))
    {
        construct_st(0, size - 1, 0);
    }

    int get_sum(int start, int last)
    {
        if (start < 0 || last > size - 1 || start > last)
            throw("invalid range");

        return get_sum_st(0, size - 1, start, last, 0);
    }

    void update_value(int number_index, int new_value)
    {
        if (number_index < 0 || number_index > size - 1)
            throw("invalid update value index");

        int diff = new_value - origin_numbers[number_index];
        origin_numbers[number_index] = new_value;
        update_value_st(0, size - 1, number_index, diff, 0);
    }

private:
    int construct_st(int start, int last, int index)
    {
        if (start == last)
        {
            tree[index] = origin_numbers[start];
            return origin_numbers[start];
        }

        int mid = start + (last - start) / 2;
        tree[index] = construct_st(start, mid, index * 2 + 1) +
            construct_st(mid + 1, last, index * 2 + 2);
        return tree[index];
    }

    int get_sum_st(int tree_start, int tree_last, int query_start, int query_last, int index)
    {
        //segment of this node(index) is a part of given query range
        if (query_start <= tree_start && query_last >= tree_last)
            return tree[index];

        //if outside the given query range
        if (tree_start > query_last || tree_last < query_start)
            return 0;

        //part of this segment overlaps with the given query range
        int mid = tree_start + (tree_last - tree_start) / 2;
        return get_sum_st(tree_start, mid, query_start, query_last, index * 2 + 1) +
            get_sum_st(mid + 1, tree_last, query_start, query_last, index * 2 + 2);
    }

    void update_value_st(int tree_start, int tree_last, int number_index, int diff, int index)
    {
        if (tree_start > number_index || tree_last < number_index)
            return;

        tree[index] += diff;
        if (tree_start != tree_last)
        {
            int mid = tree_start + (tree_last - tree_start) / 2;
            update_value_st(tree_start, mid, number_index, diff, index * 2 + 1);
            update_value_st(mid + 1, tree_last, number_index, diff, index * 2 + 2);
        }
    }

    vector<int> origin_numbers;
    int size;
    vector<int> tree;

};


//range minimum query
class segment_tree2 {
public:
    segment_tree2(const vector<int>& arr) :
        origin_numbers(arr), size(arr.size()), tree(pow(2, 2 * (int)ceil(log2(size))))
    {
        construct_st(0, size - 1, 0);
    }

    int rmq(int query_start, int query_end)
    {
        if (query_start < 0 || query_end > size - 1 || query_start > query_end)
            throw ("invalid query range");

        return rmq_st(0, size - 1, query_start, query_end, 0);
    }

private:
    int construct_st(int tree_start, int tree_end, int index)
    {
        if (tree_start == tree_end)
        {
            tree[index] = origin_numbers[tree_start];
            return origin_numbers[tree_start];
        }
        
        int mid = tree_start + (tree_end - tree_start) / 2;
        tree[index] = min(construct_st(tree_start, mid, index * 2 + 1),
            construct_st(mid + 1, tree_end, index * 2 + 2));
        return tree[index];
    }

    int rmq_st(int tree_start, int tree_end, int query_start, int query_end, int index)
    {
        if (tree_start > query_end || tree_end < query_start)
            return INT_MAX;

        if (tree_start >= query_start && tree_end <= query_end)
            return tree[index];

        int mid = tree_start + (tree_end - tree_start) / 2;
        return min(rmq_st(tree_start, mid, query_start, query_end, index * 2 + 1),
            rmq_st(mid + 1, query_end, query_start, query_end, index * 2 + 2));
    }

    vector<int> origin_numbers;
    int size;
    vector<int> tree;
};
int main()
{
    segment_tree st({ 1, 3, 5, 7, 9, 11 });
    cout << st.get_sum(1, 3) << endl;
    st.update_value(1, 10);
    cout << st.get_sum(1, 3) << endl;
    segment_tree2 st2({ 1, 3, 2, 7, 9, 11 });
    cout << st2.rmq(1, 5) << endl;

    return 0;
}