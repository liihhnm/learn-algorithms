#include <iostream>
#include <vector>
#include <iterator>
#include <climits>

using namespace std;

int ver_count = 0;
int source_ver = 0;
vector<vector<int>> graph;              //存储graph信息  
vector<int> dist;                      //标记是否探明各点最短路径  
vector<int> previous;                 //各点的最短路径长度  
vector<bool> has_viewed;               //各点最短路径下的前一个顶点 

void Dijkstra(int source_ver)
{
    //initialize the graph and other assist variables
    dist.assign(ver_count, INT_MAX);
    has_viewed.assign(ver_count, false);
    previous.resize(ver_count);
    previous[source_ver] = source_ver;
    dist[source_ver] = 0;

    for (; ; )
    {
        int min_dist = INT_MAX, v;
        
        //greedy choose: choose the shortest path in the vertex
        //that has not been viewed from the source at now
        for (int i = 0; i < ver_count; i++)
            if (!has_viewed[i] && dist[i] < min_dist)
            {
                min_dist = dist[i];
                v = i;
            }
        if (min_dist == INT_MAX)
            break;
        
        has_viewed[v] = true;

        //for the vertex that has been solved, traverse it's adjsent vertex
        //and execute relax operation
        for (int i = 0; i < ver_count; i++)
        {
            if (!has_viewed[i]
                && graph[v][i] != INT_MAX
                && dist[v] + graph[v][i] < dist[i])
            {
                dist[i] = dist[v] + graph[v][i];
                previous[i] = v;
            }
        }
    }

}

void print_path(int vertex)
{
    if (vertex != source_ver)
        print_path(previous[vertex]);
    cout << vertex << " ";
}

int main()
{
    ver_count = 7;
    graph.assign(ver_count, vector<int>(ver_count, INT_MAX));
    graph[0][1] = 2; graph[0][3] = 1; graph[0][2] = 4;
    graph[1][3] = 3; graph[1][4] = 10;
    graph[2][0] = 4; graph[2][5] = 5;
    graph[3][2] = 2; graph[3][4] = 2; graph[3][5] = 8; graph[3][6] = 4;
    graph[4][6] = 6;
    graph[6][5] = 1;
    source_ver = 0;
    Dijkstra(source_ver);
    cout << "source vertex: " << source_ver << endl;
    copy(dist.cbegin(), dist.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
    for (int i = 0; i < ver_count; i++)
    {
        cout << source_ver << " -> " << i << ": ";
        print_path(i);
        cout << endl;
    }
}