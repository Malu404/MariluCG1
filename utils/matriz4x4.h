#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <cmath>
#include <iostream>
#include <iomanip> 

#include "vec4.h"

class Matrix4x4 {
    public:

        double m[4][4];

        //conztrutor matriz identidade
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
                
                ); }
};
#endif