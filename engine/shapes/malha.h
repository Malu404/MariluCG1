#ifndef MALHA_H 
#define MALHA_H

#include "cilinder.h"
#include "../../utils/matriz4x4.h"
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
    Vec3 centroid;
    Vec3 min_point;
    Vec3 max_point;

    Malha(const std::string& filepath, Material mat) : Shape(mat) {
        load_obj(filepath);
        create_triangles();
        calculate_bounding_box(); // Calcula a caixa delimitadora inicial
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
        for (const auto& triangle : triangles) {
            if (triangle.contains(p)) {
                return triangle.get_normal(p);
            }
        }
        return Vec3(0, 0, 0); // Normal padrão se nenhum triângulo contém o ponto
    }

    double intersects(Ray r) const override {
        double t_min = INFINITY;
        for (const auto& triangle : triangles) {
            double t = triangle.intersects(r);
            if (t > 0 && t < t_min) {
                t_min = t;
            }
        }
        return t_min == INFINITY ? -INFINITY : t_min;
    }

    void calculate_bounding_box() {
        min_point = Vec3(INFINITY, INFINITY, INFINITY);
        max_point = Vec3(-INFINITY, -INFINITY, -INFINITY);
        for (const Vec3& vertex : vertices) {
            min_point.x = std::min(vertex.x, min_point.x);
            min_point.y = std::min(vertex.y, min_point.y);
            min_point.z = std::min(vertex.z, min_point.z);

            max_point.x = std::max(vertex.x, max_point.x);
            max_point.y = std::max(vertex.y, max_point.y);
            max_point.z = std::max(vertex.z, max_point.z);
        }
    }

    // Aplica uma transformação a todos os vértices da malha
    void transform(const Matrix4x4& transformation_matrix) {
        for (Vec3& vertex : vertices) {
            vertex = transformation_matrix * vertex;
        }
        // Atualiza os triângulos com os novos vértices transformados
        create_triangles();
        // Recalcula a caixa delimitadora
        calculate_bounding_box();
    }

    // Função alternativa para aplicar transformações
    void apply_transform(const Matrix4x4& transformation_matrix) {
        transform(transformation_matrix); // Reutiliza a função transform
    }
};

#endif