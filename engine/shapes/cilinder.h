#ifndef CILINDER_H
#define CILINDER_H

#include "shape.h"
#include <cmath>

class Cilinder : public Shape {
    public:
        Vec3 center;
        Vec3 direction;
        double radius;
        double height;
        bool tem_tampa;
        bool tem_base;
        Cilinder (): Shape(), center(Vec3(0.0, 0.0, 0.0)), direction(Vec3(0.0, 1.0, 0.0)), radius(1.0), height(1.0), tem_tampa(true), tem_base(true) {}
        Cilinder (Vec3 center, Vec3 direction, double radius, double height, Material mat, bool tem_base, bool tem_tampa): Shape(mat), center(center), direction(direction.normalized()), radius(radius), height(height), tem_tampa(tem_tampa), tem_base(tem_base) {}
        
        inline Vec3 get_normal(Vec3 p) const override { 
            Vec3 top_center = center + direction * height;
            if (std::abs((p - center).dot(direction)) < 1e-6) {
                return -direction; // circulo base
            } else if (std::abs((p - top_center).dot(direction)) < 1e-6) {
                return direction; // circulo topo
            } else {
                Vec3 projection = center + direction * ((p - center).dot(direction));
                return (p - projection).normalized(); // casca do cilindro
            }
        }

        void transform(Matriz4x4 m) override {
            Vec3 ctopo = center + direction * height;
            center = m * center;
            ctopo = m * ctopo;
            direction = (ctopo - center).normalized();
        }
        
        double intersects(Ray r) const override {
            Vec3 top_center = center + direction * height;
            double t_min = INFINITY;

            //confere interseção com o cilindro
            Vec3 oc = r.origin - center;
            Vec3 d = r.dr - direction * (r.dr.dot(direction));
            Vec3 oc_proj = oc - direction * (oc.dot(direction));
            double a = d.dot(d);
            double b = 2.0 * d.dot(oc_proj);
            double c = oc_proj.dot(oc_proj) - radius * radius;
            double delta = b * b - 4 * a * c;

            if (delta > 0.0) {
                double t1 = (-b - sqrt(delta)) / (2.0 * a);
                double t2 = (-b + sqrt(delta)) / (2.0 * a);
                Vec3 p1 = r.at(t1);
                Vec3 p2 = r.at(t2);
                if (t1 > 0 && (p1 - center).dot(direction) >= 0 && (p1 - center).dot(direction) <= height) {
                    t_min = t1;
                }
                if (t2 > 0 && (p2 - center).dot(direction) >= 0 && (p2 - center).dot(direction) <= height) {
                    t_min = std::min(t_min, t2);
                }
            }

            // verifica interseção com o circulo base
            if (tem_base) {
                double t_bottom = (center - r.origin).dot(direction) / r.dr.dot(direction);
                Vec3 p_bottom = r.at(t_bottom);
                if (t_bottom > 0 && (p_bottom - center).magnitude() <= radius) {
                    t_min = std::min(t_min, t_bottom);
                }
            }

            // verifica interseção com o circulo topo
            if (tem_tampa) {
                double t_top = (top_center - r.origin).dot(direction) / r.dr.dot(direction);
                Vec3 p_top = r.at(t_top);
                if (t_top > 0 && (p_top - top_center).magnitude() <= radius) {
                    t_min = std::min(t_min, t_top);
                }
            }

            return t_min == INFINITY ? -INFINITY : t_min;
        }
};

#endif