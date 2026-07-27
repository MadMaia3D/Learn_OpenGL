#ifndef MOUSE_H
#define MOUSE_H


#include <glfw/glfw3.h>


#define MOUSE_NOT_PRESSED   0
#define MOUSE_PRESSED       1
#define MOUSE_HOLD          2
#define MOUSE_RELEASE       3

typedef struct {
    float x;
    float y;
    float last_x;
    float last_y;
    float pressed_x;
    float pressed_y;
    int state;
} Mouse;


void UpdateMouse(GLFWwindow *window, Mouse *mouse) {
    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
    mouse->last_x = mouse->x;
    mouse->last_y = mouse->y;
    mouse->x = x;
    mouse->y = y;

    int mouse_left_button = glfwGetMouseButton(window, 0);

    if (mouse_left_button == GLFW_PRESS) {
        switch (mouse->state) {
        case MOUSE_NOT_PRESSED:
            mouse->state = MOUSE_PRESSED;
            mouse->pressed_x = x;
            mouse->pressed_y = y;
            break;
        case MOUSE_PRESSED:
            mouse->state = MOUSE_HOLD;
            break;
        case MOUSE_HOLD:
            mouse->state = MOUSE_HOLD;
            break;
        case MOUSE_RELEASE:
            mouse->state = MOUSE_PRESSED;
            break;
        default:
            mouse->state = MOUSE_NOT_PRESSED;
            break;
        }
    } else {
        switch (mouse->state) {
        case MOUSE_NOT_PRESSED:
            mouse->state = MOUSE_NOT_PRESSED;
            break;
        case MOUSE_PRESSED:
            mouse->state = MOUSE_RELEASE;
            break;
        case MOUSE_HOLD:
            mouse->state = MOUSE_RELEASE;
            break;
        case MOUSE_RELEASE:
            mouse->state = MOUSE_NOT_PRESSED;
            break;
        default:
            mouse->state = MOUSE_NOT_PRESSED;
            break;
        }
    }
}


#endif