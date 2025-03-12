#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <stdexcept>
using namespace std;

inline double clip(double n, double lower, double upper) {
  return std::max(lower, std::min(n, upper));
}

struct Vec3 {
    double x, y, z;
    Vec3 ():  x(0), y(0), z(0) {};
    Vec3 (double x, double y, double z): x(x), y(y), z(z) {};
    
    inline Vec3 operator+(const Vec3& other)const { return Vec3(x+other.x, y+other.y, z+other.z); }

    inline Vec3 operator-(const Vec3& other) const{ return Vec3(x-other.x, y-other.y, z-other.z); }
//coloquei um const apos o (Vec3) para nao dar erro de compilacao 4/3/25 - 18:57
    inline Vec3 operator-() const { return Vec3(-x, -y, -z); }

    inline Vec3 operator*(const double other) const { return Vec3(x*other, y*other, z*other); }//produto escalar por vetor

    inline friend Vec3 operator*(double scalar, const Vec3& other) { return Vec3(other.x*scalar, other.y*scalar, other.z*scalar); }

    inline Vec3 operator*(const Vec3& other) const { return Vec3(x*other.x, y*other.y, z*other.z); }

    inline Vec3 operator/(const double other) const { return Vec3(x/other, y/other, z/other); }//divisao por um numero

    inline friend Vec3 operator/(double scalar, const Vec3& other) { return Vec3(other.x/scalar, other.y/scalar, other.z/scalar); }

    inline Vec3 operator/(const Vec3& other) const { return Vec3(x/other.x, y/other.y, z/other.z); }

    inline bool operator==(const Vec3& other) const { return (x == other.x) && (y == other.y) && (z == other.z); }

    inline double dot(const Vec3& other) const { return x*other.x + y*other.y + z*other.z; }

    inline double magnitude() const { return sqrt(x*x + y*y + z*z); }

    inline Vec3 normalized() const { return *this / magnitude(); }

    inline Vec3 rgb_normalized() const { return Vec3(x/255.0, y/255.0, z/255.0); }

    inline Vec3 rgb_255() const { return Vec3(x*255.0, y*255.0, z*255.0); }
    

    inline Vec3 clamp(double min, double max) { return Vec3(clip(x, min, max), clip(y, min, max), clip(z, min, max)); }
    
    inline Vec3 cross(const Vec3& other) const {
      return Vec3(
          y * other.z - z * other.y,
          z * other.x - x * other.z,
          x * other.y - y * other.x
      );
  }
  };

#endif