#ifndef CILINDER_H
#define CILINDER_H
//TEMOS UM CELENDRO AEOOO
#include "shape.h"
#include <cmath>

class Cilinder : public Shape {
    public:
        Vec3 center;
        double radius;
        double height;
        Cilinder (): center(Vec3(0.0, 0.0, 0.0)), radius(1.0), height(1.0), Shape() {}
        Cilinder (Vec3 center, double radius, double height, Material mat): center(center), radius(radius), height(height), Shape(mat) {}
        
        inline Vec3 get_normal(Vec3 p) override { 
            Vec3 top_center = center + Vec3(0, height, 0);
            if (std::abs((p - center).dot(Vec3(0, 1, 0))) < 1e-6) {
                return Vec3(0, -1, 0); // Bottom circle
            } else if (std::abs((p - top_center).dot(Vec3(0, 1, 0))) < 1e-6) {
                return Vec3(0, 1, 0); // Top circle
            } else {
                Vec3 projection = Vec3(p.x, center.y, p.z);
                return (p - projection).normalize(); // Side surface
            }
        }
        
        double intersects(Ray r) override {
            Vec3 top_center = center + Vec3(0, height, 0);
            double t_min = INFINITY;

            // Check intersection with the cylindrical surface
            Vec3 oc = r.origin - center;
            double a = r.dr.x * r.dr.x + r.dr.z * r.dr.z;
            double b = 2.0 * (oc.x * r.dr.x + oc.z * r.dr.z);
            double c = oc.x * oc.x + oc.z * oc.z - radius * radius;
            double delta = b * b - 4 * a * c;

            if (delta > 0.0) {
                double t1 = (-b - sqrt(delta)) / (2.0 * a);
                double t2 = (-b + sqrt(delta)) / (2.0 * a);
                Vec3 p1 = r.at(t1);
                Vec3 p2 = r.at(t2);
                if (t1 > 0 && p1.y >= center.y && p1.y <= top_center.y) {
                    t_min = t1;
                }
                if (t2 > 0 && p2.y >= center.y && p2.y <= top_center.y) {
                    t_min = std::min(t_min, t2);
                }
            }

            // Check intersection with the bottom circle
            double t_bottom = (center.y - r.origin.y) / r.dr.y;
            Vec3 p_bottom = r.at(t_bottom);
            if (t_bottom > 0 && (p_bottom - center).magnitude() <= radius) {
                t_min = std::min(t_min, t_bottom);
            }

            // Check intersection with the top circle
            double t_top = (top_center.y - r.origin.y) / r.dr.y;
            Vec3 p_top = r.at(t_top);
            if (t_top > 0 && (p_top - top_center).magnitude() <= radius) {
                t_min = std::min(t_min, t_top);
            }

            return t_min == INFINITY ? -INFINITY : t_min;
        }
};

#endif