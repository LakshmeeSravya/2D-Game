#include<iostream>
#include <sstream>
#include <string>
#include "main.h"
#include "timer.h"
#include "ball.h"
#include "enemy.h"
#include "background.h"
#include "porcupine.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Enemy en[50];
Background back;
Porcupine po;
int flag = 0, i ,score = 0, val = -1, level = 1;


float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    back.draw(VP, level);
    if(level > 1)
    {
      po.draw(VP);
    }
    ball1.draw(VP);
    for(i = 0 ; i < 40 ; i++)
    {
        en[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window)
{
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);

    if(!left && !right && !up && ball1.position.x > -2.9f && ball1.position.x < -2.2f && ball1.position.y < -2.0f)
    {
      ball1.position.x += 0.01f;
      ball1.position.y = ball1.get_y();
      ball1.rotation -= (15/3.14159);
    }

    if(!left && !right && !up && ball1.position.x > -2.2f && ball1.position.x < -1.5f && ball1.position.y < -2.0f)
    {
      ball1.position.x -= 0.01f;
      ball1.position.y = ball1.get_y();
      ball1.rotation += (15/3.14159);
    }

    if(left && ball1.position.x >= -3.75f)
    {
      ball1.position.x -= 0.05f;
      ball1.rotation += (30/3.14159);
      if(ball1.position.y <= -2.0f && ball1.yspeed == 0.2)
      {
        ball1.position.y = ball1.get_y();
      }
    }

    if(right && ball1.position.x <= 3.75f)
    {
      ball1.position.x += 0.05f;
      ball1.rotation -= (30/3.14159);
      if(ball1.position.y <= -2.0f && ball1.yspeed == 0.2)
      {
        ball1.position.y = ball1.get_y();
      }
    }

    if((up && flag==0) || (ball1.position.y > ball1.get_y() && flag==1))
    {
      ball1.position.y += ball1.yspeed;
      if(up && !flag && ball1.position.x > -2.9f && ball1.position.x < -1.5f)
      {
        ball1.yspeed = 0.15f;
      }

        ball1.yspeed -= 0.01;
      flag = 1;
    }
    else
    {
      if(ball1.position.y < ball1.get_y() && ball1.yspeed == 0.2)
      {
          ball1.position.y = ball1.get_y();
      }
      flag = 0;
      ball1.yspeed = 0.2;
    }
}

void tick_elements() {
    ball1.tick();
    po.tick();
    if(po.position.x <= -1.0f || po.position.x >= 1.0f) {
       po.speed = -po.speed;
     }

    for(i = 0 ; i < 40 ; i++)
    {
      en[i].tick();
    }

    for(i = 0; i < 40 ; i++)
    {
      if(!en[i].slope && ball1.yspeed < 0 && detect_slope(ball1.bounding_box(), en[i].bounding_slope()))
      {
        val = 4;
        ball1.xspeed = 0.2f / tan(en[i].theta * 3.14159 / 180);
        ball1.yspeed = 0.2f;
        flag = 1;
      }
      else if(en[i].slope && detect_collision(ball1.bounding_box(), en[i].bounding_box()) && (ball1.yspeed < 0))
      {
          ball1.yspeed = 0.2;
          flag = 1;
          if(en[i].r < 0.13)
          {
            score += 15;
          }
          else if(en[i].r > 0.17)
          {
            score += 5;
          }
          else
          {
            score += 10;
          }

          en[i].position.x = rand() % 20 - 24.0f;
          en[i].position.y = (rand() % 3 - 1) + (rand() % 100) / 100.0;
          en[i].speed = (rand() % 20) / 1000.0 + 0.01;
      }
    }

    if(ball1.position.x >= 1.65f && ball1.position.x <= 2.35f && ball1.yspeed < 0 && ball1.position.y <= -1.65f && ball1.position.y >= -1.8f )
    {
        ball1.yspeed = 0.3f;
        flag = 1;
    }

    if(ball1.position.y > 2.7f && ball1.position.y < 3.3f && ball1.position.x > -2.6f && level > 2)
    {
      float a = ball1.position.x + 5.0f;
      ball1.xspeed -= a / 300;
    }
    else if(val < 0)
    {
      ball1.xspeed = 0;
    }
    val--;

    if(detect_collision_porcupine(ball1.bounding_box(), po.bounding_porcupine()) && level > 1)
    {
      score -= 20;
      ball1.position.x = 2.5f;
      ball1.position.y = ball1.get_y();
    }

    if(score < 50)
    {
      level = 1;
    }
    else if(score >= 50 && score < 100)
    {
      level = 2;
    }
    else if(score >= 100)
    {
      level = 3;
    }

    ostringstream str1, str2;
    str1 << score;
    str2 << level;
    string str = str1.str();
    string st = str2.str();
    string temp = "SCORE : " + str + "     LEVEL : " + st;

    glfwSetWindowTitle(window, temp.c_str());
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    double p, q, s;
    int slope, t, col;
    back = Background(0, 0);
    ball1 = Ball(2.5, -2, 0, 0.2);
    po = Porcupine(0, -2.2);
    for(i = 0 ; i < 40 ; i++)
    {
      col = rand() % 4;
      t = rand() % 8;
      p = rand() % 20 - 24.0f;
      q = (rand() % 3 - 1) + (rand() % 100) / 100.0;
      s = (rand() % 20) / 1000.0 + 0.01;
      en[i].r = (rand() %10) / 100.0 + 0.1001;
      if(t == 0)
      {
        slope = 0;
      }
      else
      {
        slope = 1;
      }
      if(col == 0)
      {
        en[i] = Enemy(en[i].r, (float)p, (float)q, s, slope, COLOR_ENEMY);
      }
      else if(col == 1)
      {
        en[i] = Enemy(en[i].r, (float)p, (float)q, s, slope, COLOR_YELLOW);
      }
      else if(col == 2)
      {
        en[i] = Enemy(en[i].r, (float)p, (float)q, s, slope, COLOR_BLUE);
      }
      else
      {
        en[i] = Enemy(en[i].r, (float)p, (float)q, s, slope, COLOR_GREEN);
      }
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b)
{
    return ((abs(a.x - b.x) < (a.r + b.r)) &&
            (0 < (a.y - b.y) <= (a.r + b.r)) &&
            ((a.r + 0.1)  < sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)) <= (a.r + b.r)));
}

bool detect_slope(bounding_box_t a, bounding_slope_t b)
{
  float m, x0, y0, y_cord, d1, d;
  m = tan(((90 + b.theta) * 3.14159) / 180);
  x0 = (b.r + 0.1f) * cos(b.theta * 3.14159 / 180) + b.x;
  y0 = (b.r + 0.1f) * sin(b.theta * 3.14159 / 180) + b.y;
  d1 = 0.4f / sqrt(1 + (m*m));
  d = abs((m * (a.x - x0)) - a.y + y0) / sqrt(1 + (m*m));
  return ((a.x >= x0 - d1 - 0.1) && (a.x <= x0 + d1 + 0.1) && (d >= 0.18f) && (d <= 0.22f));
}

bool detect_collision_porcupine(bounding_box_t a, bounding_porcupine_t b)
{
  return (((a.x <= b.x && a.x >= b.x - 0.4f) ||
          (a.x >= b.x && a.x <= b.x + 0.4f)) && a.y == -2.0f);
}

void reset_screen()
{
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
