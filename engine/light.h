#ifndef LIGHT_H
#define LIGHT_H
#define M_PI 3.14159265358979323846
#include "../utils/vec3.h"
#include "SDL_stdinc.h"
#include <cmath>

class Light {
    public:
        Vec3 pos;
        Vec3 color;
        Vec3 direction;   // Nova: direção do spot
        double angle;      // Novo: ângulo de abertura em radianos
        double exponent;   // Novo: expoente de atenuação
        float intensity;
        
        Light () : pos(Vec3()), color(Vec3(1.0, 1.0, 1.0)), 
                 direction(Vec3(0, -1, 0)), angle(M_PI/4), exponent(1.0), intensity(1.0) {}

        // Construtor para luz direcional padrão
        Light (Vec3 pos, Vec3 color, float intensity) : 
            pos(pos), color(color), direction(Vec3(0, -1, 0)),
            angle(M_PI), exponent(0.0), intensity(intensity) {}

        // Construtor completo para luz spot
        Light (Vec3 pos, Vec3 direction, Vec3 color, 
              float intensity, double angle_degrees, double exponent) : 
            pos(pos), color(color), direction(direction.normalize()),
            intensity(intensity), exponent(exponent) 
        {
            angle = (angle_degrees * M_PI) / 180.0; // Converte para radianos
        }

        // Calcula o fator de atenuação do spot
        float spot_factor(const Vec3& point) const {
            if(angle >= M_PI) return 1.0f; // Luz direcional
            
            Vec3 light_vec = (point - pos).normalize();
            float cos_theta = direction.dot(light_vec);
            float cos_phi = cos(angle/2.0);
            
            if(cos_theta < cos_phi) return 0.0f;
            
            // Atenuação suave
            return powf(cos_theta, exponent);
        }
};

#endif