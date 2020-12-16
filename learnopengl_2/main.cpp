#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "Shader.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

const char *vertexShaderSource ="#version 330 core\n"
                                "layout (location = 0) in vec3 aPos;\n"
                                "uniform float hOffset;\n"
                                "out vec3 fPos;\n"
                                "void main()\n"
                                "{\n"
                                "   gl_Position = vec4(aPos.x + hOffset, -aPos.y, aPos.z, 1.0);\n"
                                "   fPos = vec3(aPos.x + hOffset, -aPos.y, aPos.z);\n"
                                "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "in vec3 fPos;\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(fPos, 1.0);\n"
                                   "}\n\0";
int main() {
    // Initialization
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "LearnOpenGL_1", NULL, NULL);
    if (window == nullptr) {
        std::cerr << "Main window creation failed!, exiting!";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    framebufferSizeCallback(window, 1920, 1080);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    Shader shader(vertexShaderSource, fragmentShaderSource);

    /* Setup Triangle */
    float vertices[] = {
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f   // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.5f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        float time = glfwGetTime();

        float greenValue = sin(time);

        shader.setFloat("hOffset", -0.5f);
        GLint vertexColorLoc = glGetUniformLocation(shader.shaderProgram, "ourColor");
        glUniform4f(vertexColorLoc, 0.0f, greenValue, 0.0f, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}