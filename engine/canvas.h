#ifndef CANVAS_H
#define CANVAS_H
#include "shapes/sphere.h"
#include <SDL_render.h>
#include "scene.h"
#include "ray.h"
#include "light.h"
#include "shapes/shape.h"
#include <iostream>
//mudar de Canvas pra canvas
//mudar de janela pra janela
class Canvas {
    public:
        Vec3 pos, bg_color;
        Canvas () : pos(Vec3()), bg_color(Vec3(1.0, 1.0, 1.0)), janela(Janela()) {}
        Canvas (Vec3 pos, double x_min, double y_min, double x_max, double y_max, double d1, double cols1, double rows1, Vec3 bg_color) :
            pos(pos), bg_color(bg_color), janela(Janela(x_min, y_min, x_max, y_max, d1, cols1, rows1)) {}

        void draw_scene(SDL_Renderer* renderer, Scene scene) {
            SDL_SetRenderDrawColor(renderer, bg_color.x, bg_color.y, bg_color.z, 1.0);
            SDL_RenderClear(renderer);
            Light light = scene.lights.front(); // pegando só a primeira luz por enquanto...              
            Vec3 dr;
            dr.z = janela.d;
            for (int row = 0; row < janela.rows; row++) { // cada linha
                dr.y = janela.Y_max - janela.dy/2 - janela.dy * row;
                for (int col = 0; col < janela.cols; col++ ) { // cada coluna
                    // vetor direção pro quadrado do frame
                    dr.x = janela.X_min + janela.dx/2 + janela.dx * col;
                    
                    Vec3 dr_normalized = dr.normalize();
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

                        Vec3 iamb = k_ambient * scene.ambient_light;
                        ieye = ieye + iamb;
                        // Testa todas as luzes da cena
                        /*for (Light light : scene.lights) {
                            // Check da sombra
                            bool na_sombra = false;
                            // Raio do ponto de interseção até a luz (não normaliza o vetor direção)
                            Ray raio_p_luz = Ray(p_intersect, light.pos - p_intersect);
                            // testa pra todos os objetos da cena pra ver se eles tão na frente da luz.
                            for (Shape* s_test : scene.objects) {
                                // distância do ponto de interseção até o ponto de luz
                                double distance = s_test->intersects(raio_p_luz);

                                // 0.0001 evita problemas de precisão double
                                // isso checa se o objeto está ENTRE a interseção e o raio de luz
                                if (distance >= 0.0001 && distance <= 1.0) {
                                    na_sombra = true; // se sim, o objeto q a gente ia desenhar tá na sombra.
                                    break;
                                }
                            }

                            Vec3 l = (light.pos - p_intersect).normalize(); // Vetor apontando na direção da luz
                            Vec3 n = closest_shape->get_normal(p_intersect); // Vetor normal
                            Vec3 r = (2.0 * (l.dot(n)))*n - l; // Vetor l refletido na normal
                            Vec3 v = -dr_normalized; // Vetor apontando na direção do observador

                            double nl = n.dot(l); // N escalar L
                            double rv = r.dot(v); // R escalar V
                            if (nl < 0.0 || na_sombra) { nl = 0.0; }
                            if (rv < 0.0 || na_sombra) { rv = 0.0; }

                            Vec3 idif = closest_shape->mat.k_diffuse * nl * light.color;
                            Vec3 iesp = closest_shape->mat.k_specular * pow(rv, closest_shape->mat.e) * light.color;

                            ieye = ieye + idif + iesp;
                        }*/
                        for (Light light : scene.lights) {
                            bool na_sombra = false;
                            Ray raio_p_luz = Ray(p_intersect, light.pos - p_intersect);
                            
                            // Teste de sombra
                            for (Shape* s_test : scene.objects) {
                                double distance = s_test->intersects(raio_p_luz);
                                if (distance >= 0.0001 && distance <= 1.0) {
                                    na_sombra = true;
                                    break;
                                }
                            }

                            Vec3 l = (light.pos - p_intersect).normalize();
                            Vec3 n = closest_shape->get_normal(p_intersect);
                            Vec3 r = (2.0 * (l.dot(n)))*n - l;
                            Vec3 v = -dr_normalized;

                            double nl = n.dot(l);
                            double rv = r.dot(v);
                            if (nl < 0.0 || na_sombra) nl = 0.0;
                            if (rv < 0.0 || na_sombra) rv = 0.0;

                            // Cálculo da atenuação do spot
                            float spot_attenuation = light.spot_factor(p_intersect);
                            
                            Vec3 idif = k_diffuse * nl * light.color * light.intensity * spot_attenuation;
                            Vec3 iesp = closest_shape->mat.k_specular * pow(rv, closest_shape->mat.e) * light.color * light.intensity * spot_attenuation;

                            ieye = ieye + idif + iesp;
                        }

                        draw_pixel(renderer, col, row, ieye.clamp(0.0, 1.0).rgb_255());
                    }
                }
            }

            SDL_RenderPresent(renderer);
        }

        void aumentar_d() {
            janela.d -= 0.1;
            
        }
    
        void diminuir_d() {
            janela.d += 0.1;
           
        }
    
    private:
        inline void draw_pixel(SDL_Renderer* renderer, int x, int y, Vec3 color) {
            SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, 1.0);
            SDL_RenderDrawPoint(renderer, x, y);
        }

        class Janela {//trocar nome para janela
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