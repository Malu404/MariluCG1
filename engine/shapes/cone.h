#ifndef CONE_H
#define CONE_H

#include "shape.h"
#include <cmath>

class Cone : public Shape {
public:
    Vec3 base_center;
    Vec3 top_vertex;
    Vec3 axis_direction;
    double radius;
    double height;
    bool capped;

    void transform(Matriz4x4 m) override {
        base_center = m * base_center;
        top_vertex = m * top_vertex;
        update_constants();
        axis_direction = (top_vertex - base_center).normalized();
    }

    Cone() : Shape(), base_center(Vec3(0.0, 0.0, 0.0)), top_vertex(Vec3(0.0, 1.0, 0.0)), radius(1.0), capped(true) {
        update_constants();
        axis_direction = (top_vertex-base_center).normalized();
        height = (top_vertex - base_center).magnitude();
    }

    Cone(Vec3 base_center, Vec3 top_vertex, double radius, Material mat, bool capped = true)
        : Shape(mat), base_center(base_center), top_vertex(top_vertex), radius(std::fmax(0, radius)), capped(capped) {
        update_constants();
        axis_direction = (top_vertex - base_center).normalized();
    }

    /*inline Vec3 get_normal(Vec3 p) const override {
        Vec3 v = p - top_vertex;
        double m = sqrt(v.dot(v) - pow(v.dot(axis_direction), 2));
        return (v - axis_direction * m * (radius / height)).normalized();
    }*/
    inline Vec3 get_normal(Vec3 p) const override {
        Vec3 apex_to_p = p - top_vertex;
        double projection = apex_to_p.dot(axis_direction);
        Vec3 normal = (apex_to_p - axis_direction * projection).normalized();
        return normal;
    }

    double intersects(Ray r) const override {
        Vec3 cone_to_origin = r.origin - top_vertex;
        Vec3 axis_direction_normalized = axis_direction.normalized();
    
        // Check intersection with the cone surface
        double a = r.dr.dot(axis_direction_normalized) * r.dr.dot(axis_direction_normalized) - cos_angle_sq * r.dr.dot(r.dr);
        double b = 2.0 * (r.dr.dot(axis_direction_normalized) * cone_to_origin.dot(axis_direction_normalized) - cos_angle_sq * r.dr.dot(cone_to_origin));
        double c = cone_to_origin.dot(axis_direction_normalized) * cone_to_origin.dot(axis_direction_normalized) - cos_angle_sq * cone_to_origin.dot(cone_to_origin);
    
        double delta = b * b - 4 * a * c;
    
        double t_min = INFINITY;
    
        if (delta > 0.0) {
            double t1 = (-b - sqrt(delta)) / (2.0 * a);
            double t2 = (-b + sqrt(delta)) / (2.0 * a);
            if (t1 > 0) {
                Vec3 p1 = r.at(t1);
                Vec3 intersection_to_apex = top_vertex - p1;
                double height_at_intersection = intersection_to_apex.dot(axis_direction_normalized);
                if (height_at_intersection >= 0 && height_at_intersection <= height) {
                    t_min = t1;
                }
            }
            if (t2 > 0) {
                Vec3 p2 = r.at(t2);
                Vec3 intersection_to_apex = top_vertex - p2;
                double height_at_intersection = intersection_to_apex.dot(axis_direction_normalized);
                if (height_at_intersection >= 0 && height_at_intersection <= height) {
                    t_min = std::min(t_min, t2);
                }
            }
        }
    
        // Check intersection with the base circle
        if (capped) {
            double denominator = r.dr.dot(axis_direction_normalized);
            if (std::fabs(denominator) > 1e-8) {
                double t_base = (base_center - r.origin).dot(axis_direction_normalized) / denominator;
                if (t_base > 0) {
                    Vec3 base_intersection = r.at(t_base);
                    if ((base_intersection - base_center).magnitude() <= radius) {
                        t_min = std::min(t_min, t_base);
                    }
                }
            }
        }
    
        return t_min == INFINITY ? -INFINITY : t_min;
    }
    

private:
    double cos_angle;
    double cos_angle_sq;

    void update_constants() {
        Vec3 axis = base_center - top_vertex; // Define axis como top_vertex - base_center
        height = axis.magnitude();            // Calcula altura como distância entre base e vertex
        axis_direction = axis.normalized();    // Direção do axis(vetor unitário)
        cos_angle = height / std::sqrt(height * height + radius * radius); // Calcula o angulo
        cos_angle_sq = cos_angle * cos_angle; // Deixa calculado o cos^2 do angulo
    }
};

#endif