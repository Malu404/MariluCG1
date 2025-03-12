#ifndef CANVAS_H
#define CANVAS_H
#include "shapes/plane.h"
#include "shapes/sphere.h"
#include <SDL_render.h>
#include <tuple>
#include "scene.h"
#include "ray.h"
#include "light.h"
#include "shapes/shape.h"
#include "intersection.hpp"


//mudar de Canvas pra canvas
//mudar de janela pra janela
class Canvas {
    public:
        Vec3 pos, bg_color;
        Vec3 eixo_x = Vec3(1, 0, 0);
        Vec3 eixo_y = Vec3(0, 1, 0);
        Vec3 eixo_z = Vec3(0, 0, 1);
        Canvas () : pos(Vec3()), bg_color(Vec3(1.0, 1.0, 1.0)), janela(Janela()) {}
        Canvas (Vec3 pos, double x_min, double y_min, double x_max, double y_max, double d1, double cols1, double rows1, Vec3 bg_color) :
            pos(pos), bg_color(bg_color), janela(Janela(x_min, y_min, x_max, y_max, d1, cols1, rows1)) {}

        void set_d(double d) {
            janela.d = d;
        }

        // tupla TEM INTERSEÇÃO, OBJETO, PONTO DE INTERSEÇÃO
        // tuple<bool, Shape*, Vec3> send_ray(Scene scene, int x, int y) {
        //     Vec3 dr;
        //     dr.x = janela.X_min + janela.dx/2 + janela.dx * x;
        //     dr.y = janela.Y_max - janela.dy/2 - janela.dy * y;
        //     dr.z = janela.d;
            
        //     // vetor direção pro quadrado do frame
        //     Vec3 dr_transformed = dr.x * eixo_x + dr.y * eixo_y + dr.z * eixo_z;
        //     Vec3 dr_normalized = dr_transformed.normalized();
        //     Ray r = Ray(pos, dr_normalized); // nosso raio

        //     // pega o objeto mais próximo na cena
        //     auto [closest_shape, t] = scene.get_closest_object(r);
        //     if (t > 0.0) {
        //         return make_tuple(true, closest_shape, r.at(t));
        //     }
        //     return make_tuple(false, closest_shape, r.at(t));
        // }


        Intersection Canvas::send_ray(Scene scene, int x, int y) {
            Vec3 dr;
            dr.x = janela.X_min + janela.dx / 2 + janela.dx * x;
            dr.y = janela.Y_max - janela.dy / 2 - janela.dy * y;
            dr.z = janela.d;
        
            // Vetor direção normalizado
            Vec3 dr_transformed = dr.x * eixo_x + dr.y * eixo_y + dr.z * eixo_z;
            Vec3 dr_normalized = dr_transformed.normalized();
            Ray r = Ray(pos, dr_normalized); // Nosso raio
        
            // Pega o objeto mais próximo na cena
            auto [closest_shape, t] = scene.get_closest_object(r);
        
            if (t > 0.0) {
                Vec3 p_intersect = r.at(t); // Ponto de interseção
                Vec3 normal = closest_shape->get_normal(p_intersect); // Normal no ponto de interseção
                Vec3 color = closest_shape->mat.k_ambient; // Cor ambiente (ou defina uma cor padrão)
        
                // Retorna um objeto Intersection
                return Intersection(t, p_intersect, normal, color, closest_shape);
            } else {
                // Se não houve interseção, retorna um Intersection inválido
                return Intersection();
            }
        }

        void look_at(Vec3 p, Vec3 up) {
            Vec3 up_vector = (up - pos).normalized();
            Vec3 novo_z = (p - pos).normalized();
            Vec3 novo_x = novo_z.cross(up_vector).normalized(); // direita
            Vec3 novo_y = novo_x.cross(novo_z).normalized(); // cima
            eixo_x = novo_x;
            eixo_y = novo_y;
            eixo_z = -novo_z;
        }

