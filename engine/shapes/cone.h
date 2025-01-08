#ifndef CONE_H
#define CONE_H  

#include "shape.h"
#include <cmath>

class Cone : public Shape {
    public:
        Vec3 center;
        double radius;
        double height;
        Cone (): center(Vec3(0.0, 0.0, 0.0)), radius(1.0), height(1.0), Shape() {}
        Cone (Vec3 center, double radius, double height, Material mat): center(center), radius(radius), height(height), Shape(mat) {}
        
        inline Vec3 get_normal(Vec3 p) override { return ( p - center ).normalize(); }
        
        double intersects(Ray r) override {
            Vec3 v = center - r.origin;
            double a = r.dr.dot(r.dr) - (1 + pow(tan(radius), 2) + pow(tan(height), 2));
            double b = 2.0 * (r.dr.dot(v) - (1 + pow(tan(radius), 2) + pow(tan(height), 2)));
            double c = v.dot(v) - pow(tan(radius), 2) - pow(tan(height), 2);
            double delta = b*b - 4*a*c;

            if (delta > 0.0) {
                double t1 = (-b + sqrt(delta)) / (2.0*a);
                double t2 = (-b - sqrt(delta)) / (2.0*a);
                return (t1 < t2 || t2 < 0.0) ? t1 : t2;
            } else {
                return -INFINITY;
            }
        }
};
#endif