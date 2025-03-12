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

    void transform(Matriz4x4 m) override {
        for (Triangle& triangle : triangles) {
            triangle.transform(m);
        }
    }

    void load_obj(const std::string& filepath) {
        std::ifstream file(filepath);
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;
    
            if (prefix == "v") { // Vertex
                Vec3 vertex;
                iss >> vertex.x >> vertex.y >> vertex.z;
                vertices.push_back(vertex);
            } else if (prefix == "f") { // Face
                int vertexIndex[3];
                for (int i = 0; i < 3; ++i) {
                    iss >> vertexIndex[i];
                    vertexIndex[i]--; // OBJ indices are 1-based, convert to 0-based
                    if (iss.peek() == '/') {
                        iss.ignore(256, ' '); // Ignore texture and normal indices
                    }
                }
                faces.push_back({vertexIndex[0], vertexIndex[1], vertexIndex[2]});
            }
        }
        file.close();
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