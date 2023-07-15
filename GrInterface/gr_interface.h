#pragma once
#define GLFW_INCLUDE_NONE
#include "./glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

class GrInterface {
 private:
  size_t hight_window_ = 640;
  size_t weigh_window_ = 480; 
  GLFWwindow* window_;

  GLuint shader_program_;
  GLuint VAO_;
  GLuint VBO_;
  GLuint EBO_;

  void Init();
  void MakeShader();
  void NewBuffer(GLfloat* point, GLfloat* colors, size_t count);
  void ChangeVertex(GLfloat* vertices, GLuint* indices, size_t count_v, size_t count_tr);

 
 public:
  GrInterface();
  ~GrInterface();
  void PollEvents();
};