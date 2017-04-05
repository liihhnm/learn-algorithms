//Floyd Warshall's all pairs shortest path algorithm
//O(n^3)
//can check if there exist negative cycle by
//iterating throught diagonal ele of the dist matrix.
//if any place is less than 0, then a negative cycly exist
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;

#define INF 999999

class graph {
public:
    graph(int v) : v(v), g(vector< vector<int> >(v, vector<int>(v, INF)))
    {
        for (int i = 0; i < v; i++)
            g[i][i] = 0;
    }

    void add_edge(int u, int v, int weight)
    {
        g[u][v] = weight;
    }

    void floyd_warshall()
    {
        vector< vector<int> > dist(g);
        vector< vector<int> > previous(g);
        //initialize previous[][]
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                if (i == j || dist[i][j] == INF)
                    previous[i][j] = INF;
                else if (dist[i][j] != INF)
                    previous[i][j] = i;
            }
        }

        for (int k = 0; k < v; k++)
        {
            for (int i = 0; i < v; i++)
            {
                for (int j = 0; j < v; j++)
                {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        previous[i][j] = previous[k][j];
                    }
                }
            }
        }
        print_answer(dist, previous);
    }

private:
    void print_answer(const vector<vector<int>>& dist, const vector<vector<int>>& previous)
    {
        printf("%s\n", "dist matrix");
        for (const auto& row : dist)
        {
            for (const auto& vertex : row)
            {
                if (vertex == INF)
                    printf("%6s", "INF");
                else
                    printf("%6d", vertex);
            }
            putchar('\n');
        }
        printf("%s\n", "previous matrix");
        for (const auto& row : previous)
        {
            for (const auto& vertex : row)
            {
                if (vertex == INF)
                    printf("%6s", "NIL");
                else
                    printf("%6d", vertex);
            }
            putchar('\n');
        }
    }

private:
    int v;
    vector< vector<int> > g;
};

int main()
{
    graph g(5);
    g.add_edge(0, 1, 3);
    g.add_edge(0, 2, 8);
    g.add_edge(0, 4, -4);
    g.add_edge(1, 3, 1);
    g.add_edge(1, 4, 7);
    g.add_edge(2, 1, 4);
    g.add_edge(3, 0, 2);
    g.add_edge(3, 2, -5);
    g.add_edge(4, 3, 6);
    g.floyd_warshall();

}