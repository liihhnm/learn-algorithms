//Kosaraju's SCC algorithm
#include <vector>
#include <list>
#include <stack>
#include <iostream>

using namespace std;

class graph {
public:
    graph(int v) : v(v), g(new list<int>[v])
    { }

    void add_edge(int u, int v)
    {
        g[u].push_back(v);
    }

    graph reverse()
    {
        graph reverse_g(v);
        for (int i = 0; i < v; i++)
        {
            for (const auto& vertex : g[i])
                reverse_g.add_edge(vertex, i);
        }
        return reverse_g;
    }

    void SCC()
    {
        //get finished order, store it in a stack
        //and the last finished vertex is in the top of the stack
        stack<int> s;
        vector<bool> visited(v, false);
        for (int i = 0; i < v; i++)
        {
            if (!visited[i])
                finished_order(i, visited, s);
        }

        //get reverse graph
        graph reverse_g = this->reverse();

        //calculate SCC
        fill(visited.begin(), visited.end(), false);
        int count = 0;
        vector< vector<int> > scc;
        while (!s.empty())
        {
            int v = s.top();
            s.pop();
            
            if (!visited[v])
            {
                count++;
                scc.push_back(vector<int>());
                reverse_g.dfs(v, visited, scc[count - 1]);
            }
        }

        //print answer
       cout << "there are total " << count << " SCCs" << endl;
       for (const auto& component : scc)
       {
           for (const auto& vertex : component)
               cout << vertex << " ";
           cout << endl;
       }
    }
private:
    void finished_order(int v, vector<bool>& visited, stack<int>& s)
    {
        visited[v] = true;

        for (const auto& vertex : g[v])
        {
            if (!visited[vertex])
                finished_order(vertex, visited, s);
        }


        s.push(v);
    }

    void dfs(int v, vector<bool>& visited, vector<int>& record)
    {
        visited[v] = true;
        record.push_back(v);

        for (const auto& vertex : g[v])
        {
            if (!visited[vertex])
                dfs(vertex, visited, record);
        }

    }

private:
    int v;
    list<int>* g;
};

int main()
{

    graph g(5);
    g.add_edge(1, 0);
    g.add_edge(0, 2);
    g.add_edge(2, 1);
    g.add_edge(0, 3);
    g.add_edge(3, 4);
    g.SCC();
    
}