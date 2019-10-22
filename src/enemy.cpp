#include "enemy.h"
#include "main.h"

Enemy::Enemy(float r, float x, float y, double speed, int slope, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = speed;
    this->r = r;
    this->slope = slope;
    this->theta = 0;

    GLfloat vertex_buffer_data1[1000];
    int i,k;
    for(i=0;i<100;i++)
    {
            for(k=9*i;k<9*i+3;k++)
              vertex_buffer_data1[k]=0.0f;

            vertex_buffer_data1[9*i+3]=r*cos(i*3.14159/50);
            vertex_buffer_data1[9*i+4]=r*sin(i*3.14159/50);
            vertex_buffer_data1[9*i+5]=0.0f;

            vertex_buffer_data1[9*i+6]=r*cos((i+1)*3.14159/50);
            vertex_buffer_data1[9*i+7]=r*sin((i+1)*3.14159/50);
            vertex_buffer_data1[9*i+8]=0.0f;
    }

    this->object1 = create3DObject(GL_TRIANGLES, 300, vertex_buffer_data1, color, GL_FILL);


    float x1, x2, y1, y2, m, d1, d2;
    if(this->slope == 0)
    {
      this->theta = rand()%90 + 45;
      m = tan(((90 + this->theta) * 3.14159) / 180);
      x1 = this->r * cos(this->theta * 3.14159 / 180);
      y1 = this->r * sin(this->theta * 3.14159 / 180);
      x2 = (this->r + 0.1f) * cos(this->theta * 3.14159 / 180);
      y2 = (this->r + 0.1f) * sin(this->theta * 3.14159 / 180);
      d1 = 0.4f / sqrt(1 + (m*m));
      d2 = d1 * m;
      GLfloat vertex_buffer_data2[] = {
                       x2 + d1, y2 + d2, 0.0f,
                       x2 - d1, y2 - d2, 0.0f,
                       x1 - d1, y1 - d2, 0.0f,
                       x1 + d1, y1 + d2, 0.0f,
                       x1 - d1, y1 - d2, 0.0f,
                       x2 + d1, y2 + d2, 0.0f
                  };
      this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_SLOPE, GL_FILL);
    }
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    if(this->slope == 0)
    {
      draw3DObject(this->object2);
    }
}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy::tick() {
    this->position.x += this->speed;
    if(this->position.x > 4.3)
    {
      //this->r = (rand() %10) / 100.0 + 0.1001;
      this->position.x = rand() % 20 - 24.0f;
      this->position.y = (rand() % 3 - 1) + (rand() % 100) / 100.0;
      this->speed = (rand() % 20) / 1000.0 + 0.01;
    }
}

bounding_box_t Enemy::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float r = this->r;
    bounding_box_t bbox = { x, y, r};
    return bbox;
}

bounding_slope_t Enemy::bounding_slope(){
  float x = this->position.x, y = this->position.y;
  float r = this->r;
  float theta = this->theta;
  bounding_slope_t bbox = { x, y, r, theta};
  return bbox;
}
