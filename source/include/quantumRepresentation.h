void renderWaveTrail(GLuint shaderProgram, GLuint VAO, const std::vector<unsigned int>& sphereIndices, float time) {
    glUseProgram(shaderProgram);

    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 9.0f, 0.0f));
    view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(fov * zoom), 800.0f / 600.0f, 0.1f, 100.0f);

    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
    GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    GLint ambientStrengthLoc = glGetUniformLocation(shaderProgram, "ambientStrength");

    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
    glUniform1f(ambientStrengthLoc, 0.6f);

    int numSpheres = 50;
    float sphereSpacing = 0.15f;

    for (int i = 0; i < numSpheres; ++i) {

        // sinusoidal wave

        float displacement = sin(2.0f * time - i * sphereSpacing);
        float normalizedPosition = (displacement + 0.1f) / 0.2f;
        glm::vec3 objectColor = glm::vec3(0.0f - normalizedPosition * 0.5, 0.0f, 0.8f);

        glUniform3fv(objectColorLoc, 1, glm::value_ptr(objectColor));

        float scaleFactor = (i == 0) ? 3.0f : 1.0f;

        // smooth effect
        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f * scaleFactor)) * glm::translate(glm::mat4(1.0f), glm::vec3(i * sphereSpacing, displacement / scaleFactor, 0.0f));

        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);
    }
}


void renderEntangledSpheres(GLuint shaderProgram, GLuint VAO, const std::vector<unsigned int>& sphereIndices, float time, glm::vec3 color1, glm::vec3 color2, float duration) {
    glUseProgram(shaderProgram);

    float animationDuration = 1.0f;
    float loopDuration = duration;

    // Adjust the view
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 9.0f, 0.0f));
    view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(fov * zoom), 800.0f / 600.0f, 0.1f, 100.0f);

    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");

    // Light
    GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
    GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    GLint ambientStrengthLoc = glGetUniformLocation(shaderProgram, "ambientStrength");

    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

    float displacement = 0.1f * sin(2.0f * time * animationDuration);
    float normalizedPosition = (displacement + 0.1f) / 0.2f;
    glm::vec3 objectColor = glm::vec3(1.0f - normalizedPosition, 0.0f, normalizedPosition);

    glUniform1f(ambientStrengthLoc, 0.6f);

    glm::vec3 positionSphere1 = glm::vec3(-2.0f + time * animationDuration, 1.0f, 0.0f);
    glm::vec3 positionSphere2 = glm::vec3(2.0f - time * animationDuration, 0.0f, 0.0f);

    glm::vec3 colorSphere1, colorSphere2;

    if (time < animationDuration) {
        float t = time / animationDuration;
        colorSphere1 = glm::mix(glm::vec3(color1[0], color1[1], color1[2]), glm::vec3(color2[0], color2[1], color2[2]), t);
        colorSphere2 = glm::mix(glm::vec3(color1[0], color1[1], color1[2]), glm::vec3(color2[0], color2[1], color2[2]), t);
    }
    else {
        colorSphere1 = glm::vec3(color1[0], color1[1], color1[2]);
        colorSphere2 = glm::vec3(color2[0], color2[1], color2[2]);
    }

    if(time > animationDuration * loopDuration)
        glfwSetTime(0);

    glUniform3fv(objectColorLoc, 1, glm::value_ptr(colorSphere1));
    glm::mat4 model1 = glm::translate(glm::mat4(1.0f), positionSphere1);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);

    glUniform3fv(objectColorLoc, 1, glm::value_ptr(colorSphere2));
    glm::mat4 model2 = glm::translate(glm::mat4(1.0f), positionSphere2);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);
}

void renderUniqueSphere(GLuint shaderProgram, GLuint VAO, const std::vector<unsigned int>& sphereIndices, glm::vec3 color) {
    glUseProgram(shaderProgram);

    // Set transformation matrices 
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 9.0f, 0.0f));
    view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(fov * zoom), 800.0f / 600.0f, 0.1f, 100.0f);

    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // uniform variables for lighting
    GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
    GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    GLint ambientStrengthLoc = glGetUniformLocation(shaderProgram, "ambientStrength");

    // values for lighting
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
    glUniform3f(objectColorLoc, color[0], color[1], color[2]);
    glUniform1f(ambientStrengthLoc, 0.2f);

    // Draw the sphere at the origin
    glm::mat4 model = glm::mat4(1.0f);
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);
}

