#include "porcupine.h"
#include "main.h"

Porcupine::Porcupine(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.01f;

    GLfloat vertex_buffer_data1[30] = {
        -0.2f, 0.3f, 0.0f,
        -0.3f, 0.0f, 0.0f,
        -0.1f, 0.0f, 0.0f,
        0.0f, 0.3f, 0.0f,
        -0.1f, 0.0f, 0.0f,
        0.1f, 0.0f, 0.0f,
        0.2f, 0.3f, 0.0f,
        0.3f, 0.0f, 0.0f,
        0.1f, 0.0f, 0.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data1, COLOR_PORCUPINE, GL_FILL);
}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::tick() {
  this->position.x += this->speed;
}

bounding_porcupine_t Porcupine::bounding_porcupine(){
  float x = this->position.x, y = this->position.y;
  bounding_porcupine_t bbox = { x, y};
  return bbox;
}
