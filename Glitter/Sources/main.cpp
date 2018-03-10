// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

// Standard Headers
#include <cstdio>
#include <cstdlib>

GLfloat vertices[] = {
  -1.0f,1.0f,0.0f, //top left corner
  -1.0,-1.0f,0.0f, //bottom left corner
   1.0f,-1.0f,0.0f, //bottom right
    1.0f,1.0f,0.0f, //top right
    0.0f,0.0f,0.0f //middle
   
};

//indices used for EBO to avoid repeating vertices
GLuint indices[] = {
   0,1,2,
    0,3,2
};


int main(int argc, char * argv[]) {
  
  // Load GLFW and Create a Window
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  auto mWindow = glfwCreateWindow(600, 800, "OpenGL", nullptr, nullptr);
  
  // Check for Valid Context
  if (mWindow == nullptr) {
    fprintf(stderr, "Failed to Create OpenGL Context");
    return EXIT_FAILURE;
  }
  
  // Create Context and Load OpenGL Functions
  glfwMakeContextCurrent(mWindow);
  gladLoadGL();
  fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
  
  // vertex array object stores vertex attribute information
  // stores subsequent calls to glVertexAttribPointer, glEnableVertexAttribArray, vbos associated
  // with vertex attributes
  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1,&VBO);
  glGenBuffers(1,&EBO);
    
  glBindVertexArray(VAO);
  
  // vertex buffer object stores large number of vertices on GPU
  glBindBuffer(GL_ARRAY_BUFFER, VBO);   // this is going to be your GL_ARRAY_BUFFER
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // copy vertex data into buffer
  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    
    
  // this is the first (0th) vertex attribute, has 3 components, is of type GL_FLOAT, should
  // not be normalized, each one is 3 floats apart, start at beginning of buffer (offset is 0)
  // this vertex attribute takes its data from the VBO currently bound to GL_ARRAY_BUFFER
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  
  // unbind GL_ARRAY_BUFFER and vertex array -- state has been applied
  // unbind OpenGL objects when finished configuring them so don't mess them up
  glBindBuffer(GL_ARRAY_BUFFER, 0); 
  glBindVertexArray(0);
  
  Shader ourShader("/Users/pgringer/openGLexperiments/Glitter/Sources/shader.vs", "/Users/pgringer/openGLexperiments/Glitter/Sources/fragment.fs");

  // Rendering Loop
  while (glfwWindowShouldClose(mWindow) == false) {
    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(mWindow, true);
    
    // Background Fill Color
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw our first triangle
    ourShader.use();
    glBindVertexArray(VAO);     // bind the VAO we configured before
    glDrawElements(GL_TRIANGLE_FAN, 9, GL_UNSIGNED_INT, 0);   // draw the objects
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // unbind the VAO

    glfwSwapBuffers(mWindow);   // flip buffers and draw
    glfwPollEvents();           // check if any events are triggered, call corresponding callbacks
  }
  
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1,&EBO);
  glfwTerminate();
  
  return EXIT_SUCCESS;
}
