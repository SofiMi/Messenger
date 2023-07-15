#include "gr_interface.h"
#include "../WorkDB/data_base.h"
#include <math.h>
#include <algorithm>

GrInterface::GrInterface() {  
  Init();
  MakeShader();
  if (vertices_.size()) {
    ChangeVertex(&(vertices_[0]), &(indices_[0]), vertices_.size() / 6, indices_.size() / 3);
  }
}

void GrInterface::PollEvents() {
  //GLuint uniID = glGetUniformLocation(shader_program_, "scale");
  while (!glfwWindowShouldClose(window_)){
    UpdateWindowData();
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader_program_);
    //glUniform1f(uniID, 0.5f);
		glBindVertexArray(VAO_);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}

GrInterface::~GrInterface() {
  glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
	glDeleteBuffers(1, &EBO_);
	glDeleteProgram(shader_program_);
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void GrInterface::Init() {
  if (!glfwInit()) {
    throw std::logic_error("Glfw init fail");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if(!(window_ = glfwCreateWindow(height_window_, width_window_, "Messanger", NULL, NULL))) {
    glfwTerminate();
    throw std::logic_error("Windows create fail");
  }

  glfwSetWindowSizeCallback(window_, [](GLFWwindow* pWindow, int width, int height) 
                                      {
                                        glViewport(0, 0, width, height);
                                      }
                            );

  /* Make the window's context current */
  glfwMakeContextCurrent(window_);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::logic_error("Failed to initialize GLAD");
  }

  DrawChat();
}

void GrInterface::MakeShader() {
  const char* vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aColor;\n"
  "out vec3 color;\n"
  "uniform float scale;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);\n"
	"   color = aColor;\n"
  "}\0";

  
  //Fragment Shader source code
  const char* fragmentShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "in vec3 color;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(color, 1.0f);\n"
  "}\n\0";

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shader_program_ = glCreateProgram();
	glAttachShader(shader_program_, vertexShader);
	glAttachShader(shader_program_, fragmentShader);
	glLinkProgram(shader_program_);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void GrInterface::ChangeVertex(GLfloat* vertices, GLuint* indices, size_t count_v, size_t count_tr) {
  glGenVertexArrays(1, &VAO_);
  glBindVertexArray(VAO_);

  glGenBuffers(1, &VBO_);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*count_v, vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*count_tr, indices, GL_STATIC_DRAW);

  glBindVertexArray(VAO_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  glBindVertexArray(VAO_);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),  (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
  glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GrInterface::AddRectangle(std::vector<Point>&& rect, const std::vector<GLfloat>& color) {
  /*
  Вершины прямогульника должны быть указаны в следующем порядке:
      12
      03
  */

  for (size_t i = vertices_.size(); i < vertices_.size() + 3; ++i) {
    indices_.push_back(i);
  }

  indices_.push_back(vertices_.size());
  indices_.push_back(vertices_.size() + 2);
  indices_.push_back(vertices_.size() + 3);

  for (int i = 0; i < 4; ++i) {
    vertices_.push_back(rect[i].x);
    vertices_.push_back(rect[i].y);
    vertices_.push_back(0.0f);
    vertices_.push_back(color[0]);
    vertices_.push_back(color[1]);
    vertices_.push_back(color[2]);
  }
}


void GrInterface::UpdateChatCoord() {
  
}

void GrInterface::DrawChat() {
  for (int i = 0; i < chats_.size(); ++i) {
    if (i % 2 == 0) {
      AddRectangle({{-1.0f, chat[i].down}, {-1.0f, chat[i].top}, {-0.3f, chat[i].top}, {-0.3f, chat[i].down}}, red);
    } else {
      AddRectangle({{-1.0f, chat[i].down}, {-1.0f, chat[i].top}, {-0.3f, chat[i].top}, {-0.3f, chat[i].down}}, green);
    }
  }
}

void GrInterface::UpdateWindowData() {
  glfwGetWindowSize(window_, &width_window_, &height_window_);
}

const std::vector<GLfloat> GrInterface::red = {1, 0, 0};
const std::vector<GLfloat> GrInterface::green = {0, 1, 0};
const std::vector<GLfloat> GrInterface::blue = {0, 0, 1};

const GrInterface::Point GrInterface::top_l = {-1, 1};
const GrInterface::Point GrInterface::top_r = {1, 1};
const GrInterface::Point GrInterface::down_l = {-1, -1};
const GrInterface::Point GrInterface::down_r = {1, -1};