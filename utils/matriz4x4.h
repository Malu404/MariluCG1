#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <cmath>
#include <iostream>
#include <iomanip> 

#include "vec4.h"

class Matrix4x4 {
    public:

        double m[4][4];

        //construtor matriz identidade
        Matrix4x4() { set_I();}

        //matrix identidade
        void set_I() {
            m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
            m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
            m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
            m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
        }

        //construtor da matriz4x4
        Matrix4x4(
            double m00, double m01, double m02, double m03,
            double m10, double m11, double m12, double m13,
            double m20, double m21, double m22, double m23,
            double m30, double m31, double m32, double m33
        ) {
            m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
            m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
            m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
            m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
        }

        //matriz + matriz
        Matrix4x4 operator+(const Matrix4x4& other)
            const { return Matrix4x4(
                m[0][0] + other.m[0][0], m[0][1] + other.m[0][1], m[0][2] + other.m[0][2], m[0][3] + other.m[0][3],
                m[1][0] + other.m[1][0], m[1][1] + other.m[1][1], m[1][2] + other.m[1][1], m[1][3] + other.m[1][3], 
                m[2][0] + other.m[2][0], m[2][1] + other.m[2][1], m[2][2] + other.m[2][2], m[2][3] + other.m[2][3], 
                m[3][0] + other.m[3][0], m[3][1] + other.m[3][1], m[3][2] + other.m[3][2], m[3][3] + other.m[3][3]); }
        
