#pragma once
#define GLFW_INCLUDE_NONE
#include "./glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "../Client/client.h"

template <typename T>
struct Point {
  T x = 0.0f;
  T y = 0.0f;
  Point() = default;
  Point(T x, T y): x(x), y(y) {}
};

struct ChatCoord {
  int id_chat;
  GLfloat top;
  GLfloat down;
};

class GrInterface {
 private:
  Client* client_;
  std::vector<ChatCoord> chats_;

  int height_window_ = 640;
  int width_window_ = 480;
  int scale = 1;
  Point<double> cursor;

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
  void AddRectangle(std::vector<Point<GLfloat>>&& rect, const std::vector<GLfloat>& color);
  void DrawChat();

  void UpdateChatCoord();
  bool UpdateWindowData();
  bool UpdateCursor();

 public:
  GrInterface(Client* client);
  ~GrInterface();
  void PollEvents();

 private:
  const static std::vector<GLfloat> red;
  const static std::vector<GLfloat> green;
  const static std::vector<GLfloat> blue;
  const static std::vector<GLfloat> dim_gray;
  const static std::vector<GLfloat> gray;
};

class TextRender {
 private:
 public:
  TextRender();
  ~TextRender();
};