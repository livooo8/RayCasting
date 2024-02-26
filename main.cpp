#include "geom.h"

const int N = 1024, M = 1024;
const int MAXCOL = 225;

struct Pixel {
    Pixel(double r = 0, double g = 0, double b = 0): r(r), g(g), b(b) {}

    double r, g, b;
};

void drawTriangle(Triangle &a, vector<vector<Pixel>> &pic) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (a.isInside(Point(i,j))) {
                pic[i][j].r = 1;
                pic[i][j].b=1;
                pic[i][j].g = 1;
            }
        }
    }
}

void drawSquare(Point a, Point b, vector<vector<Pixel>> &pic) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i >= a.x && j >= a.y && i <= b.x && j <= b.y) {
                pic[i][j].r = 1;
                pic[i][j].g = 1;
                pic[i][j].b = 1;
            }
        }
    }
}

void drawGradient(vector<vector<Pixel>> &pic) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            pic[i][j].r = i / 1024.0;
            pic[i][j].g = j / 1024.0;
            pic[i][j].b = 1;
        }
    }
}

void drawCircle(Point o, double r, vector<vector<Pixel>> &pic) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if ((i - o.x) * (i - o.x) + (j - o.y) * (j-o.y) <= r * r) {
                pic[i][i].r = 1;
                pic[i][j].g = 1;
                pic[i][j].b = 1;
            }
        }
    }
}

ostream& operator<<(ostream &out, Pixel a) {
    return out << (int)(a.r * MAXCOL) << ' ' << (int)(a.g * MAXCOL) << ' ' << (int)(a.b * MAXCOL) << '\n';
}

void output(ostream &out, vector<vector<Pixel>> &pic) {
    out << "P3\n";
    out << M << ' ' << N << '\n';
    out << MAXCOL << '\n';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            out << pic[i][j] << '\n';
        }
    }
}

int main() {
    ofstream out;
    out.open("circle.ppm");
    vector<vector<Pixel>> picture(N, vector<Pixel>(M));
    drawCircle({500,500},60,picture);
    output(out, picture);
    return 0;
}
