#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

unsigned int compileShader(std::string path, GLenum type);
void createProgram(unsigned int vShader, unsigned int fShader);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void render(double dt);
void drawTriangle();

unsigned int programs[2];
GLuint VAOs[2];

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

    try {
        unsigned int vI = compileShader("main.vert", GL_VERTEX_SHADER);
        unsigned int fI = compileShader("main.frag", GL_FRAGMENT_SHADER);
        createProgram(vI, fI);

        vI = compileShader("main.vert", GL_VERTEX_SHADER);
        fI = compileShader("sec.frag", GL_FRAGMENT_SHADER);
        createProgram(vI, fI);

        glDeleteShader(vI);
        glDeleteShader(fI);
    } catch (std::runtime_error &runtime_error) {
        std::cerr << runtime_error.what();
        glfwTerminate();
        return -1;
    }

    framebufferSizeCallback(window, 1920, 1080);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    /* Setup Triangle */
    float vertices[2][9] = {
        {-0.9f, -0.5f, 0.0f,
        -0.0f, -0.5f, 0.0f,
        -0.45f, 0.5f, 0.0f},

        {0.0f, -0.5f, 0.0f,
        0.9f, -0.5f, 0.0f,
        0.45f, 0.5f, 0.0f}
    };

    GLuint VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    for (int i = 0; i < 2; i++) {
        glBindVertexArray(VAOs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    double lastTime = glfwGetTime(), currentTime = 0;
    double deltaTime = 0;
    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glfwGetTime();
        render(deltaTime);
//        std::cout << (1.0f / deltaTime) << "\n"; // fps

        glfwSwapBuffers(window);
        glfwPollEvents();
        glGetError();
    }

    glfwTerminate();
    return 0;
}

unsigned int compileShader(std::string path, GLenum type) {
    path = "shaders/" + path;
    std::ifstream ifs(path);
    const char * shaderContent;

    if(ifs.fail()) {
        throw std::runtime_error("failed to read " + path);
    }
    std::ostringstream ss;
    ss << ifs.rdbuf();
    std::string tmp = ss.str();
    shaderContent = tmp.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderContent, NULL);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << path << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("failed to compile shader");
    }

    return shader;
}

unsigned int programCount = 0;

void createProgram(unsigned int vShader, unsigned int fShader) {
    programs[programCount] = glCreateProgram();
    glAttachShader(programs[programCount], vShader);
    glAttachShader(programs[programCount], fShader);
    glLinkProgram(programs[programCount]);

    int  success;
    char infoLog[512];
    glGetProgramiv(programs[programCount], GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(programs[programCount], 512, nullptr, infoLog);
        std::cout << "Program::CREATION_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("failed to create program");
    }

    programCount++;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void render(double dt) {
    glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawTriangle();
}

void drawTriangle() {
    glUseProgram(programs[0]);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(programs[1]);
    int timeLocation = glGetUniformLocation(programs[1], "time");
    glUniform1f(timeLocation, glfwGetTime());
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}