#include "gr_interface.h"
#include "../WorkDB/data_base.h"
#include <math.h>
#include <algorithm>

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    std::cout << "Moeuse\n";
}

GrInterface::GrInterface(Client* client): client_(client) {  
  Init();
  glfwSetMouseButtonCallback(window_, mouse_button_callback);
  MakeShader();
  UpdateChatCoord();
  DrawChat();
  if (vertices_.size()) {
    ChangeVertex(&(vertices_[0]), &(indices_[0]), vertices_.size() / 6, indices_.size() / 3);
  }

  TextRender txt;
}

void GrInterface::PollEvents() {
  //GLuint uniID = glGetUniformLocation(shader_program_, "scale");
  while (!glfwWindowShouldClose(window_)){

    if (UpdateWindowData()) {
      UpdateChatCoord();
      DrawChat();
      if (vertices_.size()) {
        ChangeVertex(&(vertices_[0]), &(indices_[0]), vertices_.size() / 6, indices_.size() / 3);
      }
    }

    if (UpdateCursor()) {
      std::cout << cursor.x << " " << cursor.y << std::endl;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader_program_);
    //glUniform1f(uniID, 0.5f);
		glBindVertexArray(VAO_);
		glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
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

void GrInterface::AddRectangle(std::vector<Point<GLfloat>>&& rect, const std::vector<GLfloat>& color) {
  /*
  Вершины прямогульника должны быть указаны в следующем порядке:
      12
      03
  */
  for (size_t i = vertices_.size() / 6; i < vertices_.size() / 6 + 3; ++i) {
    indices_.push_back(i);
  }

  indices_.push_back(vertices_.size() / 6);
  indices_.push_back(vertices_.size() / 6 + 2);
  indices_.push_back(vertices_.size() / 6 + 3);

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
  const GLfloat standart_height = 150.0 / height_window_;
  std::vector<int> chat_id = client_->GetChat(height_window_ / 75 + 1, 0);
  chats_.clear();
  for (int i = 0; i < chat_id.size(); i++) {
    chats_.push_back({chat_id[i], 1.0f - i*standart_height, 1.0f - (i + 1)* standart_height});
  }
}

void GrInterface::DrawChat() {
  indices_.clear();
  vertices_.clear();
  for (int i = 0; i < chats_.size(); ++i) {
    if (i % 2 == 0) {
      AddRectangle({{-1.0f, chats_[i].down}, {-1.0f, chats_[i].top}, {-0.3f, chats_[i].top}, {-0.3f, chats_[i].down}}, dim_gray);
    } else {
      AddRectangle({{-1.0f, chats_[i].down}, {-1.0f, chats_[i].top}, {-0.3f, chats_[i].top}, {-0.3f, chats_[i].down}}, gray);
    }
  }
}

bool GrInterface::UpdateWindowData() {
  int width_window = width_window_;
  int height_window = height_window_;
  glfwGetWindowSize(window_, &width_window_, &height_window_);
  return (width_window != width_window_) || (height_window != height_window_);
}

bool GrInterface::UpdateCursor() {
  Point<double> cursor_old = cursor;
  glfwGetCursorPos(window_, &cursor.x, &cursor.y);
  return (cursor.x != cursor_old.x) || (cursor.y != cursor_old.y);
}

const std::vector<GLfloat> GrInterface::red = {1, 0, 0};
const std::vector<GLfloat> GrInterface::green = {0, 1, 0};
const std::vector<GLfloat> GrInterface::blue = {0, 0, 1};
const std::vector<GLfloat> GrInterface::dim_gray = {0.658824, 0.658824, 0.658824};
const std::vector<GLfloat> GrInterface::gray = {0.752941, 0.752941, 0.752941};