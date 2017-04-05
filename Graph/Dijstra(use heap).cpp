//Dijkstra algorithm. Use heap

#include <vector>
#include <utility>
#include <iostream>
#include <climits>
#include <list>

using namespace std;

typedef pair<int, int> i_pair;

//associated heap
class heap {
public:
    heap(int v) : size(v), capacity(v), position(v), arr(v)
    {
        for (int i = 0; i < v; i++)
        {
            position[i] = i;
            arr[position[i]] = { i, INT_MAX };
        }
    }

    bool is_empty()
    {
        return size == 0;
    }

    i_pair extract_min()
    {
        i_pair result = arr[0];
        position[arr[0].first] = size - 1;
        position[arr[size - 1].first] = 0;
        swap(arr[0], arr[size - 1]);
        size--;
        min_heapify(0);
        return result;
    }

    //decrease and swim
    void decrease(int v, int weight)
    {
        int i = position[v];
        arr[i].second = weight;

        while (i && arr[i].second < arr[(i - 1) / 2].second)
        {
            position[arr[i].first] = (i - 1) / 2;
            position[arr[(i - 1) / 2].first] = i;
            swap(arr[i], arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    bool in_heap(int v)
    {
        return position[v] < size;
    }

private:
    //sink
    void min_heapify(int index)
    {
        int smallest = index,
            left = index * 2 + 1,
            right = index * 2 + 2;

        if (left < size && arr[left].second < arr[smallest].second)
            smallest = left;
        if (right < size && arr[right].second < arr[smallest].second)
            smallest = right;

        if (smallest != index)
        {
            position[arr[smallest].first] = index;
            position[arr[index].first] = smallest;

            swap(arr[smallest], arr[index]);
            min_heapify(smallest);
        }
    }

private:
    int size, capacity;
    vector<int> position;
    vector<i_pair> arr;
};

class graph {
public:
    graph(int v) : v(v), adj_list(new list<i_pair>[v])
    { }

    void add_edge(int u, int v, int weight)
    {
        adj_list[u].push_back({ v, weight });
    }

    void Dijkstra(int src)
    {
        heap h(v);
        h.decrease(src, 0);
        vector<int> dist(v, INT_MAX), previous(v);
        dist[src] = 0;
        previous[src] = src;

        while (!h.is_empty())
        {
            i_pair temp = h.extract_min();
            dist[temp.first] = temp.second;

            for (auto& v : adj_list[temp.first])
            {
                if (h.in_heap(v.first) && dist[temp.first] != INT_MAX
                    && v.second + dist[temp.first] < dist[v.first])
                {
                    dist[v.first] = v.second + dist[temp.first];
                    previous[v.first] = temp.first;
                    h.decrease(v.first, dist[v.first]);
                }
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
    }

private:
    void print_path(const vector<int>& previous, int i, int src)
    {
        if (i != src)
            print_path(previous, previous[i], src);
        cout << i << " ";
    }

private:
    int v;
    list <i_pair>* adj_list;
};

int main()
{
    graph g(9);
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

    g.Dijkstra(0);
}