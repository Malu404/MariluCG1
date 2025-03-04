#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "shape.h"
#include "../../utils/vec3.h"

class Triangle : public Shape {
public:
    Vec3 v0, v1, v2;
    Vec3 normal;

    Triangle( Vec3 v0, Vec3 v1, Vec3 v2, Material mat) : Shape(mat), v0(v0), v1(v1), v2(v2) {
        normal = (v1 - v0).cross(v2 - v0).normalize();
    }

    inline Vec3 get_normal( Vec3 p) const override {
        return normal;
    }

    double intersects(Ray r) const override {
        // Implementação do algoritmo de interseção de triângulo
        Vec3 edge1 = v1 - v0;
        Vec3 edge2 = v2 - v0;
        Vec3 h = r.dr.cross(edge1);
        double a = edge2.dot(h);
        if (a > -1e-8 && a < 1e-8) return -INFINITY; // O raio é paralelo ao triângulo

        double f = 1.0 / a;
        Vec3 s = r.origin - v0;
        double u = f * s.dot(h);
        if (u < 0.0 || u > 1.0) return -INFINITY;

        Vec3 q = s.cross(edge2);
        double v = f * r.dr.dot(q);
        if (v < 0.0 || u + v > 1.0) return -INFINITY;

        double t = f * edge1.dot(q);
        return t > 1e-8 ? t : -INFINITY; // Retorna t se a interseção é válida
    }

    bool contains(Vec3 p) const {//tirei o const daqui de dentro do Vec3, nao sei se vai explodir o codigo 4/3/25 - 18:33
        // Verifica se o ponto p está dentro do triângulo
        Vec3 edge1 = v1 - v0;
        Vec3 edge2 = v2 - v0;
        Vec3 edge3 = v2 - v1;
        Vec3 c0 = p - v0;
        Vec3 c1 = p - v1;
        Vec3 c2 = p - v2;
        return (edge1.cross(c0).dot(normal) >= 0 &&
                edge2.cross(c1).dot(normal) >= 0 &&
                edge3.cross(c2).dot(normal) >= 0);
    }
};

#endif