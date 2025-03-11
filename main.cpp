#define SDL_MAIN_HANDLED
#include <iostream>
#include <cmath>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>

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
#include "engine/shapes/textura.h"
#include "engine/shapes/textura.cpp"
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
    int image_width = 600;
    int image_height = image_width/aspect_ratio;

    //inicializa minha textura usando sdl_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! Error: %s\n", IMG_GetError());
        return 1;
    }
    Texture beach_ball = Texture("beach_ball.png");
    Texture pokemon = Texture("mantas-de-pokemon.png");
    Material mat_malha = Material(
        Vec3(0.8, 0.2, 0.8),   // Cor ambiente (vermelho)
        Vec3(0.8, 0.2, 0.8),   // Cor difusa
        Vec3(0.9, 0.5, 0.5),   // Cor especular (brilho)
        10.0                    // Coeficiente de brilho
    );
    
    Vec3 bg_color = Vec3(0.0, 0.0, 0.0);
    Material mat_sphere = Material(
        Vec3(1, 1, 1), //luz ambiente
        Vec3(1, 1, 1), // luz difusa
        Vec3(0.7, 0.7, 0.7), // luz especular
        10000000.0//o quao refletivo éo meu material
    );
    Material mat_cilinder = Material(
        Vec3(0.2, 0.3, 0.8), //ambiente
        Vec3(0.2, 0.3, 0.8), //difuso
        Vec3(0.2, 0.3, 0.8),// especular
        100.0
    );
    Material mat_cilinderchair = Material(
        Vec3(0.2, 0.3, 0.8), //ambiente
        Vec3(0.2, 0.3, 0.8), //difuso
        Vec3(0.2, 0.3, 0.8),// especular
        100.0
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

    Sphere* sphere = new Sphere(sphere_center, sphere_radius, mat_sphere, &pokemon);

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

    // cilindro da cadeira
    Vec3 cilinder_center_chair = Vec3(0.0, 0, 0);
    Vec3 d_cil_chair = Vec3(0, 1, 0);
    double cilinder_chair_radius = 4.0; // Corrigido
    double cilinder_chair_height = 10.0;
    Cilinder* cilinder_ch1 = new Cilinder(cilinder_center_chair, d_cil_chair, cilinder_chair_radius, cilinder_chair_height, mat_cilinderchair);
    Cilinder* cilinder_ch2 = new Cilinder(cilinder_center_chair, d_cil_chair, cilinder_chair_radius, cilinder_chair_height, mat_cilinderchair);
    Cilinder* cilinder_ch3 = new Cilinder(cilinder_center_chair, d_cil_chair, cilinder_chair_radius, cilinder_chair_height, mat_cilinderchair);
    Cilinder* cilinder_ch4 = new Cilinder(cilinder_center_chair, d_cil_chair, cilinder_chair_radius, cilinder_chair_height, mat_cilinderchair);
    Cilinder* cilinder_ch5 = new Cilinder(cilinder_center_chair, d_cil_chair, cilinder_chair_radius, cilinder_chair_height, mat_cilinderchair);     
    Cilinder* cilinder_ch6 = new Cilinder(cilinder_center_chair, d_cil_chair, cilinder_chair_radius, cilinder_chair_height, mat_cilinderchair);
    Cilinder* cilinder_ch7 = new Cilinder(cilinder_center_chair, d_cil_chair, cilinder_chair_radius, cilinder_chair_height, mat_cilinderchair);
    // Cone

    Vec3 cone_base_center = Vec3(0.0, 0.0, -10.0); // Set the cone base center position
    Vec3 cone_top_vertex = Vec3(0.0, 10.0 , -10.0); // Set the cone top vertex position
    double cone_radius = 4.0; // Set the cone radius
    
    Cone* cone = new Cone(cilinder_center, cilinder_center + d_cil * cilinder_height, cilinder_radius, mat_cone);
    Malha* malha = new Malha("engine/shapes/teapot_rotated.obj", mat_malha);
    //Add lights


    Light light = Light(
        Vec3(4.0, 3.0, 10.0),
        Vec3(1.0, 1.0, 1.0),
        0.7
    );




    Vec3 ambient_light = Vec3(0.3, 0.3, 0.3);
    Light spot_light = Light(
        Vec3(0, 8, 10),       // Posição
        Vec3(0, -1, -2),       // Direção
        Vec3(1, 1, 1),        // Cor
        1.5f,                 // Intensidade
        30.0,                 // Ângulo (graus)
        8.0                   // Expoente de suavização
    );
   
    Canvas canvas = Canvas(p0, x_min, y_min, x_max, y_max, d1, cols1, rows1, bg_color);
    
    // // Criação do cone
    // Cone* cone = new Cone(cilinder_center, cilinder_center + d_cil * cilinder_height, cilinder_radius, mat_cone);

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
// Vec3 rotation_axis = Vec3(0, 0, 1);
//  double rotation_angle = 45.0;
//  Matrix4x4 rotation_matrix = Matrix4x4::rotation_arbitrary_axis(rotation_axis, rotation_angle);
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





// // Cria uma matriz de transformação (exemplo: escala 2x em x, y, z)
// Matrix4x4 scaleMatrix = Matrix4x4::scale_matrix(0.5, 0.5, 0.5);

// // Aplica a transformação à malha
// malha->transform(scaleMatrix);

// // Ou usando apply_transform
// malha->apply_transform(scaleMatrix);
// Cria uma matriz de transformação (exemplo: escala 2x em X, Y, Z)


// Matrix4x4 scale_matrix = Matrix4x4::scale_matrix(2.0, 2.0, 2.0);

// // Aplica a transformação aos objetos
// cilinder->transform(scale_matrix);
// cone->transform(scale_matrix);

    
    
    
    Scene scene = Scene(ambient_light);
    scene.add_object(sphere);
    scene.add_object(cilinder);
    scene.add_object(plane);
    scene.add_object(plane2);
    scene.add_object(cone);
    //scene.add_object(malha);
    scene.add_light(spot_light);
    //scene.add_light(light);
    
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

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_PLUS:  // Tecla +
                    case SDLK_KP_PLUS:  // Tecla + do teclado numérico
                        canvas.aumentar_d();
                        break;

                    case SDLK_MINUS:  // Tecla -
                    case SDLK_KP_MINUS:  // Tecla - do teclado numérico
                        canvas.diminuir_d();
                        break;
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

    //delete cone;
    delete plane;
    delete plane2;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}