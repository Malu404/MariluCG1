#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"
#include <cmath>
#include "textura.h"

class Sphere : public Shape {
public:
    Vec3 center;
    double radius;
    Texture* texture;

    Sphere() : center(Vec3(0.0, 0.0, 0.0)), radius(1.0), Shape(), texture(nullptr) {}
    
    Sphere(Vec3 center, double radius, Material mat, Texture* texture = nullptr)
        : center(center), radius(radius), Shape(mat), texture(texture) {}

    inline Vec3 get_normal(Vec3 p) const override { 
        return (p - center).normalize(); 
    }

    std::pair<double, double> get_uv(const Vec3& point) const {
        Vec3 dir = (point - center).normalize();
        double u = 0.5 + atan2(dir.z, dir.x) / (2 * M_PI);
        double v = 0.5 - asin(dir.y) / M_PI;
        return {u, v};
    }

    double intersects(Ray r) const override {
        Vec3 oc = r.origin - center;
        double a = r.dr.dot(r.dr);
        double b = 2.0 * oc.dot(r.dr);
        double c = oc.dot(oc) - radius * radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return -INFINITY;
        }

        double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

        if (t1 > 0) return t1;
        if (t2 > 0) return t2;
        return -INFINITY;
    }
};

#endif