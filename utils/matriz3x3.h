#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <cmath>
#include <iostream>
#include <iomanip> 

#include "matriz4x4.h"
#include "vec3.h"
class Matrix3x3{
        public:

        double m[3][3];


        

        //matrix identidade
        static Matrix3x3 I() {
            return Matrix3x3(
                1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0
            );
        }

        Matrix3x3() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    m[i][j] = 0.0;
                }
            }
        }

            // Construtor de cópia
        Matrix3x3(const Matrix3x3& other) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = other.m[i][j];
            }
        }
        }

        // Operador de atribuição
        Matrix3x3& operator=(const Matrix3x3& other) {
        if (this != &other) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    m[i][j] = other.m[i][j];
                }
            }
        }
        return *this;
        }

        Matrix3x3 transpose() const {
            Matrix3x3 result;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    result.m[i][j] = m[j][i];
                }
            }
            return result;
        }

        double determinant() const {
            return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
                 - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
                 + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
        }

        Matrix3x3(
            double m00, double m01, double m02, 
            double m10, double m11, double m12, 
            double m20, double m21, double m22
        ) {
            m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
            m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; 
            m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
        }

            Matrix3x3 operator+(const Matrix3x3& other)
            const { return Matrix3x3(
                m[0][0] + other.m[0][0], m[0][1] + other.m[0][1], m[0][2] + other.m[0][2],
                m[1][0] + other.m[1][0], m[1][1] + other.m[1][1], m[1][2] + other.m[1][2], 
                m[2][0] + other.m[2][0], m[2][1] + other.m[2][1], m[2][2] + other.m[2][2] 
                ); }


                Matrix3x3 operator-(const Matrix3x3& other)
                const { return Matrix3x3(
                m[0][0] - other.m[0][0], m[0][1] - other.m[0][1], m[0][2] - other.m[0][2], 
                m[1][0] - other.m[1][0], m[1][1] - other.m[1][1], m[1][2] - other.m[1][2],
                m[2][0] - other.m[2][0], m[2][1] - other.m[2][1], m[2][2] - other.m[2][2]
                ); }

                Matrix3x3 operator*(const Matrix3x3& other) const {
                    Matrix3x3 result;
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            result.m[i][j] = 0;
                            for (int k = 0; k < 3; k++) {
                                result.m[i][j] += m[i][k] * other.m[k][j];
                            }
                        }
                    }
                    return result;
                }

                Vec3 operator*(const Vec3& other) const {
                    Vec3 result;
                    result.x = other.x * m[0][0] + other.y * m[0][1] + other.z * m[0][2];
                    result.y = other.x * m[1][0] + other.y * m[1][1] + other.z * m[1][2];
                    result.z = other.x * m[2][0] + other.y * m[2][1] + other.z * m[2][2];
                    return result;
                }
                

                Matrix3x3 operator*(double n) const {
                    Matrix3x3 result;
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            result.m[i][j] = m[i][j] * n;
                        }
                    }
                    return result;
                }


                Matrix3x3 operator/(double n) const {
                    Matrix3x3 result;
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            result.m[i][j] = m[i][j] / n;
                        }
                    }
                    return result;
                }



                Matrix3x3 operator-() const {
                    Matrix3x3 result;
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            result.m[i][j] = -m[i][j];
                        }
                    }
                    return result;
                }

        
};



#endif