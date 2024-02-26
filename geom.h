#include <bits/stdc++.h>
using namespace std;

struct Point {
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator +(const Point &a) {
        return {x + a.x, y + a.y};
    }
    Point operator -(const Point &b) {
        return {b.x - x, b.y - y};
    }
    double operator *(const Point &a) {
        return x * a.x + y * a.y;
    }
    double operator %(const Point &a) {
        return x * a.y - y * a.x;
    }
    double len() {
        return x * x + y * y;
    }
    double slen() {
        return hypot(x,y);
    }

    double x, y;
};

struct Triangle {
    Point a, b, c;
    bool isInside(const Point &x) {
        bool f1 = (((a-b) % (a - x)) * ((a - x) % (a - c)) >= 0 && ((a - b) % (a -c)) * ((a - x) % (a - c)) >= 0);
        bool f2 = (((b - a) % (b - x)) * ((b - x) % (b - c)) >= 0 && ((b - a) % (b - c)) * ((b - x) % (b - c)) >= 0);
        return f1 && f2;
    }
};
