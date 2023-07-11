#define GLFW_INCLUDE_NONE
#include "./glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>


class GrInterface {
 private:
  GLFWwindow* window;
 
 public:
  GrInterface() {
    if (!glfwInit()) {
      throw std::logic_error("Glfw init fail");
    }

    if(!(window = glfwCreateWindow(640, 480, "Messanger", NULL, NULL))) {
      glfwTerminate();
      throw std::logic_error("Windows create fail");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      throw std::logic_error("Failed to initialize GLAD");
    }
  }

  void PollEvents() {
    while (!glfwWindowShouldClose(window)){
        /* Render here*/
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers*/
        glfwSwapBuffers(window);

        /* Poll for and process events*/
        glfwPollEvents();
    }
  }

  ~GrInterface() {
    glfwTerminate();
  }  
};