        //matriz - matriz
        Matrix4x4 operator-(const Matrix4x4& other)
                const { return Matrix4x4(
                m[0][0] - other.m[0][0], m[0][1] - other.m[0][1], m[0][2] - other.m[0][2], m[0][3] - other.m[0][3],
                m[1][0] - other.m[1][0], m[1][1] - other.m[1][1], m[1][2] - other.m[1][1], m[1][3] - other.m[1][3], 
                m[2][0] - other.m[2][0], m[2][1] - other.m[2][1], m[2][2] - other.m[2][2], m[2][3] - other.m[2][3], 
                m[3][0] - other.m[3][0], m[3][1] - other.m[3][1], m[3][2] - other.m[3][2], m[3][3] - other.m[3][3]
                ); }

        
        //matriz * matriz
        Matrix4x4 operator*(const Matrix4x4& other)
                const { return Matrix4x4(
                    m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0] + m[0][3] * other.m[3][0],
                    m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1] + m[0][3] * other.m[3][1],
                    m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2] + m[0][3] * other.m[3][2],
                    m[0][0] * other.m[0][3] + m[0][1] * other.m[1][3] + m[0][2] * other.m[2][3] + m[0][3] * other.m[3][3],
                
                
                    m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0] + m[1][3] * other.m[3][0],
                    m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1] + m[1][3] * other.m[3][1],
                    m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2] + m[1][3] * other.m[3][2],
                    m[1][0] * other.m[0][3] + m[1][1] * other.m[1][3] + m[1][2] * other.m[2][3] + m[1][3] * other.m[3][3],
                
                
                    m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0] + m[2][3] * other.m[3][0],
                    m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1] + m[2][3] * other.m[3][1],
                    m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2] + m[2][3] * other.m[3][2],
                    m[2][0] * other.m[0][3] + m[2][1] * other.m[1][3] + m[2][2] * other.m[2][3] + m[2][3] * other.m[3][3],
                
                
                    m[3][0] * other.m[0][0] + m[3][1] * other.m[1][0] + m[3][2] * other.m[2][0] + m[3][3] * other.m[3][0],
                    m[3][0] * other.m[0][1] + m[3][1] * other.m[1][1] + m[3][2] * other.m[2][1] + m[3][3] * other.m[3][1],
                    m[3][0] * other.m[0][2] + m[3][1] * other.m[1][2] + m[3][2] * other.m[2][2] + m[3][3] * other.m[3][2],
                    m[3][0] * other.m[0][3] + m[3][1] * other.m[1][3] + m[3][2] * other.m[2][3] + m[3][3] * other.m[3][3]
                ); }


                //mutiplicaação vetor4 matrix
        Vec4 operator*(const Vec4& v) const {
                    return Vec4(
                        m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
                        m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
                        m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
                        m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
                    );
                }

                //multiplicação matrix por escalar
        Matrix4x4 operator*(const double other) const { return Matrix4x4( 
                    m[0][0] * other, m[0][1] * other, m[0][2] * other, m[0][3] * other,
                    m[1][0] * other, m[1][1] * other, m[1][2] * other, m[1][3] * other,
                    m[2][0] * other, m[2][1] * other, m[2][2] * other, m[2][3] * other,
                    m[3][0] * other, m[3][1] * other, m[3][2] * other, m[3][3] * other); }


                //divisão matrix por escalar
        Matrix4x4 operator/(const double other) const {
                    return Matrix4x4(
                    m[0][0] / other, m[0][1] / other, m[0][2] / other, m[0][3] / other,
                    m[1][0] / other, m[1][1] / other, m[1][2] / other, m[1][3] / other,
                    m[2][0] / other, m[2][1] / other, m[2][2] / other, m[2][3] / other,
                    m[3][0] / other, m[3][1] / other, m[3][2] / other, m[3][3] / other
                    );
                }

        Matrix4x4 operator-() const { return 
                    Matrix4x4( -m[0][0],  -m[0][1],  -m[0][2],  -m[0][3], 
                    -m[1][0],  -m[1][1],  -m[1][2],  -m[1][3],
                    -m[2][0],  -m[2][1],  -m[2][2],  -m[2][3], 
                    -m[3][0],  -m[3][1],  -m[3][2],  -m[3][3]);
                }
        Matrix4x4 translation(const double tx, double ty, double tz) {
            return Matrix4x4(
                m[0][0] = 1, m[0][1] = 0, m[0][2] = 0, m[0][3] = tx,
                m[1][0] = 0, m[1][1] = 1, m[1][2] = 0, m[1][3] = ty,
                m[2][0] = 0, m[2][1] = 0, m[2][2] = 1, m[2][3] = tz,
                m[3][0] = 0, m[3][1] = 0, m[3][2] = 0, m[3][3] = 1
                );
        }

        Matrix4x4 scale_matrix(const double sx, double sy, double sz){
            return Matrix4x4(
                m[0][0] = sx, m[0][1] = 0, m[0][2] = 0, m[0][3] = 0,
                m[1][0] = 0, m[1][1] = sy, m[1][2] = 0, m[1][3] = 0,
                m[2][0] = 0, m[2][1] = 0, m[2][2] = sz, m[2][3] = 0,
                m[3][0] = 0, m[3][1] = 0, m[3][2] = 0, m[3][3] = 1
            );
        }


        Matrix4x4 shear_x(const double s_yz, double s_zy){
            return Matrix4x4(
                m[0][0] = 1, m[0][1] = s_yz, m[0][2] = s_zy, m[0][3] = 0,
                m[1][0] = 0, m[1][1] = 1, m[1][2] = 0, m[1][3] = 0,
                m[2][0] = 0, m[2][1] = 0, m[2][2] = 1, m[2][3] = 0,
                m[3][0] = 0, m[3][1] = 0, m[3][2] = 0, m[3][3] = 1
            );
        }



        Matrix4x4 shear_y(const double s_xz, double s_zx) {
            return Matrix4x4(
                m[0][0] = 1, m[0][1] = 0, m[0][2] = 0, m[0][3] = 0,
                m[1][0] = s_xz, m[1][1] = 1, m[1][2] = s_zx, m[1][3] = 0,
                m[2][0] = 0, m[2][1] = 0, m[2][2] = 1, m[2][3] = 0,
                m[3][0] = 0, m[3][1] = 0, m[3][2] = 0, m[3][3] = 1
            );
        }

        Matrix4x4 shear_z(const double s_xy, double s_yx){
            return  Matrix4x4(
                m[0][0] = 1, m[0][1] = 0, m[0][2] = 0, m[0][3] = 0,
                m[1][0] = 0, m[1][1] = 1, m[1][2] = 0, m[1][3] = 0,
                m[2][0] = s_xy, m[2][1] = s_yx, m[2][2] = 1, m[2][3] = 0,
                m[3][0] = 0, m[3][1] = 0, m[3][2] = 0, m[3][3] = 1
            );
        }

        Matrix4x4 shear_x_angle(const double angle){
            double s_yz = std::tan(angle);
            return Matrix4x4(
                m[0][0] = 1, m[0][1] = s_yz, m[0][2] = 0, m[0][3] = 0,
                m[1][0] = 0, m[1][1] = 1, m[1][2] = 0, m[1][3] = 0,
                m[2][0] = 0, m[2][1] = 0, m[2][2] = 1, m[2][3] = 0,
                m[3][0] = 0, m[3][1] = 0, m[3][2] = 0, m[3][3] = 1
            );
        }

        Matrix4x4 shear_y_angle(const double angle){
            double s_xz = std::tan(angle);
            return Matrix4x4(
                m[0][0] = 1, m[0][1] = 0, m[0][2] = 0, m[0][3] = 0,
                m[1][0] = s_xz, m[1][1] = 1, m[1][2] = 0, m[1][3] = 0,
                m[2][0] = 0, m[2][1] = 0, m[2][2] = 1, m[2][3] = 0,
                m[3][0] = 0, m[3][1] = 0, m[3][2] = 0, m[3][3] = 1
            );
        }


        Matrix4x4 shear_z_angle(const double angle){
            double s_xy = std::tan(angle);
            return Matrix4x4(
                m[0][0] = 1, m[0][1] = 0, m[0][2] = 0, m[0][3] = 0,
                m[1][0] = 0, m[1][1] = 1, m[1][2] = 0, m[1][3] = 0,
                m[2][0] = s_xy, m[2][1] = 0, m[2][2] = 1, m[2][3] = 0,
                m[3][0] = 0, m[3][1] = 0, m[3][2] = 0, m[3][3] = 1
            );
        }
        
};
#endif