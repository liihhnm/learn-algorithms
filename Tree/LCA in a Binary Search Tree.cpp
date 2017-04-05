//lca in binary search tree
/*
    We can solve this problem using BST properties. 
    We can recursively traverse the BST from root. 
    The main idea of the solution is, while traversing from top to bottom, 
    the first node n we encounter with value between n1 and n2, 
    i.e., n1 < n < n2 or same as one of the n1 or n2, is LCA of n1 and n2 (assuming that n1 < n2). 
    So just recursively traverse the BST in, 
    if node’s value is greater than both n1 and n2 then our LCA lies in left side of the node, 
    if it’s is smaller than both n1 and n2, then LCA lies on right side. 
    Otherwise root is LCA (assuming that both n1 and n2 are present in BST)
*/
#include <iostream>

using namespace std;

struct node {
    int value;
    node* left;
    node* right;
    node(int val) : value(val), left(nullptr), right(nullptr)
    { }
};

bool value_in_tree(node* root, int node)
{
    if (root == nullptr)
        return false;

    if (root->value < node)
        return value_in_tree(root->right, node);
    else if (root->value == node)
        return true;
    else
        return value_in_tree(root->left, node);
}

node* lca(node* root, int node1, int node2)
{
    if (root == nullptr)
        return nullptr;
    if (!value_in_tree(root, node1) || !value_in_tree(root, node2))
        return nullptr;

    if (root->value > node1 && root->value > node2)
        return lca(root->left, node1, node2);
    if (root->value < node1 && root->value < node2)
        return lca(root->right, node1, node2);
    return root;
}

int main()
{
    node* root = new node(20);
    root->left = new node(8);
    root->right = new node(22);
    root->left->left = new node(4);
    root->left->right = new node(12);
    root->left->right->left = new node(10);
    root->left->right->right = new node(14);

    node* res1 = lca(root, 10, 14);
    if (res1 != nullptr)
        cout << res1->value << endl;
    node* res2 = lca(root, 4, 19);
    if (res2 == nullptr)
        cout << "given value not in the tree." << endl;

    return 0;
}