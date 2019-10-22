#include "background.h"
#include "main.h"

Background::Background(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data1[] = {
                    -4.0f, -4.0f, 0.0f,
                     4.0f, -4.0f, 0.0f,
                     4.0f,  -2.2f, 0.0f,
                     -4.0f, -2.2f, 0.0f,
                      4.0f,  -2.2f, 0.0f,
                      -4.0f, -4.0f, 0.0f
            };

    GLfloat vertex_buffer_data2[1000];

    int i,k;
    for(i=0;i<50;i++)
    {
            vertex_buffer_data2[9*i] = -2.2f;
            vertex_buffer_data2[9*i+1] = -2.2f;
            vertex_buffer_data2[9*i+2] = 0.0f;

            vertex_buffer_data2[9*i+3] = -0.7f*cos(i*3.14159/50) - 2.2f;
            vertex_buffer_data2[9*i+4] = -0.7f*sin(i*3.14159/50) - 2.2f;
            vertex_buffer_data2[9*i+5] = 0.0f;

            vertex_buffer_data2[9*i+6] = -0.7f*cos((i+1)*3.14159/50) - 2.2f;
            vertex_buffer_data2[9*i+7] = -0.7f*sin((i+1)*3.14159/50) - 2.2f;
            vertex_buffer_data2[9*i+8] = 0.0f;
    }

    GLfloat vertex_buffer_data3[1000];
    for(i=0;i<50;i++)
    {
            vertex_buffer_data3[9*i] = 2.0f;
            vertex_buffer_data3[9*i+1] = -2.2f;
            vertex_buffer_data3[9*i+2] = 0.0f;

            vertex_buffer_data3[9*i+3] = 0.3f*cos(i*3.14159/50) + 2.0f;
            vertex_buffer_data3[9*i+4] = 0.3f*sin(i*3.14159/50) - 2.2f;
            vertex_buffer_data3[9*i+5] = 0.0f;

            vertex_buffer_data3[9*i+6] = 0.3f*cos((i+1)*3.14159/50) + 2.0f;
            vertex_buffer_data3[9*i+7] = 0.3f*sin((i+1)*3.14159/50) - 2.2f;
            vertex_buffer_data3[9*i+8] = 0.0f;
    }

    static const GLfloat vertex_buffer_data4[] = {
                     1.65f, -1.85f, 0.0f,
                     2.35f, -1.85f, 0.0f,
                     2.35f,  -2.2f, 0.0f,
                     2.35f,  -2.2f, 0.0f,
                     1.65f, -2.2f, 0.0f,
                     1.65f, -1.85f, 0.0f,
    };

   static const GLfloat vertex_buffer_data5[] = {
          -3.0f, 3.295f, 0.0f,
          -2.75f, 3.295f, 0.0f,
          -3.0f, 3.15f, 0.0f,
          -2.75f, 3.295f, 0.0f,
          -3.0f, 3.15f, 0.0f,
          -2.75f, 3.15f, 0.0f,
          -3.0f, 2.85f, 0.0f,
          -2.75f, 2.85f, 0.0f,
          -3.0f, 2.7f, 0.0f,
          -2.75f, 2.85f, 0.0f,
          -3.0f, 2.7f, 0.0f,
          -2.75f, 2.7f, 0.0f
    };

    GLfloat vertex_buffer_data6[1000] = {0};
    for(i=25;i<75;i++)
    {
            vertex_buffer_data6[9*i] = -3.0f;
            vertex_buffer_data6[9*i+1] = 3.0f;
            vertex_buffer_data6[9*i+2] = 0.0f;

            vertex_buffer_data6[9*i+3] = 0.3f*cos(i*3.14159/50) - 3.0f;
            vertex_buffer_data6[9*i+4] = 0.3f*sin(i*3.14159/50) + 3.0f;
            vertex_buffer_data6[9*i+5] = 0.0f;

            vertex_buffer_data6[9*i+6] = 0.3f*cos((i+1)*3.14159/50) - 3.0f;
            vertex_buffer_data6[9*i+7] = 0.3f*sin((i+1)*3.14159/50) + 3.0f;
            vertex_buffer_data6[9*i+8] = 0.0f;
    }

    GLfloat vertex_buffer_data7[1000] = {0};
    for(i=25;i<75;i++)
    {
      vertex_buffer_data7[9*i] = -3.0f;
      vertex_buffer_data7[9*i+1] = 3.0f;
      vertex_buffer_data7[9*i+2] = 0.0f;

      vertex_buffer_data7[9*i+3] = 0.15f*cos(i*3.14159/50) - 3.0f;
      vertex_buffer_data7[9*i+4] = 0.15f*sin(i*3.14159/50) + 3.0f;
      vertex_buffer_data7[9*i+5] = 0.0f;

      vertex_buffer_data7[9*i+6] = 0.15f*cos((i+1)*3.14159/50) - 3.0f;
      vertex_buffer_data7[9*i+7] = 0.15f*sin((i+1)*3.14159/50) + 3.0f;
      vertex_buffer_data7[9*i+8] = 0.0f;
    }

    this->ground = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, COLOR_GROUND, GL_FILL);
    this->water = create3DObject(GL_TRIANGLES, 150, vertex_buffer_data2, COLOR_WATER, GL_FILL);
    this->trampoline1 = create3DObject(GL_TRIANGLES, 150, vertex_buffer_data3, COLOR_BACKGROUND, GL_FILL);
    this->trampoline2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data4, COLOR_TRAMPOLINE, GL_FILL);
    this->magnet1 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data5, COLOR_MAGNET, GL_FILL);
    this->magnet2 = create3DObject(GL_TRIANGLES, 225, vertex_buffer_data6, COLOR_RED, GL_FILL);
    this->magnet3 = create3DObject(GL_TRIANGLES, 225, vertex_buffer_data7, COLOR_BACKGROUND, GL_FILL);
}

void Background::draw(glm::mat4 VP, int level) {
  Matrices.model = glm::mat4(1.0f);
  glm::mat4 translate = glm::translate (this->position);    // glTranslatef
  glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
  rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
  Matrices.model *= (translate * rotate);
  glm::mat4 MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  draw3DObject(this->ground);
  draw3DObject(this->water);
  draw3DObject(this->trampoline2);
  draw3DObject(this->trampoline1);
  if(level > 2)
  {
    draw3DObject(this->magnet1);
    draw3DObject(this->magnet2);
    draw3DObject(this->magnet3);
  }
}

/*void Background::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}*/
