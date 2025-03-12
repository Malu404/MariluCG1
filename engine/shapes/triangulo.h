#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "shape.h"
#include "../../utils/vec3.h"

class Triangle : public Shape {
public:
    Vec3 v0, v1, v2;
    Vec3 normal;

    Triangle( Vec3 v0, Vec3 v1, Vec3 v2, Material mat) : Shape(mat), v0(v0), v1(v1), v2(v2) {
        normal = (v1 - v0).cross(v2 - v0).normalized();
        //normal = (v2 - v0).cross(v1 - v0).normalized();
    }

    inline Vec3 get_normal(Vec3 _) const override {
        return normal;
    }

    void transform(Matriz4x4 m) override {
        v0 = m*v0;
        v1 = m*v1;
        v2 = m*v2;
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
                    Vec3 v0p = p - v0;
                
                    // Calcula as coordenadas baricêntricas
                    double d00 = edge1.dot(edge1);
                    double d01 = edge1.dot(edge2);
                    double d11 = edge2.dot(edge2);
                    double d20 = v0p.dot(edge1);
                    double d21 = v0p.dot(edge2);
                    double denom = d00 * d11 - d01 * d01;
                
                    // Evita divisão por zero (triângulo degenerado)
                    if (std::abs(denom) < 1e-8) return false;
                
                    // Calcula u e v
                    double v = (d11 * d20 - d01 * d21) / denom;
                    double w = (d00 * d21 - d01 * d20) / denom;
                    double u = 1.0 - v - w;
                
                    // Verifica se o ponto está dentro do triângulo
                    return (u >= -1e-8 && v >= -1e-8 && w >= -1e-8);
                
                
    }
};

#endif