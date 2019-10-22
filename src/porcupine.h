#include "main.h"

#ifndef PORCUPINE_H
#define PORCUPINE_H

class Porcupine{
public:
  Porcupine(){};
  Porcupine(float x, float y);
  glm::vec3 position;
  float rotation, speed;
  void tick();
  void draw(glm::mat4 VP);
  bounding_porcupine_t bounding_porcupine();
private:
    VAO *object;
};

#endif
