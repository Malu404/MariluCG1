#ifndef LIGHT_H
#define LIGHT_H
#define M_PI 3.14159265358979323846
#include "../utils/vec3.h"
#include "SDL_stdinc.h"
#include <cmath>

enum TipoLuz {
    Pontual,
    Spot,
    Direcional
};

class Light {
    public:

        Vec3 pos;
        Vec3 color;
        Vec3 direction;   // Nova: direção do spot
        double angle;      // Novo: ângulo de abertura em radianos
        float intensity;
        TipoLuz tipo;
        
        Light () : pos(Vec3()), color(Vec3(1.0, 1.0, 1.0)), 
                 direction(Vec3(0, -1, 0)), angle(M_PI/4), intensity(1.0), tipo(Pontual) {}

        // Construtor para luz pontual
        static Light luz_pontual(Vec3 pos, Vec3 color, float intensity) {
            Light luz = Light();

            luz.pos = pos;
            luz.color = color;
            luz.direction = Vec3(0, -1, 0),
            luz.angle = M_PI; 
            luz.intensity = intensity;
            luz.tipo = Pontual;

            return luz;
        }

        static Light luz_spot(Vec3 pos, Vec3 dr, double angle, Vec3 color, float intensity) {
            Light luz = Light();
            luz.pos = pos;
            luz.color = color;
            luz.direction = dr.normalized();
            luz.angle = angle; 
            luz.intensity = intensity;
            luz.tipo = Spot;
            return luz;
        }

        static Light luz_direcional(Vec3 dr, Vec3 color, float intensity) {
            Light luz = Light();
            luz.pos = Vec3(0,0,0);
            luz.color = color;
            luz.direction = dr.normalized(),
            luz.angle = 0; 
            luz.intensity = intensity;
            luz.tipo = Direcional;
            return luz;
        }

        // // Calcula o fator de atenuação do spot
        // float spot_factor(const Vec3& point) const {
        //     if(angle >= M_PI) return 1.0f; // Luz pontual
            
        //     Vec3 light_vec = (point - pos).normalized();
        //     float cos_theta = direction.dot(light_vec);
        //     float cos_phi = cos(angle/2.0);
            
        //     if(cos_theta < cos_phi) return 0.0f;
            
        //     // Atenuação suave
        //     return cos_theta;
        // }
};

#endif