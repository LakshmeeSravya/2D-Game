#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, double xspeed, double yspeed) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->xspeed = xspeed;
    this->yspeed = yspeed;

    GLfloat vertex_buffer_data[8][400];
    int i,j=1,k,l=0;
    for(i=0;i<120;i++)
    {
      if(i%20 == 0 && i!=0)
      {
         j++;
         l=0;
      }

      for(k=9*l;k<9*l+3;k++)
            vertex_buffer_data[j][k]=0.0f;

            vertex_buffer_data[j][9*l+3]=0.2*cos(i*3.14159/60);
            vertex_buffer_data[j][9*l+4]=0.2*sin(i*3.14159/60);
            vertex_buffer_data[j][9*l+5]=0.0f;

            vertex_buffer_data[j][9*l+6]=0.2*cos((i+1)*3.14159/60);
            vertex_buffer_data[j][9*l+7]=0.2*sin((i+1)*3.14159/60);
            vertex_buffer_data[j][9*l+8]=0.0f;
            l++;
    }

    this->object1 = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data[1], COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data[2], COLOR_ORANGE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data[3], COLOR_YELLOW, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data[4], COLOR_GREEN, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data[5], COLOR_BLUE, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data[6], COLOR_VIOLET, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1)); //draw something else in the circle so that it looks like rotating
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

float Ball::get_y()
{
    if((this->position.x > -2.9f && this->position.x < -2.7f) || (this->position.x > -1.7f && this->position.x < -1.5f))
    {
      return -2.2f;
    }
    else if((this->position.x >= -2.7f) && (this->position.x <= -1.7f))
    {
      return (-1.0f * (sqrt(0.25f - pow(this->position.x + 2.2f, 2)))) - 2.2f;
    }
    /*else if(this->position.x >= 1.65f && this->position.x <= 2.35f)
    {
      return -1.75f;
    }*/
    else if(this->position.x <= -2.9f || this->position.x >= -1.5f)
    {
      return -2.0f;
    }
}

void Ball::tick() {
  this->position.x += this->xspeed;
  if(this->position.x > 3.75f)
  {
    this->position.x = 3.75f;
  }
  if(this->position.x < -3.75f)
  {
    this->position.x = -3.75f;
  }
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    double r = 0.2;
    bounding_box_t bbox = { x, y, r};
    return bbox;
}
