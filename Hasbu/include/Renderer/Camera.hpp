#pragma once
#include "LA/la.hpp"

namespace HasbuRender {

struct Camera {

    // Camera() { Camera::speed = 0.5f; };

    la::vec3 position { 0.0f, 0.0f, 3.0f };
    la::vec3 front { 0.0f, 0.0f, -1.0f };
    la::vec3 right;
    la::vec3 up { 0.0f, 1.0f, 0.0f };

    void proccesKeyBoard();

    la::mat4 getViewMatrix() const;
    static double getDeltaTime();

    float speed = 0.5f;
};

}
