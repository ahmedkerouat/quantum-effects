void renderEntangledSpheres(GLuint shaderProgram, GLuint VAO, const std::vector<unsigned int>& sphereIndices, float time) {
    glUseProgram(shaderProgram);

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

    float displacement = 0.1f * sin(2.0f * time);
    float normalizedPosition = (displacement + 0.1f) / 0.2f;
    glm::vec3 objectColor = glm::vec3(1.0f - normalizedPosition, 0.0f, normalizedPosition);

    glUniform1f(ambientStrengthLoc, 0.6f);

    glm::vec3 positionSphere1 = glm::vec3(-2.0f + time, 1.0f, 0.0f);
    glm::vec3 positionSphere2 = glm::vec3(2.0f - time, 0.0f, 0.0f);

    glm::vec3 colorSphere1, colorSphere2;

    float animationDuration = 1.0f;

    if (time < animationDuration) {
        float t = time / animationDuration;
        colorSphere1 = glm::mix(glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.5f, 0.0f, 0.5f), t);
        colorSphere2 = glm::mix(glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.5f, 0.0f, 0.5f), t);
    }
    else {
        colorSphere1 = glm::vec3(1.0f, 0.0f, 0.0f);
        colorSphere2 = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    glUniform3fv(objectColorLoc, 1, glm::value_ptr(colorSphere1));
    glm::mat4 model1 = glm::translate(glm::mat4(1.0f), positionSphere1);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);

    glUniform3fv(objectColorLoc, 1, glm::value_ptr(colorSphere2));
    glm::mat4 model2 = glm::translate(glm::mat4(1.0f), positionSphere2);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);
}

void renderUniqueSphere(GLuint shaderProgram, GLuint VAO, const std::vector<unsigned int>& sphereIndices) {
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
    glUniform3f(objectColorLoc, 0.8f, 0.f, 0.8f);
    glUniform1f(ambientStrengthLoc, 0.2f);

    // Draw the sphere at the origin
    glm::mat4 model = glm::mat4(1.0f);
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);
}

void renderSuperpositionSphere(GLuint shaderProgram, GLuint VAO, const std::vector<unsigned int>& sphereIndices, float time) {
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
    glm::vec3 objectColor = glm::vec3(1.0f - normalizedPosition, 0.0f, normalizedPosition);

    glUniform3fv(objectColorLoc, 1, glm::value_ptr(objectColor));
    glUniform1f(ambientStrengthLoc, 0.6f);

    // smooth effect
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, displacement, 0.0f));

    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);
}
