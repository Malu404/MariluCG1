#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <cmath>
#include <iostream>
#include <iomanip> 

#include "vec3.h"
#include "vec4.h"
#define  M_PI  3.14159265358979323846264338327950288


class Matrix4x4 {
    public:

        double m[4][4];
        

        //construtor matriz identidade

        //conztrutor matriz identidade

        Matrix4x4() { I();}

        //matrix identidade
        static Matrix4x4 I() {
        Matrix4x4 identity(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        // Preenche a matriz identidade
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) {
                    identity.m[i][j] = 1.0;
                } else {
                    identity.m[i][j] = 0.0;
                }
            }
        }

        return identity;
    }
        // Matrix4x4 I() {
        // return Matrix4x4(
        //     for (int i = 0; i < 4; i++) {
        //              for (int j = 0; j < 4; j++) {
        //                  if (i == j) {
        //                      m[i][j] = 1.0;
        //                  } else {
        //                      m[i][j] = 0.0;
        //                  }
        //              }
        //          });
        // }

        
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
        
        // Vec3 operator*(const Vec3& v) const {
        //     Vec4 v4(v, 0.0);
        //     Vec4 result = (*this) * v4;
        //     return Vec3(result.x, result.y, result.z);
        // }

        Vec3 operator*(const Vec3& v) const {
            // Converte o Vec3 para Vec4 (coordenadas homogêneas)
            Vec4 v4(v.x, v.y, v.z, 1.0);
        
            // Multiplica a matriz pelo vetor
            Vec4 result = (*this) * v4;
        
            // Retorna o resultado como Vec3 (ignorando a coordenada w)
            return Vec3(result.x, result.y, result.z);
        }

        
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

                static Matrix4x4 translation(const double tx, double ty, double tz) {
                    return Matrix4x4(
                        1, 0, 0, tx,  // Linha 0
                        0, 1, 0, ty,  // Linha 1
                        0, 0, 1, tz,  // Linha 2
                        0, 0, 0, 1    // Linha 3
                    );
                }
            
            //    static Matrix4x4 scale_matrix(const double sx, double sy, double sz){
            //         Matrix4x4 matrix;
            //         return Matrix4x4(
            //             matrix.m[0][0] = sx, matrix.m[0][1] = 0, matrix.m[0][2] = 0, matrix.m[0][3] = 0,
            //             matrix.m[1][0] = 0, matrix.m[1][1] = sy, matrix.m[1][2] = 0, matrix.m[1][3] = 0,
            //             matrix.m[2][0] = 0, matrix.m[2][1] = 0, matrix.m[2][2] = sz, matrix.m[2][3] = 0,
            //             matrix.m[3][0] = 0, matrix.m[3][1] = 0, matrix.m[3][2] = 0, matrix.m[3][3] = 1
            //         );
            //     }


            static Matrix4x4 scale_matrix(const double sx, double sy, double sz) {
                return Matrix4x4(
                    sx, 0,  0,  0,  // Linha 0
                    0,  sy, 0,  0,  // Linha 1
                    0,  0,  sz, 0,  // Linha 2
                    0,  0,  0,  1   // Linha 3
                );
            }
            
            
            //   static  Matrix4x4 shear_x(const double s_yz, double s_zy){
            //         Matrix4x4 matrix;
            //         return Matrix4x4(
            //             matrix.m[0][0] = 1, matrix.m[0][1] = s_yz, matrix.m[0][2] = s_zy, matrix.m[0][3] = 0,
            //             matrix.m[1][0] = 0, matrix.m[1][1] = 1, matrix.m[1][2] = 0, matrix.m[1][3] = 0,
            //             matrix.m[2][0] = 0, matrix.m[2][1] = 0, matrix.m[2][2] = 1, matrix.m[2][3] = 0,
            //             matrix.m[3][0] = 0, matrix.m[3][1] = 0, matrix.m[3][2] = 0, matrix.m[3][3] = 1
            //         );
            //     }

            static Matrix4x4 shear_x(const double s_yz, double s_zy) {
                return Matrix4x4(
                    1,   s_yz, s_zy, 0,  // Linha 0
                    0,   1,    0,    0,  // Linha 1
                    0,   0,    1,    0,  // Linha 2
                    0,   0,    0,    1   // Linha 3
                );
            }
            
            
            
            //    static Matrix4x4 shear_y(const double s_xz, double s_zx) {
            //         Matrix4x4 matrix;
            //         return Matrix4x4(
            //             matrix.m[0][0] = 1, matrix.m[0][1] = 0, matrix.m[0][2] = 0, matrix.m[0][3] = 0,
            //             matrix.m[1][0] = s_xz, matrix.m[1][1] = 1, matrix.m[1][2] = s_zx, matrix.m[1][3] = 0,
            //             matrix.m[2][0] = 0, matrix.m[2][1] = 0, matrix.m[2][2] = 1, matrix.m[2][3] = 0,
            //             matrix.m[3][0] = 0, matrix.m[3][1] = 0, matrix.m[3][2] = 0, matrix.m[3][3] = 1
            //         );
            //     }

            static Matrix4x4 shear_y(const double s_xz, double s_zx) {
                return Matrix4x4(
                    1,   0,   0,   0,  // Linha 0
                    s_xz, 1,   s_zx, 0,  // Linha 1
                    0,   0,   1,   0,  // Linha 2
                    0,   0,   0,   1   // Linha 3
                );
            }
            
            //    static Matrix4x4 shear_z(const double s_xy, double s_yx){
            //         Matrix4x4 matrix;
            //         return  Matrix4x4(
            //             matrix.m[0][0] = 1, matrix.m[0][1] = 0, matrix.m[0][2] = 0, matrix.m[0][3] = 0,
            //             matrix.m[1][0] = 0, matrix.m[1][1] = 1, matrix.m[1][2] = 0, matrix.m[1][3] = 0,
            //             matrix.m[2][0] = s_xy, matrix.m[2][1] = s_yx, matrix.m[2][2] = 1, matrix.m[2][3] = 0,
            //             matrix.m[3][0] = 0, matrix.m[3][1] = 0, matrix.m[3][2] = 0, matrix.m[3][3] = 1
            //         );
            //     }

            static Matrix4x4 shear_z(const double s_xy, double s_yx) {
                return Matrix4x4(
                    1,   0,   0,   0,  // Linha 0
                    0,   1,   0,   0,  // Linha 1
                    s_xy, s_yx, 1,   0,  // Linha 2
                    0,   0,   0,   1   // Linha 3
                );
            }
            
            //  static   Matrix4x4 shear_x_angle(const double angle){
            //         double s_yz = std::tan(angle);
            //         Matrix4x4 matrix;
            //         return Matrix4x4(
            //             matrix.m[0][0] = 1, matrix.m[0][1] = s_yz, matrix.m[0][2] = 0, matrix.m[0][3] = 0,
            //             matrix.m[1][0] = 0, matrix.m[1][1] = 1, matrix.m[1][2] = 0, matrix.m[1][3] = 0,
            //             matrix.m[2][0] = 0, matrix.m[2][1] = 0, matrix.m[2][2] = 1, matrix.m[2][3] = 0,
            //             matrix.m[3][0] = 0, matrix.m[3][1] = 0, matrix.m[3][2] = 0, matrix.m[3][3] = 1
            //         );
            //     }


            static Matrix4x4 shear_x_angle(const double angle) {
                double s_yz = std::tan(angle);
                return Matrix4x4(
                    1,   s_yz, 0,   0,  // Linha 0
                    0,   1,    0,   0,  // Linha 1
                    0,   0,    1,   0,  // Linha 2
                    0,   0,    0,   1   // Linha 3
                );
            }
            
            //   static  Matrix4x4 shear_y_angle(const double angle){
            //         double angle_r = angle * M_PI / 180.0;
            //         double s_xz = std::tan(angle_r);
            //         Matrix4x4 matrix;
            //         return Matrix4x4(
            //             matrix.m[0][0] = 1, matrix.m[0][1] = 0, matrix.m[0][2] = 0, matrix.m[0][3] = 0,
            //             matrix.m[1][0] = s_xz, matrix.m[1][1] = 1, matrix.m[1][2] = 0, matrix.m[1][3] = 0,
            //             matrix.m[2][0] = 0, matrix.m[2][1] = 0, matrix.m[2][2] = 1, matrix.m[2][3] = 0,
            //             matrix.m[3][0] = 0, matrix.m[3][1] = 0, matrix.m[3][2] = 0, matrix.m[3][3] = 1
            //         );
            //     }


            static Matrix4x4 shear_y_angle(const double angle) {
                double angle_r = angle * M_PI / 180.0;
                double s_xz = std::tan(angle_r);
                return Matrix4x4(
                    1,   0,   0,   0,  // Linha 0
                    s_xz, 1,   0,   0,  // Linha 1
                    0,   0,   1,   0,  // Linha 2
                    0,   0,   0,   1   // Linha 3
                );
            }
            
            
            //   static  Matrix4x4 shear_z_angle(const double angle){
            //         double angle_r = angle * M_PI / 180.0;
            //         double s_xy = std::tan(angle_r);
            //         Matrix4x4 matrix;
            //         return Matrix4x4(
            //             matrix.m[0][0] = 1, matrix.m[0][1] = 0, matrix.m[0][2] = 0, matrix.m[0][3] = 0,
            //             matrix.m[1][0] = 0, matrix.m[1][1] = 1, matrix.m[1][2] = 0, matrix.m[1][3] = 0,
            //             matrix.m[2][0] = s_xy, matrix.m[2][1] = 0, matrix.m[2][2] = 1, matrix.m[2][3] = 0,
            //             matrix.m[3][0] = 0, matrix.m[3][1] = 0, matrix.m[3][2] = 0, matrix.m[3][3] = 1
            //         );
                    
            //     }
            
            static Matrix4x4 shear_z_angle(const double angle) {
                double angle_r = angle * M_PI / 180.0;
                double s_xy = std::tan(angle_r);
                return Matrix4x4(
                    1,   0,   0,   0,  // Linha 0
                    0,   1,   0,   0,  // Linha 1
                    s_xy, 0,   1,   0,  // Linha 2
                    0,   0,   0,   1   // Linha 3
                );
            }
                // //rotação em um eixo especifico
                // static Matrix4x4 ratotion(double angle, char eixo){
                //     double angle_r = angle * M_PI / 180.0;
                //     double cos = std::cos(angle_r);
                //     double sin = std::sin(angle_r);
            
                //     Matrix4x4 matrix;
                //     switch (eixo) {
                //         case 'x':
                //             matrix.m[1][1] = cos;
                //             matrix.m[1][2] = -sin;
                //             matrix.m[2][1] = sin;
                //             matrix.m[2][2] = cos;
                //             break;
                //         case 'y':
                //             matrix.m[0][0] = cos;
                //             matrix.m[0][2] = sin;
                //             matrix.m[2][0] = -sin;
                //             matrix.m[2][2] = cos;
                //             break;
                //         case 'z':
                //             matrix.m[0][0] = cos;
                //             matrix.m[0][1] = -sin;
                //             matrix.m[1][0] = sin;
                //             matrix.m[1][1] = cos;
                //             break;
                //         default:
                //             throw std::invalid_argument("invalido. use x, y, z.");
                    
                //     }
                //     return matrix;
                // }

                static Matrix4x4 rotation(double angle, char eixo) {
                    double angle_r = angle * M_PI / 180.0;
                    double cos = std::cos(angle_r);
                    double sin = std::sin(angle_r);
                
                    switch (eixo) {
                        case 'x':
                            return Matrix4x4(
                                1,   0,    0,   0,  // Linha 0
                                0,   cos, -sin, 0,  // Linha 1
                                0,   sin,  cos, 0,  // Linha 2
                                0,   0,    0,   1   // Linha 3
                            );
                        case 'y':
                            return Matrix4x4(
                                cos,  0,   sin, 0,  // Linha 0
                                0,    1,   0,   0,  // Linha 1
                                -sin, 0,   cos, 0,  // Linha 2
                                0,    0,   0,   1   // Linha 3
                            );
                        case 'z':
                            return Matrix4x4(
                                cos, -sin, 0,   0,  // Linha 0
                                sin,  cos, 0,   0,  // Linha 1
                                0,    0,   1,   0,  // Linha 2
                                0,    0,   0,   1   // Linha 3
                            );
                        default:
                            throw std::invalid_argument("Invalido. Use x, y, z.");
                    }
                }
            
            
            //   static  Matrix4x4 rotation_arbitrary_axis(const Vec3& eixo, double angle){
            //         Vec3 eixo_normal = eixo.normalize();
            //         double x = eixo_normal.x;
            //         double y = eixo_normal.y;
            //         double z = eixo_normal.z;
            
            //         double cos = std::cos(angle);
            //         double sin = std::sin(angle);
            //         double um_menos_cos = 1.0 - cos;
            //         Matrix4x4 matrix;
            
            //         return Matrix4x4(
            //             matrix.m[0][0] = cos + x*x*um_menos_cos, matrix.m[0][1] = x*y*um_menos_cos - z*sin, matrix.m[0][2] = x*z*um_menos_cos + y*sin, matrix.m[0][3] = 0,
            
            //             matrix.m[1][0] = y*x*um_menos_cos + z*sin, matrix.m[1][1] = cos + y*y/um_menos_cos, matrix.m[1][2] = y*z*um_menos_cos - x*sin, matrix.m[1][3] = 0,
            
            //             matrix.m[2][0] = z*x*um_menos_cos - y*sin, matrix.m[2][1] = z*y*um_menos_cos + x*sin, matrix.m[2][2] = cos + z*z*um_menos_cos, matrix.m[2][3] = 0,
            
            //             matrix.m[3][0] = 0, matrix.m[3][1] = 0, matrix.m[3][2] = 0, matrix.m[3][3] = 1
            //         );
            
            //     }


            static Matrix4x4 rotation_arbitrary_axis(const Vec3& eixo, double angle) {
                Vec3 eixo_normal = eixo.normalize();
                double x = eixo_normal.x;
                double y = eixo_normal.y;
                double z = eixo_normal.z;
            
                double cos = std::cos(angle);
                double sin = std::sin(angle);
                double um_menos_cos = 1.0 - cos;
            
                return Matrix4x4(
                    cos + x * x * um_menos_cos, x * y * um_menos_cos - z * sin, x * z * um_menos_cos + y * sin, 0,  // Linha 0
                    y * x * um_menos_cos + z * sin, cos + y * y * um_menos_cos, y * z * um_menos_cos - x * sin, 0,  // Linha 1
                    z * x * um_menos_cos - y * sin, z * y * um_menos_cos + x * sin, cos + z * z * um_menos_cos, 0,  // Linha 2
                    0, 0, 0, 1  // Linha 3
                );
            }
            
            //     //reflexão
            //   static  Matrix4x4 mirror(char plano) {
            //         Matrix4x4 matrix;
            
            //         switch (plano) {
            //         case 'x':
            //         case 'X':
            //             matrix.m[2][2] = -1; // espelho cortando o plano XY
            //             break;
            //         case 'y':
            //         case 'Y':
            //             matrix.m[0][0] = -1; // espelho cortando o plano YZ
            //             break;
            //         case 'z':
            //         case 'Z':
            //             matrix.m[1][1] = -1; // espelho cortando o plano XZ 
            //             break;
            //         default:
            //             throw std::invalid_argument("Invalido . Use x, y, z.");
            //         }
            
            //         return matrix;
            //     }


            static Matrix4x4 mirror(char plano) {
                switch (plano) {
                    case 'x':
                    case 'X':
                        return Matrix4x4(
                            1, 0, 0, 0,  // Linha 0
                            0, 1, 0, 0,  // Linha 1
                            0, 0, -1, 0, // Linha 2
                            0, 0, 0, 1   // Linha 3
                        );
                    case 'y':
                    case 'Y':
                        return Matrix4x4(
                            -1, 0, 0, 0, // Linha 0
                            0, 1, 0, 0,  // Linha 1
                            0, 0, 1, 0,  // Linha 2
                            0, 0, 0, 1   // Linha 3
                        );
                    case 'z':
                    case 'Z':
                        return Matrix4x4(
                            1, 0, 0, 0,  // Linha 0
                            0, -1, 0, 0, // Linha 1
                            0, 0, 1, 0,  // Linha 2
                            0, 0, 0, 1   // Linha 3
                        );
                    default:
                        throw std::invalid_argument("Invalido. Use x, y, z.");
                }
            }
            
            
            
        //     // matrix necessaria para reflexão oeixo arbitrario
        //   static  Matrix4x4 householder(const Vec3& pc, Vec3& vetor_normal){
        //         Vec3 normal = vetor_normal.normalize();
        //         double nor = vetor_normal.magnitude();
        //         Matrix4x4 ind;
        //         Matrix4x4 householder_matrix = ind.I();
        //         Matrix4x4 n_nt;
            
        //         n_nt.m[0][0] = normal.x*normal.x;
        //         n_nt.m[0][1] = normal.x*normal.y;
        //         n_nt.m[0][2] = normal.x*normal.z;
        //         n_nt.m[0][3] = 0;
        //         n_nt.m[1][0] = normal.y*normal.x;
        //         n_nt.m[1][1] = normal.y*normal.y;
        //         n_nt.m[1][2] = normal.y*normal.z;
        //         n_nt.m[1][3] = 0;
        //         n_nt.m[2][0] = normal.z*normal.x;
        //         n_nt.m[2][1] = normal.z*normal.y;
        //         n_nt.m[2][2] = normal.z*normal.z;
        //         n_nt.m[2][3] = 0;
        //         n_nt.m[3][0] = 0;
        //         n_nt.m[3][1] = 0;
        //         n_nt.m[3][2] = 0;
        //         n_nt.m[3][3] = 0;
            
        //         for (int i = 0; i < 4; i++) {
        //             for (int j = 0; j < 4; j++) {
        //                 householder_matrix.m[i][j] -= 2.0 * n_nt.m[i][j] / (nor * nor);
        //             }
                
        //         }
        //         Matrix4x4 matrix_reflection = translation(pc.x, pc.y, pc.z) * householder_matrix * translation(-pc.x, -pc.y, -pc.z);
        //         return matrix_reflection;
        //     }

        static Matrix4x4 householder(const Vec3& pc, Vec3& vetor_normal) {
            Vec3 normal = vetor_normal.normalize();
            double nor = vetor_normal.magnitude();
            Matrix4x4 householder_matrix = Matrix4x4::I();
            Matrix4x4 n_nt;
        
            n_nt.m[0][0] = normal.x * normal.x;
            n_nt.m[0][1] = normal.x * normal.y;
            n_nt.m[0][2] = normal.x * normal.z;
            n_nt.m[0][3] = 0;
            n_nt.m[1][0] = normal.y * normal.x;
            n_nt.m[1][1] = normal.y * normal.y;
            n_nt.m[1][2] = normal.y * normal.z;
            n_nt.m[1][3] = 0;
            n_nt.m[2][0] = normal.z * normal.x;
            n_nt.m[2][1] = normal.z * normal.y;
            n_nt.m[2][2] = normal.z * normal.z;
            n_nt.m[2][3] = 0;
            n_nt.m[3][0] = 0;
            n_nt.m[3][1] = 0;
            n_nt.m[3][2] = 0;
            n_nt.m[3][3] = 0;
        
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    householder_matrix.m[i][j] -= 2.0 * n_nt.m[i][j] / (nor * nor);
                }
            }
        
            Matrix4x4 matrix_reflection = Matrix4x4::translation(pc.x, pc.y, pc.z) * householder_matrix * Matrix4x4::translation(-pc.x, -pc.y, -pc.z);
            return matrix_reflection;
        }

        
        
    
    //   Vec4 operator=(Vec3& vetor){
    //       return Vec4(vetor.x, vetor.y, vetor.z, 1.0);
    //   }

    // void transform( Vec3& vetor, Matrix4x4& transformation_matrix) {
    //     Vec4 vetor4 = to_Vec4(vetor);
    //     Vec4 t = transformation_matrix * vetor4;
    //     vetor4.x = t.x;
    //     vetor4.y = t.y;
    //     vetor4.z = t.z;
    // }

};  
#endif
