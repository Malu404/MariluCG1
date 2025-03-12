#ifndef PLANE_H
#define PLANE_H

#include "shape.h"
#include "textura.h"
#include <cmath>

class Plane : public Shape {
    public:
        Vec3 p0;
        Vec3 normal;
        Texture* texture;
        double x_scale;
        double y_scale;
        Plane (): Shape(), p0(Vec3(0.0, 0.0, 0.0)), normal(Vec3(0.0, -1.0, 0.0)) {}
        Plane (Vec3 p0, Vec3 normal, Material mat, Texture* textura, double x_scale, double y_scale): Shape(mat), p0(p0), normal(normal.normalized()), texture(textura), x_scale(x_scale), y_scale(y_scale){}
        
        inline Vec3 get_normal(Vec3 _) const override { return normal; }

        std::pair<double, double> get_uv(const Vec3& point) const {
            Vec3 basis1 = (normal.cross(Vec3(1, 0, 0))).normalized(); // First basis vector
            if (basis1.magnitude() < 1e-6) { // If the normal is aligned with x-axis, use y-axis
                basis1 = (normal.cross(Vec3(0, 1, 0))).normalized();
            }
            Vec3 basis2 = normal.cross(basis1); // Second basis vector
    
            // Calculate texture coordinates
            double u = (point - p0).dot(basis1) / y_scale; // eixo z
            double v = (point - p0).dot(basis2) / x_scale; // eixo x
    
            // Normalize u and v if necessary (depends on your texture size)
            // For example, if your texture is 1x1 unit:
            u = u - floor(u); // Wrap around to [0, 1]
            v = v - floor(v); // Wrap around to [0, 1]

            return {u, v};
        }
        

        double intersects(Ray r) const override {
            double top = normal.dot(r.origin - p0);
            double bottom = normal.dot(r.dr);
            if (bottom == 0.0) { return -INFINITY; }
            return -top/bottom;
        }

        void transform(Matriz4x4 m) override {
            p0 = m * p0;
        }
};

#endif