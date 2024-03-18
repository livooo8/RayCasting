#include "geom.h"

const int N = 512, M = 512;
const int MAXCOLOR = 225;

struct Light {
    Light(Point p, double in) : pos(p), intensity(in) {}

    Point pos;
    double intensity;
};

struct Pixel {
    Pixel(double intensity, double spec, Color col) : col(col), specular(spec), intensity(intensity) {}

    double intensity;
    double specular;
    Color col;
};

ostream &operator<<(ostream &out, Pixel a) {
    return out << (int) (min(1.0, a.col.r * a.intensity + a.specular) * MAXCOLOR) << ' '
               << (int) (min(1.0, a.col.g * a.intensity + a.specular) * MAXCOLOR) << ' '
               << (int) (min(1.0, a.col.b * a.intensity + a.specular) * MAXCOLOR) << '\n';
}

Vector Reflection(Vector norm, Vector a) {
    double angle = norm * (a.Mul(-1));
    Vector x = norm.Mul(angle);
    Vector y = a - x.Mul(-1);
    Vector reflected = x + y;
    return reflected.Norm();
}

Color Relect(Vector ray, Point Inter, )

void drawSphere(vector<vector<Pixel>> &pic, Point o, vector<Light> &lights, vector<Sphere> &a) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {

            double x = -0.5 + (double) j / M;
            double y = 0.5 - (double) i / N;
            double z = 1;
            Vector ray = Vector(o, Point(x, y, z));
            double mindist = INF;
            Color c;
            Vector norm;
            int ind = -1;
            Sphere the_nearest = {Point(0, 0, 0), Color(0, 0, 0), 0};
            for (int q = 0; q < a.size(); q++) {
                auto sphere = a[q];
                auto Inter = sphere.Intersection(o, ray);
                if (Inter.x == -INF || Vector(Inter, o).len() > mindist) {
                    continue;
                } else {
                    mindist = Vector(Inter, o).len();
                    norm = Vector(sphere.o, Inter).Norm();
                    c = sphere.col;
                    the_nearest = sphere;
                    ind = q;
                }
            }
            if (ind == -1) {
                pic[i][j] = {1, 0, {0.5, 0.5, 0.5}};
                continue;
            }
            Point Inter = the_nearest.Intersection(o, ray);
            double IntSum = 0;
            double AngSum = 0;

            for (int q = 0; q < lights.size(); q++) {
                bool fl = true;
                auto light = lights[q];
                double d = Vector(light.pos, Inter).slen();
                for (int q1 = 0; q1 < a.size(); q1++) {
                    if (q1 == ind) continue;
                    auto isInt = a[q1].Intersection(light.pos, Vector(light.pos, Inter).Norm());
                    if (Vector(isInt, light.pos).slen() < d) {
                        fl = false;
                    }
                }
                if (!fl)continue;
                Vector raylight = Vector(Inter, light.pos).Norm();
                IntSum += max(0.0, norm * raylight) * light.intensity;
                Vector ref = Reflection(Vector(the_nearest.o, Inter).Norm(), Vector(light.pos, Inter).Norm());
                double ang = pow(max(0.0, ref * Vector(Inter, o).Norm()), 51);
                AngSum += ang;
            }

            pic[i][j] = {IntSum, AngSum, c};
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
    vector<vector<Pixel>> picture(N, vector<Pixel>(M, {0, 0, {0.5, 0.5, 0.5}}));
    vector<Sphere> spheres = {{{1,  0, 5}, {1, 0, 0}, 1},
                              {{-1.3, 0, 6}, {0, 1, 0}, 1.2}};
    vector<Light> lights = {{Point(5, 0, 0),     1}};
    drawSphere(picture, {0, 0, 0}, lights, spheres);
    output(out, picture);
    return 0;
}
