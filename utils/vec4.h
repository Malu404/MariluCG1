#ifndef VEC4_H
#define VEC4_H

#include <algorithm>
#include <cmath>
#include <stdexcept>

// #include "matriz4x4.h"



#include "vec3.h"

using namespace std;

class Vec4{
    public:
    double x, y, z, w;

    //construtores
    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(const Vec4 &) = default;
    Vec4(Vec4 &&) = default;
    Vec4 &operator=(const Vec4 &) = default;
    Vec4 &operator=(Vec4 &&) = default;
    Vec4(double x, double y, double z, double w = 1.0)
        : x(x), y(y), z(z), w(w) {}
    Vec3 to_vec3() const {
        if (w != 0) {
            return Vec3(x / w, y / w, z / w);
        }
        return Vec3(x, y, z);  // Direction vector
    }
    
    Vec4(const Vec3& v, double w = 1.0) : x(v.x), y(v.y), z(v.z), w(w) {}
    Vec4 operator=(Vec3& vetor){
        return Vec4(vetor.x, vetor.y, vetor.z, 1.0);
      }
    //adição
    Vec4 operator+(const Vec4& other) const { 
        return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    //subtração
    Vec4 operator-(const Vec4& other) const { 
        return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
    }
     Vec4 operator-() const { return Vec4(-x, -y, -z, -w); }

     Vec4 operator*(const double other) const { return Vec4(x*other, y*other, z*other, w*other); }//produto escalar por vetor

     friend Vec4 operator*(double scalar, const Vec4& other) { return Vec4(other.x*scalar, other.y*scalar, other.z*scalar, other.w*scalar); }

    Vec4 operator*(const Vec4& other) const { return Vec4(x*other.x, y*other.y, z*other.z, w*other.w); }

     Vec4 operator/(const double other) const { return Vec4(x/other, y/other, z/other, w/other); }//divisao por um numero

     friend Vec4 operator/(double scalar, const Vec4& other) { return Vec4(other.x/scalar, other.y/scalar, other.z/scalar, other.w/scalar); }

     Vec4 operator/(const Vec4& other) const { return Vec4(x/other.x, y/other.y, z/other.z, w/other.w); }

     bool operator==(const Vec4& other) const { return (x == other.x) && (y == other.y) && (z == other.z) && ( w == other.w); }

     double dot(const Vec4& other) const { return x*other.x + y*other.y + z*other.z + w*other.w; }
     
     double magnitude() const { return sqrt(x*x + y*y + z*z + w*w); }

     Vec4 normalize() const { return *this / magnitude(); }

     Vec4 rgb_normalized() const { return Vec4(x/255.0, y/255.0, z/255.0, w/255.0); }

     Vec4 rgb_255() const { return Vec4(x*255.0, y*255.0, z*255.0, w*255.0); }

     Vec4 min_(const Vec4& other) const {
        return Vec4(
            (x < other.x) ? x : other.x,
            (y < other.y) ? y : other.y,
            (z < other.z) ? z : other.z,
            (w < other.w) ? w : other.w
        );
    }

    // Função para calcular o máximo (elemento a elemento)
    Vec4 max_(const Vec4& other) const {
        return Vec4(
            (x > other.x) ? x : other.x,
            (y > other.y) ? y : other.y,
            (z > other.z) ? z : other.z,
            (w > other.w) ? w : other.w
        );
    }

    /// Retorna o vetor com cada elemento restrito entre um intervalo [min, max]
    double clamp(double value, double min, double max) {
        return (value < min) ? min : (value > max) ? max : value;
    }

    //meu vscode da erro 
    //  Vec4 min_(const Vec4& other) const {
    //     return vec4(std::min(x, other.x), std::min(y, other.y), std::min(z, other.z), std::min(w, other.w));
    // }

    // // Max Element-Wise
    // Vec4 max_(const Vec4& other) const {
    //     return vec4(std::max(x, other.x), std::max(y, other.y), std::max(z, other.z), std::max(w, other.w));
    // }

    //  Vec3 to_vec3() const {
    //     if (w != 0) {
    //         return Vec3(x / w, y / w, z / w);
    //     }
    //     return Vec3(x, y, z);  
    // }

    


};
#endif