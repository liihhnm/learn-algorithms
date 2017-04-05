//Bell-Ford's single source shortest paths algorithm
//allow existence of edge with negative weight
#include <utility>
#include <vector>
#include <iostream>
#include <climits>

using  namespace std;

typedef pair<int, int> i_pair;

class graph {
public:
    graph(int v, int e) : v(v), e(e)
    { }

    void add_edge(int u, int v, int w)
    {
        edges.push_back({ w, { u, v } });
    }

    bool bellman_ford(int src)
    {
        vector<int> dist(v, INT_MAX), previous(v);
        dist[src] = 0;
        for (int i = 0; i < v; i++)
            previous[i] = i;

        for (int i = 0; i < v - 1; i++)
        {
            for (const auto& edge : edges)
            {
                int u = edge.second.first, v = edge.second.second;
                int weight = edge.first;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    previous[v] = u;
                }
            }
        }

        for (const auto& edge : edges)
        {
            int u = edge.second.first, v = edge.second.second;
            int weight = edge.first;
            if (dist[u] != INT_MAX &&  dist[u] + weight < dist[v])
            {
                cout << "graph contains negative weight cycle" << endl;
                return false;
            }
        }


        cout << "source: " << src << endl;
        for (int i = 0; i < v; i++)
        {
            if (i != src)
            {
                cout << "vertex " << i << ": ";
                print_path(previous, i, src);
                cout << endl;
                cout << "weight  : " << dist[i] << endl;
            }
        }
        return true;
    }

    void print_path(const vector<int>& previous, int i, int src)
    {
        if (i != src)
            print_path(previous, previous[i], src);
        cout << i << " ";
    }

private:
    int v, e;
    vector< pair <int, i_pair>> edges;
};

int main()
{
    int v = 5, e = 8;
    graph g(v, e);

    //  making above shown graph
    g.add_edge(0, 1, -1);
    g.add_edge(0, 2, 4);
    g.add_edge(1, 2, 3);
    g.add_edge(1, 3, 2);
    g.add_edge(1, 4, 2);
    g.add_edge(3, 2, 5);
    g.add_edge(3, 1, 1);
    g.add_edge(4, 3, -3);

    g.bellman_ford(0);
}