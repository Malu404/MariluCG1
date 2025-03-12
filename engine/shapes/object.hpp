#pragma once
#include "material.h"
#include "../ray.h"
#include "../../utils/matriz4x4.h"

struct Intersection;

class Object {
    public:
        Material mat;
        Object () : mat(Material()) {}
        Object (Material mat) : mat(mat) {}
        
        // Retorna o menor T positivo + informações da colisão do objeto com o raio (INFINITO se não há colisão)
        virtual const Intersection get_intersection(Ray r) = 0;
        virtual ~Object() {} // Declare the destructor as virtual
        virtual void translate(Vec3 translation_vector) = 0;
        virtual void transform(Matriz4x4 m) = 0;
};