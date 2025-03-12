#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"
#include "utils/matriz4x4.h"
#include <cstddef>
#define SDL_MAIN_HANDLED
#include <iostream>
#include <cmath>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>

#include "utils/vec3.h"
#include "engine/canvas.h"
//#include "engine/camera.h"
#include "engine/light.h"
#include "engine/scene.h"
#include "engine/shapes/material.h"
#include "engine/shapes/sphere.h"
#include "engine/shapes/plane.h"
#include "engine/shapes/cilinder.h"
#include "engine/shapes/cone.h"
#include "engine/shapes/malha.h"
#include "engine/shapes/textura.h"
#include "engine/shapes/textura.cpp"
using namespace std;


int main() {
    Vec3 p0 = Vec3(0,2.0,10.75);
    
    double x_min = -2;
    double y_min = -2;
    double x_max = 2;
    double y_max = 2;
    double d1 = -2;
    double cols1 = 600;
    double rows1 = 600;
    double aspect_ratio = 1;
    int image_width = 600;
    int image_height = image_width/aspect_ratio;

    //inicializa minha textura usando sdl_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! Error: %s\n", IMG_GetError());
        return 1;
    }
    Texture areia = Texture("textura_areia.jpg");
    Texture salada_t = Texture("textura_salada.jpg");
    Vec3 bg_color = Vec3(0.4, 0.65, 0.9);
    Material mat_malha = Material(
        Vec3(1.0, 0.74, 0.34),   // Cor ambiente (vermelho)
        Vec3(1.0, 0.74, 0.34),   // Cor difusa
        Vec3(1.0, 1.0, 1.0),   // Cor especular (brilho)
        5.0                    // Coeficiente de brilho
    );
    Material mat_p1 = Material(
        Vec3(1, 1, 1), //luz ambiente
        Vec3(1, 1, 1), // luz difusa
        Vec3(0.7, 0.7, 0.7), // luz especular
        10000000.0//o quao refletivo éo meu material
    );
    Material mat_cilinder = Material(
        Vec3(0, 0, 0), //ambiente
        Vec3(0, 0, 0), //difuso
        Vec3(1, 1, 1),// especular
        100.0
    );
    Material mat_cone = Material(
        Vec3(0.8, 0.3, 0.2), // Ambient
        Vec3(0.8, 0.3, 0.2), // Diffuse
        Vec3(0.8, 0.3, 0.2), // Specular
        10.0
    );
    Material mat_sphere = Material(
        Vec3(0.2, 0.7, 0.2),
        Vec3(0.2, 0.7, 0.2),
        Vec3(0.0, 0.0, 0.0),
        10.0
    );
    Material mat_p2 = Material(
        Vec3(0.5, 0.5, 0.9),
        Vec3(0.5, 0.5, 0.9),
        Vec3(1.0, 1.0, 1.0),
        100.
    );

    double sphere_radius = 4.0;
    Vec3 sphere_center = Vec3(0.0, 0, -13.0);

    Sphere* sphere = new Sphere(sphere_center, sphere_radius, mat_sphere, NULL);

    Vec3 plane_p0 = Vec3(0.0, 0.0, 0.0); // Green plane
    Vec3 plane_normal = Vec3(0.0, 1.0, 0.0);
    // Vec3 plane2_p0 = Vec3(0.0, 0.0, -30.0); // Blue plane
    // Vec3 plane2_normal = Vec3(0.0, 0.0, 1.0);
    
    Plane* plane = new Plane(plane_p0, plane_normal, mat_p1, &areia, 16, 16);
    // Plane* plane2 = new Plane(plane2_p0, plane2_normal, mat_p2);
    
    Vec3 cilinder_center = Vec3(0.0, -4, -13.0);
    Vec3 d_cil = Vec3(0, 1, 0);
    

    Material mat_cilindertable = Material(
        Vec3(0.42, 0.318, 0.251), //ambiente
        Vec3(0.42, 0.318, 0.251), //difuso
        Vec3(0.42, 0.318, 0.251),// especular
        1
    );

    Material mat_bacia = Material(
        Vec3(0.92, 0.818, 0.751), //ambiente
        Vec3(0.92, 0.518, 0.751), //difuso
        Vec3(0.92, 0.518, 0.751),// especular
        100.0
    );

    // cilindro da cadeira
    Vec3 cilinder_center_chair = Vec3(0.0, 0, 0);
    Vec3 d_cil_chair = Vec3(0, 1, 0);
    double x_table = 0;
    double y_table = 0;
    double z_table = 13;
    Vec3 d_cil_table = Vec3(0, 1, 0);
    double cilinder_table_radius = 0.8; // Corrigido
    double cilinder_table_height = 1.1;

    double y_table_top = cilinder_table_height + cilinder_table_height/15 + cilinder_table_height/20;

    Vec3 cilinder_center_table_neck = Vec3(x_table, y_table+cilinder_table_height/15, z_table);
    Vec3 cilinder_center_table_topo = Vec3(x_table, y_table+cilinder_table_height/15+cilinder_table_height, z_table);
    Vec3 cilinder_center_table_pé = Vec3(x_table, y_table, z_table);

    Cilinder* cilinder_table_neck = new Cilinder(cilinder_center_table_neck, d_cil_table, cilinder_table_radius/4, cilinder_table_height, mat_cilindertable, true, true);
    Cilinder* cilinder_table_topo = new Cilinder(cilinder_center_table_topo, d_cil_table, cilinder_table_radius*1.5, cilinder_table_height/20, mat_cilindertable, true, true);
    Cilinder* cilinder_table_pé = new Cilinder(cilinder_center_table_pé, d_cil_table, cilinder_table_radius/1.5, cilinder_table_height/15, mat_cilindertable, true, true);
    // Cone

    Cilinder* bacia = new Cilinder(Vec3(x_table, y_table_top, z_table), d_cil_table, 0.3, 0.2, mat_p1, true, false);
    Sphere* salada = new Sphere(Vec3(x_table, y_table_top , z_table), 0.3, mat_p1, &salada_t);
    Cilinder* copo = new Cilinder(Vec3(x_table + 0.5, y_table_top, z_table), d_cil_table, 0.075, 0.3, mat_p2, true, false);
    Cilinder* liquido = new Cilinder(Vec3(x_table + 0.5, y_table_top, z_table), d_cil_table, 0.0745, 0.28, mat_cilinder, true, false);

    Vec3 d_cone = Vec3(1,1,-0.5).normalized();
    Vec3 base_cone = Vec3(x_table + 0.58, y_table_top+0.32, z_table);
    double altura_cone = 0.075;
    Cone* sombrinha = new Cone(base_cone,base_cone + d_cone * altura_cone, 0.1, mat_cone, false);
    double h = 0.15;
    Cilinder* sombrinha_pau = new Cilinder(base_cone - d_cone * h, d_cone, 0.01, 0.15, mat_p1, true, true);

    Vec3 cone_base_center = Vec3(0.0, 0.0, -10.0); // Set the cone base center position
    Vec3 cone_top_vertex = Vec3(0.0, 10.0 , -10.0); // Set the cone top vertex position
    Malha* malha = new Malha("engine/shapes/piramide.obj", mat_malha);
    Malha* malha2 = new Malha("engine/shapes/piramide.obj", mat_malha);
    Malha* malha3 = new Malha("engine/shapes/piramide.obj", mat_malha);
    // Add lights
    Light light = Light::luz_direcional(
        Vec3(1.0,1.0,0.0),
        Vec3(1.0, 1.0, 1.0),
        0.7
    );
    Vec3 ambient_light = Vec3(0.3, 0.3, 0.3);
    Light spot_light = Light::luz_spot(
        Vec3(0, 8, 10),       // Posição
        Vec3(0, -1, -2),       // Direção
        20.0,                      // Ângulo (graus)
        Vec3(1, 1, 1),     // Cor
        1.5f                   // Intensidade
    );
   
    Canvas canvas = Canvas(p0, x_min, y_min, x_max, y_max, d1, cols1, rows1, bg_color);
    
    Scene scene = Scene(ambient_light);
    scene.add_object(sphere);
    scene.add_object(bacia);
    scene.add_object(copo);
    scene.add_object( liquido);
    scene.add_object(plane);
    scene.add_object(salada);
    scene.add_object(malha);
    scene.add_object(malha2);
    scene.add_object(malha3);
    scene.add_object( sombrinha);
    scene.add_object( sombrinha_pau);
    scene.add_light(spot_light);
    scene.add_light(light);
    scene.add_object(cilinder_table_neck);
    scene.add_object(cilinder_table_topo);
    scene.add_object(cilinder_table_pé);

    Vec3 piramide1_centro = Vec3(500, 0, 800);
    Vec3 piramide2_centro = Vec3(250, 0, 800);
    Vec3 piramide3_centro = Vec3(100, 0, 800);
    Matriz4x4 m = Matriz4x4::translation_matrix(piramide1_centro.x, piramide1_centro.y, piramide1_centro.z);
    Matriz4x4 m2 = Matriz4x4::scale_matrix(100, 100, 100, piramide1_centro);
    malha->transform(m);
    malha->transform(m2);
    Matriz4x4 m3 = Matriz4x4::translation_matrix(piramide2_centro.x, piramide2_centro.y, piramide2_centro.z);
    Matriz4x4 m4 = Matriz4x4::scale_matrix(75, 75, 75, piramide2_centro);
    malha2->transform(m3);
    malha2->transform(m4);
    Matriz4x4 m5 = Matriz4x4::translation_matrix(piramide3_centro.x, piramide3_centro.y, piramide3_centro.z);
    Matriz4x4 m6 = Matriz4x4::scale_matrix(50, 50, 50, piramide3_centro);
    malha3->transform(m5);
    malha3->transform(m6);

    canvas.look_at(piramide2_centro, canvas.pos + Vec3(0,1,0));
    
    // SDL init
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { printf("SDL_Init Error: %s\n", SDL_GetError()); return 1; }
    SDL_Window* window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, image_width, image_height, 0);
    if (window == NULL) { printf("SDL_CreateWindow Error: %s\n", SDL_GetError()); SDL_Quit(); return 1; }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) { printf("SDL_CreateRenderer Error: %s\n", SDL_GetError()); SDL_DestroyWindow(window); SDL_Quit(); return 1; }

    // FPS counter
    int frameCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    // Main loop
    SDL_Event event;
    while (true) {
        // Event handler
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) { goto quit; }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        canvas.pos.z -= 1; break;
                    case SDLK_s:
                        canvas.pos.z += 1; break;
                    case SDLK_a:
                        canvas.pos.x -= 1; break;
                    case SDLK_d:
                        canvas.pos.x += 1; break;
                    case SDLK_SPACE:
                        canvas.pos.y += 1; break;
                    case SDLK_LSHIFT:
                        canvas.pos.y -= 1; break;
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // CLICK DO BOTÃO DO MEIO DO MOUSE = LOOK_AT
                if (event.button.button == SDL_BUTTON_MIDDLE) {
                    // picking
                    auto [teve_intersecao, objeto, ponto_intersecao] = canvas.send_ray(event.button.x, event.button.y, scene);
                    // look_at
                    if (teve_intersecao) {
                        canvas.look_at(ponto_intersecao, canvas.pos + Vec3(0,1,0));
                    }
                }
            }
        }

        // Draw scene
        canvas.draw_scene(renderer, scene);

        // Print FPS to terminal
        frameCount++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - startTime;
        if (elapsedTime.count() >= 1.0) {
            std::cout << "FPS: " << frameCount << std::endl;
            frameCount = 0;
            startTime = currentTime;
        }
    }
    quit:

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}