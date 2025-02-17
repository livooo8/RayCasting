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
    out.open("photo.ppm");
    vector<vector<Pixel>> picture(N, vector<Pixel>(M));
    Triangle t = {{200, 200}, {654,12}, {978, 1032}};
    drawTriangle(t, picture);
    output(out, picture);
    return 0;
}
