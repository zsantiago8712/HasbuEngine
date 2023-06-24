#include "Renderer/Camera.hpp"
#include "Application/Application.hpp"
#include "Application/KeyCodes.hpp"
#include "Utilities/Logger.hpp"
// #include <GLFW/glfw3.h>
#include "Application/Input.hpp"

#include <glm/glm.hpp>

namespace HasbuRender {

static double delta_time = 0.0f;
static double last_frame = 0.0f;
static float sd = 0.5;

void Camera::proccesKeyBoard()
{

    this->speed = 2.5 * delta_time;

    if (Hasbu::isKeyBeenPressed(Hasbu::KeyCode::W)) {
        this->position += Camera::speed * this->front;
        HASBU_DEBUG("Move forward");
    } else if (Hasbu::isKeyBeenPressed(Hasbu::KeyCode::S)) {
        this->position -= Camera::speed * this->front;
        HASBU_DEBUG("Move backards");
    } else if (Hasbu::isKeyBeenPressed(Hasbu::KeyCode::A)) {
        this->position -= la::normalize(la::cross(this->front, this->up)) * Camera::speed;
        HASBU_DEBUG("Move to the Left");
    } else if (Hasbu::isKeyBeenPressed(Hasbu::KeyCode::D)) {
        this->position += la::normalize(la::cross(this->front, this->up)) * Camera::speed;
        HASBU_DEBUG("Move to the Left");
    }
}

la::mat4 Camera::getViewMatrix() const
{
    // NOTE: Se suman los vectores para asegurar que la camara siga viendo
    //  al target (front)
    //
    return la::lookAt(this->position, this->position + this->front, this->up);
}

double Camera::getDeltaTime()
{

    double current_time = Hasbu::getTime();
    delta_time = current_time - last_frame;
    last_frame = current_time;
    sd = delta_time * 5.0f;

    return delta_time;
}
}
