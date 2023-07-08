#pragma once
#include <glm/glm.hpp>
namespace Hasbu::Render {

unsigned int createCamera(const glm::vec3& position = { -100.0f, 0.0f, 3.0f });
const glm::mat4 getViewMatrix(const unsigned int cameraID);

void processKeyBoardInputCamera(const double delta);
void processMauseInputCamera(const double xpos, const double ypos);
void processMauseInputScrollCamera([[maybe_unused]] const double xpos, const double ypos);

const glm::vec3& getCameraPosition(const unsigned int cameraID);
const glm::vec3& getCameraFront(const unsigned int cameraID);
float getCameraFov(const unsigned int cameraID);

}
