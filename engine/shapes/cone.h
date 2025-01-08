#ifndef CONE_H
#define CONE_H  

#include "shape.h"
#include <cmath>

class Cone : public Shape {
    public:
        Vec3 center;
        Vec3 direction;
        double radius;
        double height;
        Cone (): center(Vec3(0.0, 0.0, 0.0)), direction(Vec3(0.0, 1.0, 0.0)), radius(1.0), height(1.0), Shape() {}
        Cone (Vec3 center, Vec3 direction, double radius, double height, Material mat): center(center), direction(direction.normalize()), radius(radius), height(height), Shape(mat) {}
        
        inline Vec3 get_normal(Vec3 p) override {
            Vec3 v = p - center;
            double m = sqrt(v.dot(v) - pow(v.dot(direction), 2));
            return (v - direction * m * (radius / height)).normalize();
        }
        
        double intersects(Ray r) override {
            Vec3 v = center - r.origin;
            double cos_theta = height / sqrt(height * height + radius * radius);
            double sin_theta = radius / sqrt(height * height + radius * radius);
            double a = r.dr.dot(r.dr) - pow(r.dr.dot(direction), 2) - pow(cos_theta, 2) * (r.dr.dot(direction) * r.dr.dot(direction) - r.dr.dot(r.dr));
            double b = 2.0 * (r.dr.dot(v) - (r.dr.dot(direction) * v.dot(direction)) - pow(cos_theta, 2) * (r.dr.dot(direction) * v.dot(direction) - r.dr.dot(v)));
            double c = v.dot(v) - pow(v.dot(direction), 2) - pow(cos_theta, 2) * (v.dot(direction) * v.dot(direction) - v.dot(v));
            double delta = b * b - 4 * a * c;

            if (delta > 0.0) {
                double t1 = (-b + sqrt(delta)) / (2.0 * a);
                double t2 = (-b - sqrt(delta)) / (2.0 * a);
                return (t1 < t2 || t2 < 0.0) ? t1 : t2;
            } else {
                return -INFINITY;
            }
        }
};

#endif