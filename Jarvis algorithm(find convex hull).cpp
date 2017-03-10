//jarvis convex hull algorithm
//O(nh) while h is the number of vertice in the convex hull
#include <vector>
#include <iostream>
#include <algorithm>

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
class jarvis {
public:
    jarvis() = default;
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
        swap(dots[min], dots[0]);
        //
        vector<dot> result;
        
        int current = 0;
        do
        {
            result.push_back(dots[current]);
            int next = (current + 1) % v;

            for (int i = 0; i < v; i++)
                if (orientation(dots[current], dots[i], dots[next]) == C_CLOCK)
                    next = i;

            current = next;
        } while (current != 0);

        for (const auto& d : result)
            cout << d << endl;
    }

private:
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
    int v = 0;
    vector<dot> dots;
};

int main()
{
    jarvis g;
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