        void draw_scene(SDL_Renderer* renderer, Scene scene) {
            SDL_SetRenderDrawColor(renderer, bg_color.x, bg_color.y, bg_color.z, 1.0);
            SDL_RenderClear(renderer);
            Vec3 dr;
            dr.z = janela.d;
            for (int row = 0; row < janela.rows; row++) { // cada linha
                dr.y = janela.Y_max - janela.dy/2 - janela.dy * row;
                for (int col = 0; col < janela.cols; col++ ) { // cada coluna
                    // vetor direção pro quadrado do frame
                    dr.x = janela.X_min + janela.dx/2 + janela.dx * col;
                    
                    Vec3 dr_transformed = dr.x * eixo_x + dr.y * eixo_y + dr.z * eixo_z;
                    Vec3 dr_normalized = dr_transformed.normalized();
                    Ray r = Ray(pos, dr_normalized); // nosso raio

                    // pega o objeto mais próximo na cena
                    auto [closest_shape, t] = scene.get_closest_object(r);

                    // se ele não estiver atrás da câmera, calcula aS luzes (mas testa pra sombra antes né etc.)
                    if (t > 0.0) {
                        Vec3 p_intersect = r.at(t); // Ponto de interseção do raio com o objeto                    
                        Vec3 ieye = Vec3(0.0, 0.0, 0.0);

                        
                        Vec3 k_ambient = closest_shape->mat.k_ambient;
                        Vec3 k_diffuse = closest_shape->mat.k_diffuse;

                        Sphere* sphere_ptr = dynamic_cast<Sphere*>(closest_shape);
                        if (sphere_ptr && sphere_ptr->texture) {
                            auto [u, v] = sphere_ptr->get_uv(p_intersect);
                            Vec3 tex_color = sphere_ptr->texture->sample(u, v);
                            k_ambient = tex_color;
                            k_diffuse = tex_color;
                        }

                        Plane* plane_ptr = dynamic_cast<Plane*>(closest_shape);
                        if (plane_ptr && plane_ptr->texture) {
                            auto [u, v] = plane_ptr->get_uv(p_intersect);
                            Vec3 tex_color = plane_ptr->texture->sample(u, v);
                            k_ambient = tex_color;
                            k_diffuse = tex_color;
                        }

                        Vec3 iamb = k_ambient * scene.ambient_light;
                        ieye = ieye + iamb;
                        
                        for (Light light : scene.lights) {
                            bool na_sombra = false;
                            Vec3 ldr;
                            if (light.tipo == TipoLuz::Pontual) {
                                ldr = light.pos - p_intersect;
                            } else if (light.tipo == TipoLuz::Direcional) {
                                ldr = light.direction;
                            } else if (light.tipo == TipoLuz::Spot) {
                                ldr = light.pos - p_intersect;
                                if ((-light.direction).dot(ldr.normalized()) <= cos(degreesToRadians(light.angle))) {
                                    continue;
                                }
                            }

                            Ray raio_p_luz = Ray(p_intersect, ldr);
                            
                            // Teste de sombra
                            for (Shape* s_test : scene.objects) {
                                // if (s_test == closest_shape) {continue;}
                                double distance = s_test->intersects(raio_p_luz);
                                if (distance >= 0.0001 && (light.tipo == TipoLuz::Direcional || distance <= 1.0)) {
                                    na_sombra = true;
                                    break;
                                }
                            }

                            Vec3 l = ldr.normalized();
                            Vec3 n = closest_shape->get_normal(p_intersect);
                            Vec3 r = (2.0 * (l.dot(n)))*n - l;
                            Vec3 v = -dr_normalized;

                            double nl = n.dot(l);
                            double rv = r.dot(v);
                            if (nl < 0.0 || na_sombra) nl = 0.0;
                            if (rv < 0.0 || na_sombra) rv = 0.0;
                            
                            Vec3 idif = k_diffuse * nl * light.color * light.intensity;
                            Vec3 iesp = closest_shape->mat.k_specular * pow(rv, closest_shape->mat.e) * light.color * light.intensity;

                            ieye = ieye + idif + iesp;
                        }

                        draw_pixel(renderer, col, row, ieye.clamp(0.0, 1.0).rgb_255());
                    } else {
                        draw_pixel(renderer, col, row, bg_color.clamp(0.0, 1.0).rgb_255());
                    }
                }
            }

            SDL_RenderPresent(renderer);
        }
        

        // Function to convert degrees to radians
        double degreesToRadians(double degrees) {
            return degrees * (M_PI / 180.0);
        }

        // Function to convert radians to degrees
        double radiansToDegrees(double radians) {
            return radians * (180.0 / M_PI);
        }

        inline void draw_pixel(SDL_Renderer* renderer, int x, int y, Vec3 color) {
            SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, 1.0);
            SDL_RenderDrawPoint(renderer, x, y);
        }

         void aumentar_d() {
            janela.d -= 0.1;
            
        }
    
        void diminuir_d() {
            janela.d += 0.1;
           
        }

        class Janela {
        public:
            double width, height, dx, dy, X_min, Y_min, X_max, Y_max, d;
            int cols, rows;
            
            Janela () {
                Vec3 pos = Vec3(0.0, 0.0, -1.0);
                X_min = -1.0; 
                Y_min = -1.0; 
                X_max = 1.0; 
                Y_max = 1.0; //default

                width = X_max - X_min; 
                height = Y_max - Y_min;
                cols = 100; rows = 100;
                d = -1.0;
                dx = width/cols;
                dy = height/rows;
            }

            Janela (double x_min, double y_min, double x_max, double y_max, double d1, double cols1, double rows1) {
                X_min = x_min; 
                Y_min = y_min; 
                X_max = x_max; 
                Y_max = y_max; //default

                d = d1;

                width = X_max - X_min; 
                height = Y_max - Y_min;

                cols = cols1; 
                rows = rows1;

                dx = width/cols;
                dy = height/rows;    
            }
        };
        Janela janela;
};

#endif