#pragma once
#define GLFW_INCLUDE_NONE
#include "./glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

struct Point {
  GLfloat x;
  GLfloat y;
  Point(GLfloat x, GLfloat y): x(x), y(y) {}
};

struct ChatCoord {
  int id_chat;
  GLfloat top;
  GLfloat down;
}

class GrInterface {
 private:
  std::vector<ChatCoord> chats_;
  int height_window_ = 640;
  int width_window_ = 480;

  std::vector<GLfloat> vertices_;
  std::vector<GLuint> indices_;

  GLFWwindow* window_;
  GLuint shader_program_;
  GLuint VAO_;
  GLuint VBO_;
  GLuint EBO_;

  void Init();
  void MakeShader();
  void ChangeVertex(GLfloat* vertices, GLuint* indices, size_t count_v, size_t count_tr);
  void AddRectangle(std::vector<Point>&& rect, const std::vector<GLfloat>& color);
  void DrawChat(const std::vector<int>& chat_id);
  void UpdateWindowData();

  const static std::vector<GLfloat> red;
  const static std::vector<GLfloat> green;
  const static std::vector<GLfloat> blue;
  const static Point top_l;
  const static Point top_r;
  const static Point down_l;
  const static Point down_r;

  int user_id_ = 1;
  int max_count_chat_ = 6;
 public:
  GrInterface();
  ~GrInterface();
  void PollEvents();
};