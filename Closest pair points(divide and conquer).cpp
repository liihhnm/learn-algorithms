#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cmath>

using namespace std;

class points_set {
public:

    struct point {
        double x;
        double y;
        point() : x(0.0), y(0.0)
        { }
        point(double x, double y) : x(x), y(y)
        { }
    };
public:
    points_set() = default;
    void add_point(double x, double y)
    {
        set.push_back({ x, y });
    }

    double closest_pair()
    {
        vector<point> point_x(set);
        vector<point> point_y(set);
        //sort point set separately by x coor and y coor
        sort(point_x.begin(), point_x.end(), compare_x);
        sort(point_y.begin(), point_y.end(), compare_y);

        return closest_pair_helper(point_x, point_y, 0, point_y.size() - 1);
    }

private:
    double closest_pair_helper(const vector<point>& point_x, const vector<point>& point_y,
        int first, int last)
    {
        int size = last - first + 1;
        if (size <= 3)
            return brute_force_search(point_x, first, last);

        int mid = first + (last - first) / 2;
        point mid_point = point_x[mid];

        //divide point_y into two parts according to the vertical split line
        //and these two part are already sorted by y coor!!!
        vector<point> point_y_left(mid - first + 1);
        vector<point> point_y_right(last - mid);
        int left_index = 0, right_index = 0;
        for (int i = 0; i < size; ++i)
        {
            if (point_y[i].x <= mid_point.x && left_index < mid - first + 1)
                point_y_left[left_index++] = point_y[i];
            else
                point_y_right[right_index++] = point_y[i];
        }

        //calculate smallest dist of left and right side
        double dist_left = closest_pair_helper(point_x, point_y_left, first, mid);
        double dist_right = closest_pair_helper(point_x, point_y_right, mid + 1, last);

        double current_min = min(dist_left, dist_right);
        
        //find closest pair points in strip area
        vector<point> strip;
        for (int i = 0; i < size; ++i)
            if (abs(point_y[i].x - mid_point.x) < current_min)
                strip.push_back(point_y[i]);

        return min(current_min, strip_closest(strip, current_min));
    }

    //when there are less than 4 points, use brute force search to find min dist
    double brute_force_search(const vector<point>& point_x, int first, int last)
    {
        double min = DBL_MAX;
        for (auto& itr = point_x.cbegin() + first; itr <= point_x.cbegin() + last; ++itr)
        {
            for (auto& itr2 = itr + 1; itr2 <= point_x.cbegin() + last; ++itr2)
                if (dist(*itr, *itr2) < min)
                    min = dist(*itr, *itr2);
        }
        return min;
    }

    double strip_closest(vector<point>& strip, double current_min)
    {
        double min = current_min;
        int size = strip.size();
        //compare at most with 7 other points
        for (int i = 0; i < size; ++i)
        {
            for (int j = i + 1; j < size && strip[j].y - strip[i].y; ++j)
                if (dist(strip[i], strip[j]) < min)
                    min = dist(strip[i], strip[j]);
        }
        return min;
    }

    double dist(const point& x, const point& y)
    {
        return sqrt(pow(x.x - y.x, 2) + pow(x.y - y.y, 2));
    }

    static bool compare_x(const point& x, const point& y)
    {
        return x.x < y.x;
    }

    static bool compare_y(const point& x, const point& y)
    {
        return x.y < y.y;
    }

private:
    vector<point> set;
};

int main()
{
    points_set ps;
    ps.add_point(2, 3);
    ps.add_point(12, 30);
    ps.add_point(40, 50);
    ps.add_point(5, 1);
    ps.add_point(12, 10);
    ps.add_point(3, 4);
    cout << ps.closest_pair() << endl;
    return 0;
}