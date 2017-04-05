//based on: http://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

using  namespace std;

typedef pair<int, int> i_pair;

class union_find {
    vector<int> previous, rank;
    int n;

public:
    union_find(int n) : n(n), previous(n), rank(n, 0)
    {
        for (int i = 0; i < n; i++)
            previous[i] = i;
    }

    int find(int u)
    {
        if (u != previous[u])
            previous[u] = find(previous[u]);
        return previous[u];
    }

    void merge(int x, int y)
    {
        int x_root = find(x);
        int y_root = find(y);

        if (rank[x] > rank[y])
            previous[y] = x;
        else
        {
            previous[x] = y;
            if (rank[x] == rank[y])
                rank[y]++;
        }
    }
};

class graph {
    int v, e;
    //<first: weight; second: <first: u
    //                         second: v>>
    vector< pair< int, i_pair> > edges;

public:
    graph(int v, int e) : v(v), e(e)
    { }

    void add_edge(int u, int v, int w)
    {
        edges.push_back({ w,{ u, v } });
    }

    int kruskal_mst()
    {
        int weight = 0;

        sort(edges.begin(), edges.end());

        union_find uf(v);

        for (auto itr = edges.begin(); itr != edges.end(); itr++)
        {
            int u = itr->second.first;
            int v = itr->second.second;
            int set_u = uf.find(u);
            int set_v = uf.find(v);

            if (set_u != set_v)
            {
                cout << u << " - " << v << endl;

                weight += itr->first;
                uf.merge(set_u, set_v);
            }
        }
        return weight;
    }
};

int main()
{
    int v = 9, e = 14;
    graph g(v, e);

    //  making above shown graph
    g.add_edge(0, 1, 4);
    g.add_edge(0, 7, 8);
    g.add_edge(1, 2, 8);
    g.add_edge(1, 7, 11);
    g.add_edge(2, 3, 7);
    g.add_edge(2, 8, 2);
    g.add_edge(2, 5, 4);
    g.add_edge(3, 4, 9);
    g.add_edge(3, 5, 14);
    g.add_edge(4, 5, 10);
    g.add_edge(5, 6, 2);
    g.add_edge(6, 7, 1);
    g.add_edge(6, 8, 6);
    g.add_edge(7, 8, 7);

    cout << "Edges of MST are \n";
    int mst_wt = g.kruskal_mst();

    cout << "\nWeight of MST is " << mst_wt;

    return 0;
}