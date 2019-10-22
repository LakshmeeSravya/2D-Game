#include "main.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background{
public:
  Background(){};
  Background(float x, float y);
  glm::vec3 position;
  float rotation;
  void tick();
  void draw(glm::mat4 VP, int level);
private:
    VAO *ground;
    VAO *water;
    VAO *trampoline1;
    VAO *trampoline2;
    VAO *magnet1;
    VAO *magnet2;
    VAO *magnet3;
};

#endif
