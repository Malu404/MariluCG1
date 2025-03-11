#ifndef LIGHT_H
#define LIGHT_H

#include "../utils/vec3.h"

class Light {
    public:
        Vec3 pos;
        Vec3 color;
        Light (): pos(Vec3()), color(Vec3(1.0, 1.0, 1.0)) {}
        Light (Vec3 pos, Vec3 color, float intensity): pos(pos), color(color * intensity) {}
};

#endif

// #ifndef LIGHT_H
// #define LIGHT_H

// #include "../utils/vec3.h"

// class Light {
// public:
//     enum class Type {
//         Point,
//         Spotlight,
//         Directional
//     };

//     Vec3 pos;       // Posição da luz (usada para Point e Spotlight)
//     Vec3 color;     // Cor da luz
//     Vec3 direction; // Direção da luz (usada para Spotlight e Directional)
//     double angle;   // Ângulo de abertura (usado para Spotlight)
//     Type type;      // Tipo de luz

//     // Construtor padrão
//     Light() : pos(Vec3()), color(Vec3(1.0, 1.0, 1.0)), direction(Vec3()), angle(0.0), type(Type::Point) {}

//     // Construtor para luz pontual
//     Light(Vec3 pos, Vec3 color, float intensity) 
//         : pos(pos), color(color * intensity), direction(Vec3()), angle(0.0), type(Type::Point) {}

//     // Construtor para spotlight
//     Light(Vec3 pos, Vec3 direction, double angle, Vec3 color, float intensity)
//         : pos(pos), color(color * intensity), direction(-direction), angle(angle), type(Type::Spotlight) {}

//     // Construtor para luz direcional
//     Light(Vec3 direction, Vec3 color, float intensity, Type type = Type::Directional)
//         : pos(Vec3()), color(color * intensity), direction(-direction), angle(0.0), type(type) {}
// };

// // Função para criar uma spotlight
// inline Light spotlight(const Vec3& pos, const Vec3& direction, double angle, const Vec3& color, float intensity) {
//     return Light(pos, direction, angle, color, intensity);
// }

// // Função para criar uma luz direcional
// inline Light directional(const Vec3& direction, const Vec3& color, float intensity) {
//     return Light(direction, color, intensity, Light::Type::Directional);
// }

// #endif // LIGHT_H


