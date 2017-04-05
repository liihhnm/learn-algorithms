/*
    We require three arrays for implementation:

        1) Nodes visited in order of Euler tour of T
        2) Level of each node visited in Euler tour of T
        3) Index of the first occurrence of a node in Euler tour of T 
            (since any occurrence would be good, let’s track the first one)

    Algorithm:

        1) Do a Euler tour on the tree, and fill the euler, level and first occurrence arrays.
        2) Using the first occurrence array, get the indices corresponding to the two nodes 
            which will be the corners of the range in the level array that is fed to the RMQ algorithm for the minimum value.
        3) Once the algorithm return the index of the minimum level in the range, 
            we use it to determine the LCA using Euler tour array.

*/
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

struct node {
    int value;
    node* left;
    node* right;
    node(int val) : value(val), left(nullptr), right(nullptr)
    { }
};

int size_of_tree(node* root)
{
    if (root == nullptr)
        return 0;
    else
        return 1 + size_of_tree(root->left) + size_of_tree(root->right);
}

void delete_tree(node* root)
{
    if (root == nullptr)
        return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

class lca {
public:
    lca(node* root) : size(size_of_tree(root)), euler_tour_record(size * 2), euler_tour_level(size * 2), index(0)
    {
        //euler traverse the tree to record node and level info
        euler_tour(root, 0);
        //build range minimum query segment tree of euler_tour_level
        construct_st();
    }

    int find_lca(int node1, int node2)
    {
        if (first_meet.find(node1) == first_meet.end() ||
            first_meet.find(node2) == first_meet.end())
        {
            cout << "there is no given data in the tree" << endl;
            return -1;
        }
        if (first_meet[node1] > first_meet[node2])
            swap(node1, node2);

        int query_start = first_meet[node1];
        int query_end = first_meet[node2];

        int ancestor_index = rmq_st(query_start, query_end);
        return euler_tour_record[ancestor_index];
    }

private:
    void euler_tour(node* root, int level)
    {
        if (root == nullptr)
            return;

        //record the euler tour node and level.
        euler_tour_record[index] = root->value;
        euler_tour_level[index] = level;
        index++;

        //record the index of the first meet of a node.
        if (first_meet.end() == first_meet.find(root->value))
            first_meet[root->value] = index - 1;

        //traverse left and right subtree
        if (root->left != nullptr)
        {
            euler_tour(root->left, level + 1);
            euler_tour_record[index] = root->value;
            euler_tour_level[index] = level;
            index++;
        }
        if (root->right != nullptr)
        {
            euler_tour(root->right, level + 1);
            euler_tour_record[index] = root->value;
            euler_tour_level[index] = level;
            index++;
        }
    }
    
    //segment tree construct function and recursive helper function
    //notice that segment tree store the index of euler_tour_level arr compared by it's level value
    void construct_st()
    {
        segment_tree = vector<int>(2 * (int)pow(2, (int)ceil(log2(index))));
        construct_st_helper(0, index - 1, 0);
    }

    void construct_st_helper(int tree_start, int tree_end, int tree_index)
    {
        if (tree_start == tree_end)
        {
            segment_tree[tree_index] = tree_start;
            return;
        }

        int mid = tree_start + (tree_end - tree_start) / 2;
        construct_st_helper(tree_start, mid, tree_index * 2 + 1);
        construct_st_helper(mid + 1, tree_end, tree_index * 2 + 2);
        
        if (euler_tour_level[segment_tree[2 * tree_index + 1]] < euler_tour_level[segment_tree[2 * tree_index + 2]])
            segment_tree[tree_index] = segment_tree[2 * tree_index + 1];
        else
            segment_tree[tree_index] = segment_tree[2 * tree_index + 2];
    }

    //segment tree rmq function and recursive helper function
    int rmq_st(int query_start, int query_end)
    {
        if (query_start < 0 || query_end > index - 1)
            throw("invalid query range");

        return rmq_st_helper(0, index - 1, query_start, query_end, 0);
    }

    int rmq_st_helper(int tree_start, int tree_end, int query_start, int query_end, int tree_index)
    {
        if (tree_start > query_end || tree_end < query_start)
            return -1;

        if (tree_start >= query_start && tree_end <= query_end)
            return segment_tree[tree_index];

        int mid = tree_start + (tree_end - tree_start) / 2;
        int query_left = rmq_st_helper(tree_start, mid, query_start, query_end, tree_index * 2 + 1);
        int query_right = rmq_st_helper(mid + 1, tree_end, query_start, query_end, tree_index * 2 + 2);

        if (query_left == -1)
            return query_right;
        else if (query_right == -1)
            return query_left;
        return (euler_tour_level[query_left] < euler_tour_level[query_right]) ? query_left : query_right;
    }

    int size; //size of tree
    vector<int> euler_tour_record;
    vector<int> euler_tour_level;
    map<int, int> first_meet;
    vector<int> segment_tree;
    int index; //number of euler tour node
};

int main()
{
    node* root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->left->right = new node(5);
    root->right->left = new node(6);
    root->right->right = new node(7);
    root->left->right->left = new node(8);
    root->left->right->right = new node(9);
  //  cout << size_of_tree(root) << endl;
    lca l(root);
    cout << l.find_lca(4, 9) << endl;

    node* tree2 = new node(5);
    tree2->left = new node(2);
    tree2->left->left = new node(1);
    tree2->left->right = new node(3);
    tree2->left->right->right = new node(4);

    tree2->right = new node(8);
    tree2->right->left = new node(6);
    tree2->right->left->right = new node(7);
    tree2->right->right = new node(9);
    tree2->right->right->right = new node(10);
   // cout << size_of_tree(tree2) << endl;
    lca l2(tree2);
    cout << l2.find_lca(7, 9) << endl;
    cout << l2.find_lca(2, 3) << endl;
    cout << l2.find_lca(2, 10) << endl;

    return 0;
}