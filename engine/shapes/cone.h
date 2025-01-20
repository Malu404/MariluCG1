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

    Cone() : base_center(Vec3(0.0, 0.0, 0.0)), top_vertex(Vec3(0.0, 1.0, 0.0)), radius(1.0), height(1.0), capped(true), Shape() {
        update_constants();
    }

    Cone(Vec3 base_center, Vec3 top_vertex, double radius, Material mat, bool capped = true)
        : base_center(base_center), top_vertex(top_vertex), radius(std::fmax(0, radius)), capped(capped), Shape(mat) {
        update_constants();
    }

    inline Vec3 get_normal(Vec3 p) override {
        Vec3 v = p - top_vertex;
        double m = sqrt(v.dot(v) - pow(v.dot(axis_direction), 2));
        return (v - axis_direction * m * (radius / height)).normalize();
    }

    double intersects(Ray r) override {
        Vec3 ray_origin = r.origin;
        Vec3 ray_direction = r.dr;
        Vec3 cone_to_origin = ray_origin - top_vertex; // Vector from cone apex to ray origin

        // Precompute reusable dot products
        double axis_dot_direction = ray_direction.dot(axis_direction);
        double axis_dot_cone_to_origin = cone_to_origin.dot(axis_direction);
        double direction_dot_cone_to_origin = ray_direction.dot(cone_to_origin);
        double cone_to_origin_dot_cone_to_origin = cone_to_origin.dot(cone_to_origin);

        // Calculate quadratic coefficients
        double a = axis_dot_direction * axis_dot_direction - cos_angle_sq;
        double b = 2.0 * (axis_dot_direction * axis_dot_cone_to_origin - direction_dot_cone_to_origin * cos_angle_sq);
        double c = axis_dot_cone_to_origin * axis_dot_cone_to_origin - cone_to_origin_dot_cone_to_origin * cos_angle_sq;

        // Compute the discriminant
        double discriminant = b * b - 4.0 * a * c;
        if (discriminant < 0.0) return -INFINITY; // No real solutions, no intersection

        double sqrt_discriminant = std::sqrt(discriminant);
        double t1 = (-b - sqrt_discriminant) / (2.0 * a);
        double t2 = (-b + sqrt_discriminant) / (2.0 * a);

        // Helper function to check if t value hits the cone
        auto is_valid_cone_hit = [&](double t) {
            if (t <= 0.0) return false;
            Vec3 intersection_to_apex = (ray_origin + t * ray_direction) - top_vertex;
            double height_at_t = intersection_to_apex.dot(axis_direction);
            return height_at_t >= 0.0 && height_at_t <= height;
        };

        bool hit_detected = false;
        double t = 0.0;
        Vec3 surface_normal;

        // Check intersections with the cone surface
        if (is_valid_cone_hit(t1)) {
            hit_detected = true;
            t = t1;
            Vec3 intersection_to_apex = (ray_origin + t * ray_direction) - top_vertex;
            double height_at_intersection = intersection_to_apex.dot(axis_direction);
            surface_normal = (intersection_to_apex - axis_direction * height_at_intersection).normalize();
        }
        if (is_valid_cone_hit(t2) && (!hit_detected || t2 < t)) {
            hit_detected = true;
            t = t2;
            Vec3 intersection_to_apex = (ray_origin + t * ray_direction) - top_vertex;
            double height_at_intersection = intersection_to_apex.dot(axis_direction);
            surface_normal = (intersection_to_apex - axis_direction * height_at_intersection).normalize();
        }

        // Check intersection with the base if necessary
        if (capped && (!hit_detected || t <= 0.0)) {
            double denominator = ray_direction.dot(axis_direction);
            if (std::fabs(denominator) > 1e-8) {
                double t_base = (base_center - ray_origin).dot(axis_direction) / denominator;
                if (t_base > 0.0) {
                    Vec3 base_intersection = r.at(t_base);
                    if ((base_intersection - base_center).magnitude() <= radius) {
                        t = t_base;
                        surface_normal = -axis_direction;
                        hit_detected = true;
                    }
                }
            }
        }

        if (!hit_detected) return -INFINITY;

        return t;
    }

private:
    double cos_angle;
    double cos_angle_sq;

    void update_constants() {
        Vec3 axis = base_center - top_vertex; // Define the axis as top_vertex - base_center
        height = axis.magnitude();            // Calculate the height as the distance between base and vertex
        axis_direction = axis.normalize();    // Direction of the axis (unit vector)
        cos_angle = height / std::sqrt(height * height + radius * radius); // Calculate the angle
        cos_angle_sq = cos_angle * cos_angle; // Precompute the cosine squared
    }
};

#endif