void renderSuperpositionSphere(GLuint shaderProgram, GLuint VAO, const std::vector<unsigned int>& sphereIndices, float time, glm::vec3 color1, glm::vec3 color2) {
    glUseProgram(shaderProgram);

    // Set transformation matrices 
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 9.0f, 0.0f));
    view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(fov * zoom), 800.0f / 600.0f, 0.1f, 100.0f);

    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // uniform variables for lighting
    GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
    GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    GLint ambientStrengthLoc = glGetUniformLocation(shaderProgram, "ambientStrength");

    // values for lighting
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

    // link color and position
    float displacement = 0.1f * sin(2.0f * time);
    float normalizedPosition = (displacement + 0.1f) / 0.2f;
    glm::vec3 objectColor = glm::mix(color1, color2, normalizedPosition);

    glUniform3fv(objectColorLoc, 1, glm::value_ptr(objectColor));
    glUniform1f(ambientStrengthLoc, 0.6f);

    // smooth effect
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, displacement, 0.0f));

    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);
}


void heisenbergUncertainty(GLuint shaderProgram, GLuint VAO, const std::vector<unsigned int>& sphereIndices, float speedPrecision, glm::vec3 color, bool initializeAgain) {

    struct SpherePosition {
        float x, y;
    };

    static std::vector<SpherePosition> spherePositions;
    static bool initialized = false;

    // Initialize positions 
    if (!initialized) {
        srand(static_cast<unsigned int>(time(0)));
        int numSpheres = static_cast<int>(speedPrecision * 50);
        for (int i = 0; i < numSpheres; ++i) {
            float sphereX = static_cast<float>(rand()) / RAND_MAX * 10.0f - 5.0f;
            float sphereY = static_cast<float>(rand()) / RAND_MAX * 10.0f - 5.0f;
            spherePositions.push_back({ sphereX, sphereY });
        }
        initialized = true;
    }

    if (initializeAgain) {
        initialized = false;
        spherePositions.clear();
    }

    glUseProgram(shaderProgram);
    float time = glfwGetTime();

    for (size_t i = 0; i < spherePositions.size(); ++i) {
        SpherePosition& position = spherePositions[i];

        // subtle variations
        float variationX = static_cast<float>(rand()) / RAND_MAX * 0.01f - 0.005f;
        float variationY = static_cast<float>(rand()) / RAND_MAX * 0.01f - 0.005f;
        position.x += sin(time * 2.0f) * 0.01f + variationX;
        position.y += cos(time * 2.0f) * 0.01f + variationY;
    }

    glm::mat4 model = glm::mat4(1.0f);  

    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
    GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    GLint ambientStrengthLoc = glGetUniformLocation(shaderProgram, "ambientStrength");

    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

    glm::vec3 objectColor = glm::vec3(color[0], color[1], color[2]);

    glUniform3fv(objectColorLoc, 1, glm::value_ptr(objectColor));
    glUniform1f(ambientStrengthLoc, 0.6f);

    for (size_t i = 0; i < spherePositions.size(); ++i) {
        const SpherePosition& position = spherePositions[i];

        glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));

        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(translateMatrix));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);
    }
}

void renderQuantumTunneling(GLuint shaderProgram, GLuint VAO, const std::vector<unsigned int>& sphereIndices, float time) {
    glUseProgram(shaderProgram);

    float animationDuration = 1.0f;
    float loopDuration = 3.0f;

    //matrices 
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 9.0f, 0.0f));
    view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(fov * zoom), 800.0f / 600.0f, 0.1f, 100.0f);

    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    //lighting
    GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
    GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    GLint ambientStrengthLoc = glGetUniformLocation(shaderProgram, "ambientStrength");

    // values for lighting
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

    // Barrier & sphere
    glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f);
    glUniform1f(ambientStrengthLoc, 0.2f);
    glm::mat4 barrierModel = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 0.8f));
    GLuint barrierModelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(barrierModelLoc, 1, GL_FALSE, glm::value_ptr(barrierModel));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);

    glm::vec3 sphereColor = glm::vec3(1.0f, 0.0f, 0.0f);

    glUniform3fv(objectColorLoc, 1, glm::value_ptr(sphereColor));
    glUniform1f(ambientStrengthLoc, 0.6f);

    glm::mat4 sphereModel = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f , 0.0f, -2.0f + time * animationDuration));
    GLuint sphereModelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(sphereModelLoc, 1, GL_FALSE, glm::value_ptr(sphereModel));

    if (time > animationDuration * loopDuration)
        glfwSetTime(0);

    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);
}

