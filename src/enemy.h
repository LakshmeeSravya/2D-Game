#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float r, float x, float y,double speed,int slope, color_t color);
    glm::vec3 position;
    float rotation, theta, r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int slope;
    bounding_box_t bounding_box();
    bounding_slope_t bounding_slope();
private:
    VAO *object1;
    VAO *object2;
};

#endif // ENEMY_H
