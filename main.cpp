#define SDL_MAIN_HANDLED
#include <iostream>
#include <cmath>
#include <chrono>
#include <SDL.h>

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

using namespace std;

int main() {
    Vec3 p0 = Vec3(0,0,0);
    
    double x_min = -2;
    double y_min = -2;
    double x_max = 2;
    double y_max = 2;
    double d1 = -7;
    double cols1 = 300;
    double rows1 = 300;
    double aspect_ratio = 1;

    //double viewport_width = 3.2; 
    //double viewport_height = viewport_width/aspect_ratio;
    //double viewport_distance = 1.0;
    int image_width = 300;
    int image_height = image_width/aspect_ratio;



    //double sphere_radius = 4.0;
    //double cilinder_radius = std::trunc(sphere_radius / 3.0); // Corrigido
    //double cilinder_height = sphere_radius *3.0;
    //double cone_radius = 4.0; // Set the cone radius
    //double cone_height = 12.0; // Set the cone height


    //;//esfera centro posição

    //Vec3 d_cil = Vec3(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));//direção cilindro
    //Vec3 cilinder_center = Vec3(0.0, 0.0, -5.0);//cilindro centro posição

    //Vec3 cone_base_center = Vec3(0.0, 0.0, -20.0); // Set the cone base center position
    //Vec3 cone_top_vertex = Vec3(0.0, 0.0 , -10.0); // Set the cone top vertex position

    //Vec3 plane_p0 = Vec3(0.0, -5.0, 0.0); // Green plane
    //Vec3 plane_normal = Vec3(0.0, 1.0, 0.0);
    //Vec3 plane2_p0 = Vec3(0.0, 0.0, -30.0); // Blue plane
    //Vec3 plane2_normal = Vec3(0.0, 0.0, 1.0);
    
    Material mat_malha = Material(
        Vec3(0.8, 0.2, 0.2),   // Cor ambiente (vermelho)
        Vec3(0.8, 0.2, 0.2),   // Cor difusa
        Vec3(0.5, 0.5, 0.5),   // Cor especular (brilho)
        1.0                    // Coeficiente de brilho
    );
    
    Vec3 bg_color = Vec3(0.0, 0.0, 0.0);
     Material mat_sphere = Material(
        Vec3(0.7, 0.2, 0.2),
        Vec3(0.7, 0.2, 0.2),
        Vec3(0.7, 0.2, 0.2),
        100.0
    );
    Material mat_cilinder = Material(
        Vec3(0.2, 0.3, 0.8), //ambiente
        Vec3(0.2, 0.3, 0.8), //difuso
        Vec3(0.2, 0.3, 0.8),// especular
        1
    );
    Material mat_cone = Material(
        Vec3(0.8, 0.3, 0.2), // Ambient
        Vec3(0.8, 0.3, 0.2), // Diffuse
        Vec3(0.8, 0.3, 0.2), // Specular
        3
    );
    Material mat_p1 = Material(
        Vec3(0.2, 0.7, 0.2),
        Vec3(0.2, 0.7, 0.2),
        Vec3(0.0, 0.0, 0.0),
        1
    );
    Material mat_p2 = Material(
        Vec3(0.3, 0.3, 0.7),
        Vec3(0.3, 0.3, 0.7),
        Vec3(0.0, 0.0, 0.0),
        1
    );

    double sphere_radius = 4.0;
    Vec3 sphere_center = Vec3(0.0, 0, -13.0);

    Sphere* sphere = new Sphere(sphere_center, sphere_radius, mat_sphere);

    Vec3 plane_p0 = Vec3(0.0, -5.0, 0.0); // Green plane
    Vec3 plane_normal = Vec3(0.0, 1.0, 0.0);
    Vec3 plane2_p0 = Vec3(0.0, 0.0, -30.0); // Blue plane
    Vec3 plane2_normal = Vec3(0.0, 0.0, 1.0);
    
    Plane* plane = new Plane(plane_p0, plane_normal, mat_p1);
    Plane* plane2 = new Plane(plane2_p0, plane2_normal, mat_p2);
    
    Vec3 cilinder_center = Vec3(0.0, -5.0, -20.0);
    Vec3 d_cil = Vec3(0, 1, 0);
    double cilinder_radius = 4.0; // Corrigido
    double cilinder_height = 10.0;
    Cilinder* cilinder = new Cilinder(cilinder_center, d_cil, cilinder_radius, cilinder_height, mat_cilinder);

    Vec3 cone_base_center = Vec3(0.0, 0.0, -10.0); // Set the cone base center position
    Vec3 cone_top_vertex = Vec3(0.0, 10.0 , -10.0); // Set the cone top vertex position
    double cone_radius = 4.0; // Set the cone radius
    
    Cone* cone = new Cone(cone_base_center, cone_top_vertex, cone_radius, mat_cone);
    Malha* malha = new Malha("C:/Users/PAZ/Desktop/MariluCG1/engine/shapes/cubo.obj", mat_malha);
    // Add lights
    Light light1 = Light(
        Vec3(0.0, 0.0, -2.0),
        Vec3(1.0, 1.0, 1.0),
        0.3
    );
    Light light2 = Light(
        Vec3(0.8, 0.8, 0.0),
        Vec3(1.0, 1.0, 1.0),
        0.3
    );
    Vec3 ambient_light = Vec3(0.3, 0.3, 0.3);
    
    Camera camera = Camera(p0, x_min, y_min, x_max, y_max, d1, cols1, rows1, bg_color);
    
    Scene scene = Scene(ambient_light);
    //scene.add_object(sphere);
    //scene.add_object(cilinder);
    scene.add_object(plane);
    scene.add_object(plane2);
    //scene.add_object(cone);
    scene.add_object(malha);

    scene.add_light(light1);
    scene.add_light(light2);
    
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
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                goto quit;
            }
        }

        // Draw scene
        camera.draw_scene(renderer, scene);

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

    //delete cone;
    delete plane;
    delete plane2;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}