#pragma once
#include "../utils/vec3.h"
#include "shapes/object.hpp"
#include <cmath>
#include "shapes/shape.h"

struct Intersection {
    double t;
    Vec3 p;
    Vec3 normal;
    Vec3 color;
    Object* shape;

    // Construtor padrão
    Intersection() : t(INFINITY), p(Vec3(0, 0, 0)), normal(Vec3(0, 0, 0)), color(Vec3(0, 0, 0)), shape(nullptr) {}

    // Construtor com parâmetros
    Intersection(double t, Vec3 p, Vec3 normal, Vec3 color, Object* shape)
        : t(t), p(p), normal(normal), color(color), shape(shape) {}

    // Construtor que aceita um std::tuple<bool, Shape*, Vec3>
    Intersection(const std::tuple<bool, Object*, Vec3>& t) {
        if (std::get<0>(t)) { // Se houve interseção (bool é true)
            this->t = 0; // Defina um valor adequado para 't'
            this->p = std::get<2>(t); // Use o Vec3 do tuple como ponto de interseção
            this->normal = Vec3(0, 0, 0); // Calcule a normal adequada
            this->color = Vec3(0, 0, 0); // Defina uma cor padrão ou calcule
    
            // Converte Object* para Shape* usando dynamic_cast
            this->shape = dynamic_cast<Shape*>(std::get<1>(t));
            if (!this->shape) {
                // Se a conversão falhar, defina shape como nullptr
                this->shape = nullptr;
            }
        } else {
            // Se não houve interseção, use o construtor padrão
            *this = Intersection();
        }
    }
    
};
