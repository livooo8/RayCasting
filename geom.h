#pragma once

#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;

struct Point {
    Point() {}

    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    double x, y, z;
};

struct Vector {
    Vector() {}

    Vector(const Point a, const Point b) : x(b.x - a.x), y(b.y - a.y), z(b.z - a.z) {}

    Vector(double x, double y, double z) : x(x), y(y), z(z) {}

    Point operator+(const Point &a) {
        return {x + a.x, y + a.y, z + a.z};
    }

    double operator*(const Vector &a) {
        return x * a.x + y * a.y + z * a.z;
    }

    Vector Mul(double a) {
        return {x * a, y * a, z * a};
    }

    double len() {
        return x * x + y * y + z * z;
    }

    double slen() {
        return sqrt(x * x + y * y + z * z);
    }

    Vector Norm() {
        double l = slen();
        return {x / l, y / l, z / l};
    }

    double x, y, z;
};

Vector operator-(const Point &a, const Point &b) {
    return {b.x - a.x, b.y - a.y, b.z - a.z};
}

struct Color {

    Color(double r=0, double g=0, double b=0) : r(r), g(g), b(b) {}
    double r, g, b;
};

struct Sphere {
    Point Intersection(Point pos, Vector ray) {
        auto u = (pos - o);
        double a = ray * ray;
        double b = ray * u * 2;
        double c = u * u - r * r;
        double D = b * b - 4 * a * c;
        if (D < 0) {
            return {-2e9, -2e9, -2e9};
        }
        double t1 = (-b + sqrt(D)) / (2 * a);
        double t2 = (-b - sqrt(D)) / (2 * a);

        Point f = ray.Mul(t1) + pos;
        Point s = ray.Mul(t2) + pos;

        if ((f - pos).len() < (f - pos).len()) {
            return f;
        } else {
            return s;
        }
    }

    Point o;
    Color col;
    double r;
};
