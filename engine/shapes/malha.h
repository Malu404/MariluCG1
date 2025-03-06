#ifndef MALHA_H 
#define MALHA_H

#include "shape.h"
#include "triangulo.h"
#include "../../utils/vec3.h"
#include "material.h"
#include <array> 
#include <vector>
#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

class Malha : public Shape {
public:
    std::vector<Vec3> vertices;
    std::vector<std::array<int, 3>> faces;
    std::vector<Triangle> triangles;

    Malha(const std::string& filepath, Material mat) : Shape(mat) {
        load_obj(filepath);
        create_triangles();
    }

    void load_obj(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) throw std::runtime_error("Failed to open OBJ file: " + filepath);

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v") {
                double x, y, z;
                iss >> x >> y >> z;
                vertices.emplace_back(x, y, z);
            } else if (prefix == "f") {
                std::vector<int> faceIndices;
                std::string vertexData;
                while (iss >> vertexData) {
                    std::istringstream vertexStream(vertexData);
                    int vertexIndex;
                    vertexStream >> vertexIndex;
                    faceIndices.push_back(vertexIndex - 1);
                }
                faces.push_back(std::array<int, 3>{
                    faceIndices[0], 
                    faceIndices[1], 
                    faceIndices[2]
                });
            }
        }
    }

    void create_triangles() {
        for (const auto& face : faces) {
            triangles.emplace_back(vertices[face[0]], vertices[face[1]], vertices[face[2]], mat);
        }
    }

    inline Vec3 get_normal(Vec3 p) const override {
        // Implementação simplificada: retorna a normal do primeiro triângulo que contém o ponto p
        for (const auto& triangle : triangles) {
            if (triangle.contains(p)) {
                return triangle.get_normal(p);
            }
        }
        return Vec3(0, 0, 0); // Normal padrão se nenhum triângulo contém o ponto
    }
    /*inline Vec3 get_normal(Vec3 p) const override {
        double t_min = INFINITY;
        Vec3 normal_correta = Vec3(0, 0, 0);
    
        // Cria um raio partindo do ponto p em direção oposta à normal (para evitar self-shadowing)
        Ray raio = Ray(p + normal_correta * 1e-4, -normal_correta); 
    
        for (const auto& triangle : triangles) {
            double t = triangle.intersects(raio);
            if (t > 0 && t < t_min) {
                t_min = t;
                normal_correta = triangle.normal;
            }
        }
    
        return normal_correta;
    }*/
    

    double intersects(Ray r) const override {
        double t_min = INFINITY;
        for (const auto& triangle : triangles) {//tirei o const daqui antes do auto, nao sei se vai explodir o codigo 4/3/25 - 18:33
            double t = triangle.intersects(r);
            if (t > 0 && t < t_min) {
                t_min = t;
            }
        }
        return t_min == INFINITY ? -INFINITY : t_min;
    }
};

#endif