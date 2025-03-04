#ifndef SHAPE_H
#define SHAPE_H

#include <tuple>
#include "material.h"
#include "../ray.h"

class Shape {
    public:
        Material mat;
        Shape () : mat(Material()) {}
        Shape (Material mat) : mat(mat) {}
        
        // Retorna a normal de um objeto em um ponto P
        virtual Vec3 get_normal(Vec3 p) const = 0;

        // Retorna o menor T positivo da colisão do objeto com o raio, 
        // T negativo se não há colisão positiva (objeto atrás do p0 do raio),
        // -INFINITO se não há colisão.
        virtual double intersects(Ray r) const  = 0;
        //adicionei const = 0 para nao dar erro de compilacao 4/3/25 - 19:27 e pq sao operacoes que nao alteram valores do shape original
};

#endif