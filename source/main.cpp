#include <iostream>
#include <vector>
#include <sphere.h>
#include <shader.h>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "shader_config.h"
#include <camera.h>
#include "quantumRepresentation.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "QuantumEffects", nullptr, nullptr);
    if (!window) {
        std::cerr << "GLFW window creation failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD initialization failed" << std::endl;
        return -1;
    }

    // Vertex and fragment shader source code
    std::string vertexShaderSource = loadShaderSource("shaders/vertexShader.glsl");
    std::string fragmentShaderSource = loadShaderSource("shaders/fragmentShader.glsl");
    GLuint shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    // Create a sphere
    Sphere particle(0.1f, 500, 500);
    const std::vector<float>& sphereVertices = particle.getVertices();
    const std::vector<unsigned int>& sphereIndices = particle.getIndices();

    // Create and bind VAO, VBO, and EBO
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), sphereVertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(unsigned int), sphereIndices.data(), GL_STATIC_DRAW);

    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Set scroll callback function
    glfwSetScrollCallback(window, scroll_callback);

    // Set mouse callback functions
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Set key callback function
    glfwSetKeyCallback(window, key_callback);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // unique sphere
        //glm::mat4 model = glm::mat4(1.0f);
        //renderUniqueSphere(shaderProgram, VAO, sphereIndices);

        // Render superposition state
        //renderSuperpositionSphere(shaderProgram, VAO, sphereIndices, glfwGetTime());

        //renderEntangledSpheres(shaderProgram, VAO, sphereIndices, glfwGetTime());

        //renderWaveTrail(shaderProgram, VAO, sphereIndices, glfwGetTime());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup and exit
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

