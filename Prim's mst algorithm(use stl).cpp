//implement of prim's MST algorithm
//use c++ STL container adopter: priority queue
//based on: http://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/


//The algorithm discussed here can be modified so that decrease key is never required. 
//The idea is, not to insert all vertices in priority queue, but only those which are 
//not MST and have been visited through a vertex that has included in MST. 
//We keep track of vertices included in MST in a separate boolean array inMST[].
#include <list>
#include <utility>
#include <climits>
#include <cstdio>
#include <queue>
#include <functional>
#include <iostream>

using namespace std;

typedef pair<int, int> i_pair; //first: connected vertex; second: edge weight

class graph {
    int v;
    list<pair<int, int>>* adj_list;

public:
    graph(int v) : v(v), adj_list(new list<pair<int, int>>[v])
    { }

    void add_edge(int u, int v, int w)
    {
        adj_list[u].push_back(make_pair(v, w));
        adj_list[v].push_back(make_pair(u, w));
    }

    int prim_mst()
    {
        priority_queue<i_pair, vector<i_pair>, greater<i_pair>> pq;
        int src = 0;
        int weight = 0;

        vector<int> key(v, INT_MAX);
        vector<int> previous(v, -1);
        vector<bool> in_mst(v, false);

        pq.push(make_pair(0, src));
        key[src] = 0;

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            //optimize
            /***********************/
            if (in_mst[u])
                continue;
            /***********************/

            in_mst[u] = true;
            for (auto i = adj_list[u].begin(); i != adj_list[u].end(); ++i)
            {
                int weight = i->second;
                int v = i->first;

                if (!in_mst[v] && key[v] > weight)
                {
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    previous[v] = u;
                }
            }
        }

        for (int i = 1; i < v; ++i)
        {
            int j = previous[i];
            printf("%d -> %d\n", j, i);
            for (const auto& p : adj_list[i])
            {
                if (p.first == j)
                    weight += p.second;
            }
        }
        return weight;
    }

    ~graph()
    {
        delete[] adj_list;
    }
};

int main()
{
    int v = 9, e = 14;
    graph g(v);

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

    cout << g.prim_mst() << endl;

    return 0;
}













