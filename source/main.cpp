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
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

    // logo

    int logoWidth, logoHeight, logoChannels;
    unsigned char* logoPixels = stbi_load("logo.png", &logoWidth, &logoHeight, &logoChannels, 4);


    GLFWimage icons[1];
    icons[0].width = logoWidth;
    icons[0].height = logoHeight;
    icons[0].pixels = logoPixels;

    glfwSetWindowIcon(window, 1, icons);
    stbi_image_free(logoPixels);

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

    // Initialize Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // settings
    glm::vec3 colorPicked = glm::vec3(0.8f, 0.f, 0.8f);
    glm::vec3 color1 = glm::vec3(1.0f, 0.f, 0.0f);;
    glm::vec3 color2 = glm::vec3(0.0f, 0.f, 1.0f);;
    float mesurePrecisionOnSpeed = 1.0f;

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Render functions");

        struct ImGuiParameterState
        {
            int selected_radio;
        };

        static ImGuiParameterState state;

        ImGui::RadioButton("Simple Particle", &state.selected_radio, 0);
        ImGui::RadioButton("Quantum Spin", &state.selected_radio, 1);
        ImGui::RadioButton("Uncertainty Principle", &state.selected_radio, 2);
        ImGui::RadioButton("Quantum Superposition", &state.selected_radio, 3);
        ImGui::RadioButton("Quantum Entaglement", &state.selected_radio, 4);
        ImGui::RadioButton("Quantum Tunneling", &state.selected_radio, 5);
        ImGui::RadioButton("Wave-Particle Duality", &state.selected_radio, 6);
        ImGui::End();;
        ImGui::Begin("Options");

        if (state.selected_radio == 0) {
            // unique sphere
            glm::mat4 model = glm::mat4(1.0f);
            renderUniqueSphere(shaderProgram, VAO, sphereIndices, colorPicked);

            ImGui::Text("Select Color:");
            ImGui::ColorEdit3("Color", (float*)&colorPicked);
        }

        if (state.selected_radio == 1) {
            // Quantum Spin
            glm::mat4 model = glm::mat4(1.0f);
            renderUniqueSphere(shaderProgram, VAO, sphereIndices, colorPicked);
            ImGui::Text("Select Color:");
            ImGui::ColorEdit3("Color", (float*)&colorPicked);
            float cameraRotationSpeed = 0.4;
            float cameraRotationX = sin(glfwGetTime()) * cameraRotationSpeed;
            float cameraRotationY = cos(glfwGetTime()) * cameraRotationSpeed;
            cameraPosition = glm::vec3(cameraRotationX, cameraRotationY, 1.0f);
        }

        if (state.selected_radio == 2) {
                bool initializeAgain = false;
            if (ImGui::SliderFloat("Mesure Precision on Speed", &mesurePrecisionOnSpeed, 0.0001, 10, "%.5f")) {
                initializeAgain = true;
            }
            ImGui::Text("Select Color:");
            ImGui::ColorEdit3("Color", (float*)&colorPicked);
            heisenbergUncertainty(shaderProgram, VAO, sphereIndices, mesurePrecisionOnSpeed, colorPicked, initializeAgain);
        }

        if (state.selected_radio == 3) {
            // Render superposition state
            glm::mat4 model = glm::mat4(1.0f);

            ImGui::Text("Select Color 1:");
            ImGui::ColorEdit3("Color1", (float*)&color1);

            ImGui::Text("Select Color 2:");
            ImGui::ColorEdit3("Color2", (float*)&color2);

            glm::vec3 colorMix ((color1[0] / 2 + color2[0] / 2), (color1[1] / 2 + color2[1] / 2), (color1[2] / 2 + color2[2] / 2));
            renderUniqueSphere(shaderProgram, VAO, sphereIndices, colorMix);
            renderSuperpositionSphere(shaderProgram, VAO, sphereIndices, glfwGetTime(), color1, color2);
        }

        if (state.selected_radio == 4) {
            renderEntangledSpheres(shaderProgram, VAO, sphereIndices, glfwGetTime());
        }

        if (state.selected_radio == 5) {
            renderQuantumTunneling(shaderProgram, VAO, sphereIndices, glfwGetTime());
        }

        if (state.selected_radio == 6) {
            renderWaveTrail(shaderProgram, VAO, sphereIndices, glfwGetTime());
        }

        if (ImGui::Button("Reset camera")) {
            yaw = -90.0f;
            pitch = 10.0f;
            zoom = 1.0f;
            cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
        }

        ImGui::End();;

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup and exit
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

