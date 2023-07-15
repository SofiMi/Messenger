#include "gr_interface.h"
#include <math.h>

GrInterface::GrInterface() {  
  Init();
  MakeShader();
  std::vector<GLfloat> vertices =
  { //               COORDINATES                  /     COLORS           //
   -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
   -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
   0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
   0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  };

  // Indices for vertices order
  std::vector<GLuint> indices =
  {
    0, 1, 3,
    0, 2, 3
  };
  ChangeVertex(&(vertices[0]), &(indices[0]), 4, 2);
}

void GrInterface::PollEvents() {
  GLuint uniID = glGetUniformLocation(shader_program_, "scale");
  while (!glfwWindowShouldClose(window_)){
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

  if(!(window_ = glfwCreateWindow(hight_window_, weigh_window_, "Messanger", NULL, NULL))) {
    glfwTerminate();
    throw std::logic_error("Windows create fail");
  }

  glfwSetWindowSizeCallback(window_, [](GLFWwindow* pWindow, int width, int height) {glViewport(0, 0, width, height);});

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
