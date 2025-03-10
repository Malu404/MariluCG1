#define SDL_MAIN_HANDLED
#include <iostream>
#include <cmath>
#include <chrono>
#include <SDL.h>

#include "utils/vec4.h"
#include "utils/matriz4x4.h"
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
    Vec3 p0 = Vec3(0,0,10);
    
    double x_min = -2;
    double y_min = -2;
    double x_max = 2;
    double y_max = 2;
    double d1 = -2;
    double cols1 = 600;
    double rows1 = 600;
    double aspect_ratio = 1;

    //double viewport_width = 3.2; 
    //double viewport_height = viewport_width/aspect_ratio;
    //double viewport_distance = 1.0;
    int image_width = 600;
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
        Vec3(0.8, 0.2, 0.8),   // Cor ambiente (vermelho)
        Vec3(0.8, 0.2, 0.8),   // Cor difusa
        Vec3(0.9, 0.5, 0.5),   // Cor especular (brilho)
        10.0                    // Coeficiente de brilho
    );
    
    Vec3 bg_color = Vec3(0.0, 0.0, 0.0);
     Material mat_sphere = Material(
        Vec3(0.7, 0.2, 0.2),
        Vec3(0.7, 0.2, 0.2),
        Vec3(0.7, 0.2, 0.2),
        10.0
    );
    Material mat_cilinder = Material(
        Vec3(0.2, 0.3, 0.8), //ambiente
        Vec3(0.2, 0.3, 0.8), //difuso
        Vec3(0.2, 0.3, 0.8),// especular
        1.0
    );
    Material mat_cone = Material(
        Vec3(0.8, 0.3, 0.2), // Ambient
        Vec3(0.8, 0.3, 0.2), // Diffuse
        Vec3(0.8, 0.3, 0.2), // Specular
        10.0
    );
    Material mat_p1 = Material(
        Vec3(0.2, 0.7, 0.2),
        Vec3(0.2, 0.7, 0.2),
        Vec3(0.0, 0.0, 0.0),
        10.0
    );
    Material mat_p2 = Material(
        Vec3(0.3, 0.3, 0.7),
        Vec3(0.3, 0.3, 0.7),
        Vec3(0.0, 0.0, 0.0),
        10.0
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


    //testando cilindro2
    Vec3 cilinder_center2 = Vec3(15.0, -5.0, -20.0);
    Vec3 d_cil2 = Vec3(0, 1, 0);
    double cilinde_radius2 = 4.0;
    double cilinder_height2 = 10.0;

    Cilinder* cilinder2 = new Cilinder(cilinder_center2, d_cil2, cilinde_radius2, cilinder_height2, mat_cilinder);

    //testando cilinro3
    Vec3 cilinder_center3 = Vec3(-15.0, -5.0, -20.0);
    Vec3 d_cil3 = Vec3(0, 1, 0);
    double cilinde_radius3 = 4.0;
    double cilinder_height3 = 10.0;

    Cilinder* cilinder3 = new Cilinder(cilinder_center3, d_cil3, cilinde_radius3, cilinder_height3, mat_cilinder);

    

    
    Vec3 cilinder_center = Vec3(-15.0, -5.0, -20.0);
    Vec3 d_cil = Vec3(0, 1, 0);
    double cilinder_radius = 4.0; // Corrigido
    double cilinder_height = 10.0;
    Cilinder* cilinder = new Cilinder(cilinder_center, d_cil, cilinder_radius, cilinder_height, mat_cilinder);

    Vec3 cone_base_center = Vec3(0.0, 0.0, -10.0); // Set the cone base center position
    Vec3 cone_top_vertex = Vec3(0.0, 10.0 , -10.0); // Set the cone top vertex position
    double cone_radius = 4.0; // Set the cone radius
    
    // Cone* cone = new Cone(cilinder_center, cilinder_center + d_cil * cilinder_height, cilinder_radius, mat_cone);
    // Malha* malha = new Malha("engine/shapes/teapot_rotated.obj", mat_malha);
    // Add lights
    Light light = Light(
        Vec3(4.0, 3.0, 10.0),
        Vec3(1.0, 1.0, 1.0),
        0.7
    );
    Vec3 ambient_light = Vec3(0.3, 0.3, 0.3);
    
    Canvas canvas = Canvas(p0, x_min, y_min, x_max, y_max, d1, cols1, rows1, bg_color);
    
    // Criação do cone
    Cone* cone = new Cone(cilinder_center, cilinder_center + d_cil * cilinder_height, cilinder_radius, mat_cone);

// Rotacionar o cone
// Vec3 rotation_axis = Vec3(0, 1, 0);
// double rotation_angle = 45.0;
// Matrix4x4 rotation_matrix = Matrix4x4::rotation_arbitrary_axis(rotation_axis, rotation_angle);
// cilinder->center = rotation_matrix * cilinder->center;
// cilinder->direction = rotation_matrix * cilinder->direction;

// // Atualiza o top_center após a rotação
// Vec3 top_center = cilinder->center + cilinder->direction * cilinder->height;



// Vec3 translation_vector = Vec3(5, 0, 0); // Move 5 unidades no eixo X
// Matrix4x4 translation_matrix = Matrix4x4::translation(translation_vector.x, translation_vector.y, translation_vector.z);
// cilinder->center = translation_matrix * cilinder->center;
    
// Vec3 translation_vector = -cilinder->center;

// // Crie a matriz de translação
// Matrix4x4 translation_matrix = Matrix4x4::translation(translation_vector.x, translation_vector.y, translation_vector.z);

// // Aplique a translação ao center do cilindro
// cilinder->center = translation_matrix * cilinder->center;

// // Atualize o top_center após a translação
// Vec3 top_center = cilinder->center + cilinder->direction * cilinder->height;

// std::cout << "Novo centro do cilindro: (" << cilinder->center.x << ", " << cilinder->center.y << ", " << cilinder->center.z << ")" << std::endl;



// Vec3 translation_vector = -cilinder->center;
// Matrix4x4 translation_matrix = Matrix4x4::translation(translation_vector.x, translation_vector.y, translation_vector.z);
// cilinder->center = translation_matrix * cilinder->center;

// // 2. Aplicar a rotação (45 graus em torno do eixo Y)
// double rotation_angle = 45.0; // Ângulo de rotação em graus
// Matrix4x4 rotation_matrix = Matrix4x4::rotation(rotation_angle, 'x');
// cilinder->center = rotation_matrix * cilinder->center;
// cilinder->direction = rotation_matrix * cilinder->direction; // Rotaciona a direção do cilindro

// // 3. Transladar de volta para a posição original
// Matrix4x4 inverse_translation_matrix = Matrix4x4::translation(-translation_vector.x, -translation_vector.y, -translation_vector.z);
// cilinder->center = inverse_translation_matrix * cilinder->center;

// // Atualize o top_center após a rotação e translação
// Vec3 top_center = cilinder->center + cilinder->direction * cilinder->height;

// // Verifique o resultado
// std::cout << "Novo centro do cilindro: (" << cilinder->center.x << ", " << cilinder->center.y << ", " << cilinder->center.z << ")" << std::endl;
// std::cout << "Nova direção do cilindro: (" << cilinder->direction.x << ", " << cilinder->direction.y << ", " << cilinder->direction.z << ")" << std::endl;






    
    
    Scene scene = Scene(ambient_light);
    // scene.add_object(sphere);
    scene.add_object(cilinder);
    scene.add_object(plane);
    scene.add_object(plane2);
    scene.add_object(cone);
    //scene.add_object(cilinder2);
    //scene.add_object(cilinder3);
    //scene.add_object(malha);

    scene.add_light(light);
    
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

    //delete cone;
    delete plane;
    delete plane2;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}