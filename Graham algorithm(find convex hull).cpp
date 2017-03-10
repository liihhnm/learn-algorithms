//graham algorithm. Find convex hull.
//O(nlgn)
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <stack>
#include <cmath>

using namespace std;

#define LINEAR 0
#define CLOCK 1
#define C_CLOCK 2

struct dot {
    dot() = default;
    dot(double x, double y)
        : x(x), y(y)
    { }
    

    double x, y;
};

ostream& operator<<(ostream& ost, const dot& d)
{
    ost << d.x << " " << d.y;
    return ost;
}

dot q0;
//compare function used by sort
bool compare(const dot& x, const dot& y);

class graham {
public:
    graham() = default;
    void add_dot(double x, double y)
    {
        dots.push_back({ x, y });
        v++;
    }

    void convex_hull()
    {
        if (v < 2)
            return;
        //find origin
        double y_min = dots[0].y;
        int min = 0;
        for (int i = 1; i < v; i++)
        {
            if (dots[i].y < y_min ||
                (dots[i].y == y_min && dots[i].x < dots[min].x))
            {
                y_min = dots[i].y;
                min = i;
            }
        }
        q0 = dots[min];
        swap(dots[min], dots[0]);

        //sort by polar angle to origin
        sort(dots.begin() + 1, dots.end(), compare);

        //remove points with same angle with p0
        //but the one that's farthest with p0
        int index = 1;
        for (int i = 1; i < v; i++)
        {
            while (i < v - 1 &&
                LINEAR == orientation(q0, dots[i], dots[i + 1]))
                i++;
            dots[index] = dots[i];
            index++;
        }
        
        if (index < 2) return;
        
        //
        stack<dot> s;
        s.push(dots[0]);
        s.push(dots[1]);
        s.push(dots[2]);
        for (int i = 3; i < index; i++)
        {
            while (C_CLOCK != orientation(next_to_top(s), s.top(), dots[i]))
                s.pop();
            s.push(dots[i]);
        }

        //print answer
        while (!s.empty())
        {
            cout << s.top() << endl;
            s.pop();
        }
        cout << "done" << endl;
        return;
    }

    //return distance of tow dots
    static double dist(const dot& u, const dot& v)
    {
        return pow(u.x - v.x, 2) + pow(u.y - v.y, 2);
    }
    //return orientation of three dots
    static int orientation(const dot& i, const dot& j, const dot& k)
    {
        double cross_product = (j.x - i.x) * (k.y - j.y) -
            (k.x - j.x) * (j.y - i.y);
        if (abs(cross_product) < 1e-9)
            return LINEAR;
        return cross_product > 0 ? C_CLOCK : CLOCK;
    }
    
private:
    //helper function to extend stl stack
    static dot next_to_top(stack<dot>& s)
    {
        dot temp = s.top();
        s.pop();
        dot result = s.top();
        s.push(temp);
        return result;
    }

private:
    int v = 0;
    vector<dot> dots;
};

bool compare(const dot&x, const dot& y)
{
    int o = graham::orientation(q0, x, y);
    if (o == LINEAR)
        return graham::dist(q0, x) <= graham::dist(q0, y);
    return o == C_CLOCK ? true : false;
}

int main()
{
    graham g;
    g.add_dot(0, 3);
    g.add_dot(1, 1);
    g.add_dot(2, 2);
    g.add_dot(4, 4);
    g.add_dot(0, 0);
    g.add_dot(1, 2);
    g.add_dot(3, 1);
    g.add_dot(3, 3);
    g.convex_hull();

    return 0;
}