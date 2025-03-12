#ifndef PICK_HPP
#define PICK_HPP

#include "scene.h"
#include "canvas.h"
#include "intersection.hpp"

// Função pick: lança um raio e retorna o objeto colidido (se houver)
Object* pick(Canvas& camera, Scene& scene, int mouseX, int mouseY);

#endif // PICK_HPP