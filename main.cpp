#include "geom.h"

const int N = 512, M = 512;
const int MAXCOLOR = 225;

struct Light{
    Light(Point p, double in) : pos(p), intensity(in) {}

    Point pos;
    double intensity;
};

struct Pixel {
    Pixel(double intensity, Color col): col(col), intensity(intensity) {}

    double intensity;
    Color col;
};

ostream& operator<<(ostream &out, Pixel a) {
    return out << (int)(min(1.0,a.col.r * a.intensity) * MAXCOLOR) << ' ' << (int)(min(1.0,a.col.g * a.intensity) * MAXCOLOR) << ' ' << (int)(min(1.0,a.col.b * a.intensity) * MAXCOLOR) << '\n';
}


void drawSphere(vector<vector<Pixel>> &pic, Point o, vector<Light> &lights, vector<Sphere> &a) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            double cy = i - N / 2.0;
            double cx = j - M / 2.0;
            double x = cx / M;
            double y = -cy / N;
            double z = 1;
            Vector ray = Vector(o, Point(x,y,z)).Norm();
            double mindist = INF;
            double svet = 0;
            Color c;
            for (auto sphere : a) {
                auto Inter = sphere.Intersection(o, ray);
                if (Inter.x == -INF) {
                    continue;
                } else {
                    if (Vector(Inter, o).len() > mindist) {
                        continue;
                    }
                    mindist = Vector(Inter, o).len();
                    Vector norm = Vector(Inter, sphere.o).Norm();
                    c = sphere.col;
                    svet = 0;
                    for (auto light : lights) {
                        Vector raylight = Vector(Inter, light.pos).Norm();
                        double intensity = max(0.0, norm * raylight) * light.intensity;
                        svet += intensity;
                    }
                }
            }
            pic[i][j] = {svet, c};
        }
    }
}


void output(ostream &out, vector<vector<Pixel>> &pic) {
    out << "P3\n";
    out << M << ' ' << N << '\n';
    out << MAXCOLOR << '\n';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            out << pic[i][j] << '\n';
        }
    }
}

int main() {
    ofstream out;
    out.open("sphere.ppm");
    vector<vector<Pixel>> picture(N, vector<Pixel>(M, {0,{0.5,0.5,0.5}}));
    vector<Sphere> spheres = {{{-2, 0.5, 7}, {1,0,0}, 1.77}, {{2, 0.7, 8}, {0,0,1}, 1.7}};
    vector<Light> lights = {{ {Point(0, 10, -7),1.8}}};
    drawSphere( picture, {0,0,0}, lights, spheres);
    output(out, picture);
    return 0;
}
